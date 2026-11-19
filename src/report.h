#pragma once
// 「デバイスのサポートをリクエスト」: 表示されないデバイスをユーザーが選ぶ小さなウィンドウ。アプリはその名前と
// 短い技術情報を krisgfx.com/tools の公開リクエスト一覧に送る（GitHub の issue が作成または更新される）。
// ユーザーが「送信」を押すまで何も送らず、送る内容はウィンドウに先にそのまま表示する。
#include <windows.h>

#include <string>

namespace report {

// ウィンドウを開く（すでに開いていれば前面に出す）。オーナーがない場合（`--report`）は、ウィンドウを
// 閉じるとメッセージループが終わる。
void Show(HINSTANCE inst, HWND owner);

// ウィンドウ内で Tab / Enter / Esc が効くようにする。メッセージループで TranslateMessage の前に呼ぶこと。
bool PreTranslate(MSG* msg);

// `--dump` と完全なレポート用の追加セクション: 開けなかった HID デバイス、すべての USB デバイス
// （HID インターフェースがないもの、たとえば音声専用や WinUSB のドングル、シリアルポートも含む）、そして
// Windows が把握している Bluetooth デバイス。
std::wstring DumpExtras();

}  // namespace report
