#pragma once
// テキストファイルによる UI の翻訳。
//
// 1 つの言語は UTF-8 のテキストファイルで、1 行に 1 フレーズ、左側が英語:
//    @code = tr
//    @name = Türkçe
//    Refresh now = Şimdi yenile
//    {name} is at {percent}% = {name}: %{percent} kaldı
// # で始まる行はコメント。訳文中の "\n" は改行になる。プレースホルダーには名前が付いている
// （{name}、{percent}）ので、翻訳を間違えてもアプリが落ちることはない。最悪でも単語がおかしくなるだけ。
// 訳がないフレーズは英語のまま。
//
// 言語の読み込み元:
//  * リポジトリの lang\*.txt。exe に組み込まれる（言語の追加 = ファイルの追加。コードの変更は不要）
//  * WirelessBattery.exe の隣の "lang" フォルダーと %APPDATA%\WirelessBattery\lang: ここに置いた .txt は
//    ビルドし直さなくても「言語」メニューに出る。組み込みの言語と同じ @code のファイルは、その訳を置き換える
//    （手元で単語を直したいとき用）。
// --list / --dump の出力は、あえて英語のままにしている（GitHub の issue に貼り付けるため）。
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

namespace i18n {

struct Language {
    std::wstring code;  // "tr"、"pt-BR" など
    std::wstring name;  // その言語自身での名前: "Türkçe"、"Português (Brasil)"
};

// 言語（組み込みとユーザーのファイル）を探し、保存された選択を適用する。起動時に 1 回呼ぶ。
void Init();
// 選べるすべての言語。先頭は英語。
std::vector<Language> Available();
// 保存された選択: 空 = Windows の表示言語に従う。
std::wstring Choice();
// 選択を保存し（"" = 自動）、その言語に切り替える。
void SetChoice(const std::wstring& code);
// 右から左に書く言語（ヘブライ語、アラビア語）なら true: メニューを右から並べる。
bool Rtl();
// %APPDATA%\WirelessBattery\lang を作り、全フレーズのテンプレートを置いてエクスプローラーで開く。
void OpenUserFolder();

}  // namespace i18n

// 英語の UI フレーズの訳。訳がなければフレーズそのもの。
const wchar_t* T(const wchar_t* en);
std::wstring T(const std::wstring& en);
// 名前付きプレースホルダー付きの T(): TF(L"{name} is at {percent}%", { { L"name", n }, { L"percent", L"40" } })。
std::wstring TF(const wchar_t* en, std::initializer_list<std::pair<const wchar_t*, std::wstring>> args);
