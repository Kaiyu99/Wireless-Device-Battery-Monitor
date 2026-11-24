#pragma once
// デバイスのブランド表示: メーカーの色のアイコンにやわらかな光彩を付け、パーセントの下に細い残量バーを
// 表示する（Razer Synapse / Logitech G HUB のような見た目）。Accent::None なら通常のシステムの見た目のまま。
#include <string>
#include "devices.h"

enum class Accent {
    None,
    Razer, Logitech, SteelSeries, Corsair, HyperX, Rog, Zowie,
    PlayStation, Xbox, Galaxy, Apple, Jabra, Jbl, CoolerMaster, Steam, Vspo, Pulsar,
};

struct BrandColor { unsigned char r, g, b; };

struct BrandStyle {
    Accent accent;
    const wchar_t* name;  // "SteelSeries"（--list で表示される）
    BrandColor dark;      // 暗いタスクバー用: ブランドカラー。暗すぎて読みにくい場合だけ明るくする
    BrandColor light;     // 明るいタスクバー用: 同じ色相の濃い色（コントラスト 3:1 以上）
};

// すべてのブランドとその色。enum の順番（先頭は Accent::None）。
const BrandStyle* AllBrands(int& count);
const BrandStyle& StyleOf(Accent a);
BrandColor AccentColor(Accent a, bool lightTaskbar);

// ブランドの判定順: ドライバーのキー（"steelseries:..."）、次に USB / Bluetooth のベンダー ID、最後に名前。
Accent BrandOf(const DeviceStatus& s);
