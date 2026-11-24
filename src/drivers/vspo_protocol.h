#pragma once
// VSPO! GEAR ゲーミングキーボード Ver.2（Luminkey 系のファームウェア、ベンダー ID 19F5）のバッテリー問い合わせ。
// Windows に依存しない部分だけをここに置き、tests/vspo_protocol_test.cpp から単体でテストできるようにしている。
//
// プロトコルは公式の Web ドライバー（vspogear-keyboard.app、assets/index-*.js）から読み取ったもの:
//   出力レポート: レポート ID 0 + 64 バイト。[55][cmd][00][sum][len][addr lo][addr hi][00 ...]
//                 sum = (addr lo + addr hi + len) & 0xFF
//   応答:         同じコレクションに届く 64 バイトの入力レポート。データは先頭から 8 バイト目以降
//   cmd 04 (getBase):  [55 04 00 20 20] → data[0] = 現在のプロファイル番号（0〜3）
//   cmd 05 (getFunc):  プロファイル p の設定ブロック（64 バイト）を addr = 64 * p から読む。
//                      ブロックの 32 バイト目がバッテリー: 下位 7 ビット = 残量（%）、最上位ビット = 充電中
// キーボードからは次のレポートも勝手に届くので、応答待ちの間は読み飛ばす（Web ドライバーと同じ）:
//   先頭が A0〜A3 のレポート、[FA FB 06 xx]（無線の切断 00 / 再接続 01）、[FA FB 07 xx ...]（バッテリー通知）
#include <cstddef>
#include <cstdint>
#include <vector>

namespace vspo {

constexpr uint16_t kVid = 0x19F5;
constexpr uint16_t kReceiverPid = 0x8F10;  // 2.4G レシーバー（Web ドライバーでの名前は "VSPO 80HE JIS (2.4G receiver)"）
constexpr uint16_t kCablePid = 0xA022;     // USB ケーブル（"VSPO 80HE JIS"）

constexpr uint8_t kCmdPrefix = 0x55;
constexpr uint8_t kCmdGetBase = 0x04;
constexpr uint8_t kCmdGetFunc = 0x05;
constexpr size_t kPayloadLen = 64;   // レポート ID を除いた出力 / 入力レポートの長さ
constexpr size_t kDataOffset = 8;    // 応答のうち、データが始まる位置
constexpr size_t kBatteryIndex = 32; // 設定ブロック内のバッテリーのバイト

// レポート ID 0 を先頭に付けた、65 バイトの出力レポートを作る（hid.h の Write() の約束事どおり）。
inline std::vector<uint8_t> BuildRequest(uint8_t cmd, uint8_t len, uint16_t addr) {
    std::vector<uint8_t> r(1 + kPayloadLen, 0);
    uint8_t lo = (uint8_t)(addr & 0xFF), hi = (uint8_t)(addr >> 8);
    r[1] = kCmdPrefix;
    r[2] = cmd;
    r[3] = 0x00;
    r[4] = (uint8_t)((lo + hi + len) & 0xFF);
    r[5] = len;
    r[6] = lo;
    r[7] = hi;
    return r;
}

// getBase: Web ドライバーは [55 04 00 20 20] を送る（ここだけ sum と len の意味が違うが、そのまま真似る）。
inline std::vector<uint8_t> BuildGetBase() {
    std::vector<uint8_t> r(1 + kPayloadLen, 0);
    r[1] = kCmdPrefix;
    r[2] = kCmdGetBase;
    r[3] = 0x00;
    r[4] = 0x20;
    r[5] = 0x20;
    return r;
}

// getFunc の最初の 56 バイト分（バッテリーの 32 バイト目を含む）。
inline std::vector<uint8_t> BuildGetFunc(int profile) {
    return BuildRequest(kCmdGetFunc, 56, (uint16_t)(64 * profile));
}

// 勝手に届く通知レポートなら true（応答としては使わない）。r はレポート ID 0 を取り除いたもの。
inline bool IsNotification(const std::vector<uint8_t>& r) {
    if (r.empty()) return true;
    if (r[0] >= 0xA0 && r[0] <= 0xA3) return true;
    if (r.size() >= 3 && r[0] == 0xFA && r[1] == 0xFB && (r[2] == 0x06 || r[2] == 0x07)) return true;
    return false;
}

// 応答として使えるか。先頭が 55 なら、送ったコマンドのエコーであることも確かめる。
inline bool IsReplyTo(const std::vector<uint8_t>& r, uint8_t cmd) {
    if (IsNotification(r) || r.size() < kDataOffset + kBatteryIndex + 1) return false;
    if (r[0] == kCmdPrefix && r[1] != cmd) return false;
    return true;
}

struct Battery {
    int percent = -1;  // 0..100、わからなければ -1
    bool charging = false;
};

// 設定ブロックのバッテリーのバイトを読み解く。0 はキーボードがつながっていない（値がない）ものとして扱う。
inline Battery ParseBatteryByte(uint8_t b) {
    Battery out;
    int level = b & 0x7F;
    if (level > 100) level = 100;
    out.charging = (b & 0x80) != 0;
    if (b != 0) out.percent = level;
    return out;
}

// [FA FB 06 00] = 無線が切れた（キーボードの電源オフ、範囲外など）。
inline bool IsWirelessDisconnect(const std::vector<uint8_t>& r) {
    return r.size() >= 4 && r[0] == 0xFA && r[1] == 0xFB && r[2] == 0x06 && r[3] == 0x00;
}

}  // namespace vspo
