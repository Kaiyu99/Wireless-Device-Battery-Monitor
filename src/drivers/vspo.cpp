// VSPO! GEAR ゲーミングキーボード Ver.2（ぶいすぽっ! メンバーモデル。例: "Kaminari Qpi 2.4G"）。
// 2.4G レシーバー（19F5:8F10）または USB ケーブル（19F5:A022）。Luminkey 系のファームウェア。
//
// バッテリーは、メーカー独自コレクション（Web ドライバーと同じく FF00:0001、なければ 0001:0000 の
// 64 バイトの入出力レポート。レシーバーではインターフェース 1）に、読み取り専用の問い合わせを 2 つ送って取る:
//   1. getBase [55 04 00 20 20]          → 現在のプロファイル番号
//   2. getFunc [55 05 00 sum 38 lo hi]   → そのプロファイルの設定ブロック。32 バイト目がバッテリー
// バイトの意味とフレームの形は vspo_protocol.h を参照（公式の Web ドライバー vspogear-keyboard.app より）。
// 書き込み系のコマンド（06 setFunc など）は一切送らない。
//
// Web ドライバーは 15 秒ごとに問い合わせているので、このアプリのポーリング間隔なら毎回聞いても問題ない。
// Bluetooth 接続は Windows 自身の残量（PollBluetooth）に任せる。
#include "drivers.h"
#include "vspo_protocol.h"

namespace {

using namespace vspo;

// 問い合わせを 1 つ送り、応答（レポート ID 0 を取り除いたもの）を受け取る。
// 無線の切断通知を見かけたら disconnected を立てる。
bool Transact(HidDev& d, const std::vector<BYTE>& req, BYTE cmd, std::vector<BYTE>& reply, bool& disconnected) {
    d.Flush();
    if (!d.Write(req)) return false;
    ULONGLONG end = GetTickCount64() + 600;
    for (;;) {
        int left = (int)((LONGLONG)end - (LONGLONG)GetTickCount64());
        if (left <= 0) return false;
        std::vector<BYTE> r;
        int n = d.Read(r, left);
        if (n < 0) return false;
        if (IsWirelessDisconnect(r)) disconnected = true;
        if (!IsReplyTo(r, cmd)) continue;
        reply.swap(r);
        return true;
    }
}

// 成功すれば true。キーボードがつながっていない（値 0 や切断通知）ときは b.percent が -1 のまま true を返す。
bool ReadBattery(const HidColl& c, Battery& b, bool& disconnected) {
    HidDev d;
    if (!d.Open(c)) return false;
    std::vector<BYTE> r;
    int profile = 0;
    if (Transact(d, BuildGetBase(), kCmdGetBase, r, disconnected)) {
        int p = r[kDataOffset];
        if (p >= 0 && p <= 3) profile = p;
    }
    if (!Transact(d, BuildGetFunc(profile), kCmdGetFunc, r, disconnected)) return false;
    b = ParseBatteryByte(r[kDataOffset + kBatteryIndex]);
    return true;
}

// Web ドライバーと同じ選び方: FF00:0001 を優先し、なければ 0001:0000。どちらも 64 バイト + レポート ID。
const HidColl* PickCollection(const PollContext& ctx, USHORT pid) {
    auto sized = [](const HidColl& c) { return c.inLen() == 1 + kPayloadLen && c.outLen() == 1 + kPayloadLen; };
    auto vendor = ctx.Find(kVid, pid, [&](const HidColl& c) { return sized(c) && c.page() == 0xFF00 && c.usage() == 0x0001; });
    if (!vendor.empty()) return vendor.front();
    auto generic = ctx.Find(kVid, pid, [&](const HidColl& c) { return sized(c) && c.page() == 0x0001 && c.usage() == 0x0000; });
    if (!generic.empty()) return generic.front();
    return nullptr;
}

// "Kaminari Qpi 2.4G" → "Kaminari Qpi"。
std::wstring KeyboardName(const HidColl& c) {
    std::wstring name = HidProduct(c);
    while (!name.empty() && name.back() == L' ') name.pop_back();
    const std::wstring suffix = L" 2.4G";
    if (name.size() > suffix.size() && name.compare(name.size() - suffix.size(), suffix.size(), suffix) == 0)
        name.resize(name.size() - suffix.size());
    return name.empty() ? L"VSPO! GEAR Keyboard" : name;
}

}  // namespace

void PollVspo(PollContext& ctx) {
    for (USHORT pid : { kCablePid, kReceiverPid }) {  // 両方つながっていればケーブルを優先する
        if (ctx.IsClaimed(kVid, pid)) continue;
        const HidColl* c = PickCollection(ctx, pid);
        if (!c) continue;
        bool cable = pid == kCablePid;
        Battery b;
        bool disconnected = false;
        // 2.4 GHz のリンクが起きる途中で最初の問い合わせが無視されることがあるので、1 回だけやり直す。
        bool ok = ReadBattery(*c, b, disconnected);
        if (!ok && !disconnected) ok = ReadBattery(*c, b, disconnected);

        DeviceStatus s;
        s.key = L"vspo:19F5";  // どちらの接続でも同じキーボードとして 1 つにまとめる
        s.name = KeyboardName(*c);
        s.kind = DeviceKind::Keyboard;
        s.via = cable ? L"USB cable" : L"2.4 GHz receiver";
        s.graceSec = 1800;  // スリープ中で応答しないときは、しばらく最後の値を表示し続ける
        if (ok && b.percent >= 0) {
            s.percent = b.percent;
            s.charging = b.charging;
        } else if (disconnected || (ok && b.percent < 0)) {
            s.connected = false;  // レシーバーはあるがキーボードの電源が切れている、範囲外、または別モード
        } else {
            s.asleep = true;      // 応答なし: スリープ中か処理中。最後の値を保持する
        }
        ctx.Add(s, kVid, pid);
        if (cable) ctx.Claim(kVid, kReceiverPid);
        return;
    }
}
