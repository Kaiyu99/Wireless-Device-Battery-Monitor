#pragma once
// タスクバーのウィジェットで、同じ種類のデバイス（マウス 2 台、コントローラー 2 台など）を区別するための
// 短いキャプション。普通は同じアイコンで描かれてしまうため。文字列処理だけで、Windows の API は呼ばない。
#include <string>
#include <vector>

#include "devices.h"

struct LabelInput {
    DeviceKind kind;
    std::wstring name;
};

// 入力 1 つにつきキャプションを 1 つ、同じ順番で返す。同じ種類のデバイスが他にも表示されるときだけキャプションが
// 付き、そうでなければ空になる。キャプションは最大 `maxChars` 文字で、同じ種類の中で重複しない。決め方の順番は
// 次のとおり: 区別できるなら名前の中で最初の意味のある単語（メーカー名や "Wireless"、"Mouse" のような一般的な
// 単語は飛ばす）、次に単語を増やす、次に名前の末尾の数字（"Xbox controller 2" -> "2"）、最後に入力順の
// 1, 2, 3...（同じ "DualSense" が 2 台など）。
std::vector<std::wstring> ShortLabels(const std::vector<LabelInput>& items, size_t maxChars = 3);
