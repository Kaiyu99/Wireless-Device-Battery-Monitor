#pragma once
// すべてのドライバーで共有する、薄い Win32 HID レイヤー。
//
// レポートバッファーは hidapi の約束事に従うので、他プロジェクトのプロトコルのコードをそのまま当てはめられる:
//  * Write/SetFeature: data[0] はレポート ID（デバイスがレポートに番号を付けない場合は 0）。
//    バッファーはレポート長までゼロで埋める。
//  * Read: 先頭のレポート ID が 0 なら取り除くので、番号なしのレポートでは data[0] がペイロードの
//    最初のバイト、番号付きのレポートではレポート ID になる。
#include "platform_compat.h"

#ifdef _WIN32
#include <hidsdi.h>
#include <hidpi.h>
#else
// ポータブルなドライバーが必要とするのは、HidColl のアクセサーが使うフィールドだけ。
struct HIDP_CAPS {
    USHORT UsagePage = 0, Usage = 0;
    USHORT InputReportByteLength = 0;
    USHORT OutputReportByteLength = 0;
    USHORT FeatureReportByteLength = 0;
};
#endif

#include <initializer_list>
#include <string>
#include <vector>

#include "devices.h"

struct HidColl {
    std::wstring path;
    std::wstring product;  // Linux バックエンドが sysfs から設定する。Windows では使わない
    USHORT vid = 0, pid = 0;
    int iface = -1;  // USB のインターフェース番号（パス中の MI_xx）。不明なら -1
    HIDP_CAPS caps{};
    USHORT page() const { return caps.UsagePage; }
    USHORT usage() const { return caps.Usage; }
    USHORT inLen() const { return caps.InputReportByteLength; }
    USHORT outLen() const { return caps.OutputReportByteLength; }
    USHORT featLen() const { return caps.FeatureReportByteLength; }
};

std::vector<HidColl> EnumHid();

class HidDev {
public:
    HidDev() = default;
    ~HidDev() { Close(); }
    HidDev(const HidDev&) = delete;
    HidDev& operator=(const HidDev&) = delete;

    bool Open(const HidColl& c);            // 読み書き、オーバーラップ I/O
    bool OpenReadOnly(const HidColl& c);    // 読み取り専用、オーバーラップ I/O: 他のアプリが握っているかもしれない、プッシュ専用のコレクション用
    bool OpenFeatureOnly(const HidColl& c);  // アクセス権なし: フィーチャーレポートには十分で、マウスやキーボードでも使える
    void Close();
#ifdef _WIN32
    bool ok() const { return h_ != INVALID_HANDLE_VALUE; }
#else
    bool ok() const { return fd_ >= 0; }
#endif
    const HidColl& coll() const { return c_; }

    bool Write(const std::vector<BYTE>& data, int timeoutMs = 500);
    bool Write(std::initializer_list<BYTE> data, int timeoutMs = 500) { return Write(std::vector<BYTE>(data), timeoutMs); }
    // 入力レポートを 1 つ `buf` に読み込む（サイズは合わせて変更）。バイト数を返し、タイムアウトやエラーなら -1。
    int Read(std::vector<BYTE>& buf, int timeoutMs);
    // インターラプト OUT パイプがないコレクション用（そこでは WriteFile が失敗する）: 読み取りを開始してから
    // `data` を HidD_SetOutputReport で送り、Read() と同じように最初の入力レポートを返す。
    int SetOutputAndRead(const std::vector<BYTE>& data, std::vector<BYTE>& buf, int timeoutMs);
    void Flush();  // たまっている入力レポートを捨てる

    bool SetFeature(const std::vector<BYTE>& data);
    bool GetFeature(BYTE reportId, std::vector<BYTE>& out);  // out[0] = レポート ID
    bool GetFeatureByte(BYTE reportId, BYTE& value);  // 読み取りハンドルで、番号付きの 2 バイトのレポート
    bool GetInputReport(BYTE reportId, std::vector<BYTE>& out);  // コントロールパイプ経由で現在の入力レポートを取得。out[0] = レポート ID

private:
#ifdef _WIN32
    HANDLE h_ = INVALID_HANDLE_VALUE;
    bool overlapped_ = false;
#else
    int fd_ = -1;  // /dev/hidrawN
#endif
    HidColl c_;
};

std::wstring HidProduct(const HidColl& c);
std::wstring Hex4(USHORT v);
int Clamp100(int v);
int MapTo100(int v, int lo, int hi);  // lo..hi を 0..100 に線形変換し、範囲内に収める
// (mv[i], pct[i]) を通る折れ線で補間する。テーブルは電圧の高い順に並べること。
int Interpolate(int mv, const int* mvTable, const int* pctTable, int n);
DeviceKind GuessKind(const std::wstring& name);
// デバイスが公開する最上位コレクションから種類を決める（マウス > ゲームパッド > キーボード）。
DeviceKind KindFromCollections(const std::vector<HidColl>& all, USHORT vid, USHORT pid);
