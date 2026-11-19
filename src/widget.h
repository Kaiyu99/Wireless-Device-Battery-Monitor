#pragma once
// タスクバー上、通知領域のすぐ左に置く小さな透明の帯。"[アイコン] 30%  [アイコン] 93%" のように表示する。
// タスクバー（Shell_TrayWnd）のレイヤードな子ウィンドウとして実装し、サブモニターのタスクバー
// （Shell_SecondaryTrayWnd）にも時計の隣にコピーを置く。
#include <windows.h>
#include <string>
#include <vector>
#include "brands.h"
#include "devices.h"

struct WidgetItem {
    DeviceKind kind = DeviceKind::Other;
    int  percent  = -1;     // -1 = 不明
    std::wstring text;      // 設定されていればパーセントの代わりに表示する（"Low" のような大まかな段階）
    bool charging = false;
    bool dim      = false;  // スリープ中 / 古い値
    bool low      = false;
    bool bluetooth = false;  // デバイスの種類が不明なときに Bluetooth のアイコンを選ぶ
    bool chargingCase = false;  // イヤホンの充電ケース: アイコンフォントに絵柄がないので専用の形を描く
    std::wstring label;      // アイコンに付ける小さなキャプション。同じ種類のデバイスが 2 台表示されるときだけ設定する
    Accent accent  = Accent::None;  // アイコン、その光彩、残量バーに使うブランドカラー
};

namespace widget {
// メインのタスクバーにウィジェットを作る。クリックは `notifyWnd` に `clickMsg` を投げて知らせる。
bool Create(HINSTANCE inst, HWND notifyWnd, UINT clickMsg, bool lightTheme);
void Destroy();
bool Alive();
void SetItems(const std::vector<WidgetItem>& items, const std::wstring& tooltip);
void SetLightTheme(bool light);
// 文字の後ろに、タスクバーの色で角の丸い背景を描く（Create/Destroy をまたいで保持）。
void SetBackground(bool on);
// タスクバーに十分な高さがあれば、アイコンをパーセントの横ではなく上に置く（Create/Destroy をまたいで保持）。
void SetStacked(bool on);
// 帯を表示するタスクバー: L"all"（既定）、L"main"、または OtherMonitors() で得たほかのモニター 1 台の ID
// （その場合はそのモニターにだけ表示）。Create/Destroy をまたいで保持。
void SetMonitorChoice(const std::wstring& choice);
struct MonitorOption {
    std::wstring id;     // 変わらないモニターの識別子。設定に保存する
    std::wstring label;  // "Display 3 (right)"
};
// メイン以外で、横向きのタスクバーがあるモニター（モニターが 1 台なら空）。
std::vector<MonitorOption> OtherMonitors();
// タスクバーの配置を確認し直し、必要ならウィジェットを動かす。1 秒に 1 回くらい呼ぶこと。
// 取り付け先のタスクバーがなくなっていたら false を返す。
bool Reposition();
}
