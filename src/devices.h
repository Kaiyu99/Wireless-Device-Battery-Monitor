#pragma once
#include <string>
#include <vector>

enum class DeviceKind { Other, Mouse, Headset, Keyboard, Gamepad, Phone };

// 左右に分かれたイヤホンの片側（または充電ケース）の残量。
struct EarbudLevel {
    std::wstring side;   // "L" / "R" / "C"（ケース）。キーの末尾とアイコンのキャプションに使う
    int percent = -1;    // 0..100。ケースに入っているなど、今わからないときは -1
    std::wstring label;  // 名前に付ける表示（英語。翻訳して使う）。空なら side
    bool isCase = false; // 充電ケース（専用のケースのアイコンで描く）
};

// バッテリーで動くデバイス 1 台分の情報（1 回のポーリングで見えたもの）。
struct DeviceStatus {
    std::wstring key;          // ポーリングをまたいで変わらない識別子（トレイアイコンの ID に使う）
    std::wstring name;         // 人が読める名前
    std::wstring via;          // "2.4 GHz receiver"、"Bluetooth"、"USB cable" など
    DeviceKind kind = DeviceKind::Other;
    int  percent    = -1;      // 0..100。今わからないときは -1
    std::wstring detail;       // ツールチップ用の内訳。例: "L 80%, R 75%, case 40%"
    std::wstring levelText;    // 大まかな段階（"Low"、"Full" など）しか報告しないデバイスで設定される
    bool charging   = false;
    bool asleep     = false;   // レシーバーは応答したがデバイスはスリープ中（最後の値を保持する）
    bool connected  = true;    // false: レシーバーはあるがデバイスの電源がオフ（非表示）
    int  millivolts = 0;       // 報告される場合のバッテリー電圧（0 = 不明）
    int  graceSec   = 0;       // デバイスが応答しなくなっても、この時間は最後の値を表示し続ける
    std::vector<EarbudLevel> buds;  // 左右のイヤホン（わかる場合）。「左右のイヤホンを別々に表示」がオンなら 1 台ずつ表示する
    bool chargingCase = false; // イヤホンの充電ケース。ウィジェットでは専用のケースのアイコンで描く
    std::wstring caption;      // 空でなければ、アイコンのキャプションとして必ず表示する（左右のイヤホンとケースの "L" / "R" / "C"）
    unsigned short vid = 0;    // わかる場合の USB / Bluetooth HID のベンダー ID（ブランドカラーの判定に使う）
};

// 対応しているすべてのデバイスに問い合わせる。ブロッキング処理（1〜2 秒かかることがある）なので、ワーカースレッドから呼ぶこと。
std::vector<DeviceStatus> PollAllDevices();

// すべての HID コレクションを出力する（新しいデバイスに対応するときに使う）。
std::wstring DumpHidCollections();
