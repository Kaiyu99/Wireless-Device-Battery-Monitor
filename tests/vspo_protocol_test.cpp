// VSPO! GEAR キーボードのプロトコル（src/drivers/vspo_protocol.h）の単体テスト。
// 期待値は公式の Web ドライバーが送るバイト列（getBase / getFunc）と、Fi()（e & 127 を 0〜100 に収める）から。
#include "../src/drivers/vspo_protocol.h"

#include <cstdio>

static int failures = 0;
#define CHECK(cond)                                                    \
    do {                                                               \
        if (!(cond)) {                                                 \
            std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
            failures++;                                                \
        }                                                              \
    } while (0)

using namespace vspo;

static std::vector<uint8_t> Reply(uint8_t cmd, uint8_t battery) {
    std::vector<uint8_t> r(kPayloadLen, 0);
    r[0] = 0x55;
    r[1] = cmd;
    r[kDataOffset + kBatteryIndex] = battery;
    return r;
}

int main() {
    // getBase: [00][55 04 00 20 20 ...]
    auto base = BuildGetBase();
    CHECK(base.size() == 65);
    CHECK(base[0] == 0x00 && base[1] == 0x55 && base[2] == 0x04 && base[3] == 0x00 && base[4] == 0x20 && base[5] == 0x20);

    // getFunc(0) の最初のチャンク: addr 0, len 56 → sum = 56 = 0x38
    auto f0 = BuildGetFunc(0);
    CHECK(f0.size() == 65);
    CHECK(f0[1] == 0x55 && f0[2] == 0x05 && f0[3] == 0x00 && f0[4] == 0x38 && f0[5] == 0x38 && f0[6] == 0x00 && f0[7] == 0x00);
    // getFunc(2): addr 128 = 0x80 → sum = (0x80 + 0 + 0x38) & 0xFF = 0xB8
    auto f2 = BuildGetFunc(2);
    CHECK(f2[4] == 0xB8 && f2[5] == 0x38 && f2[6] == 0x80 && f2[7] == 0x00);
    // getFunc(3): addr 192 = 0xC0 → sum = 0xF8
    CHECK(BuildGetFunc(3)[4] == 0xF8);

    // バッテリーのバイト
    Battery b = ParseBatteryByte(85);
    CHECK(b.percent == 85 && !b.charging);
    b = ParseBatteryByte(0x80 | 40);
    CHECK(b.percent == 40 && b.charging);
    b = ParseBatteryByte(0x7F);  // 127 は 100 に丸める
    CHECK(b.percent == 100);
    b = ParseBatteryByte(0);
    CHECK(b.percent == -1);

    // 通知レポートは応答として使わない
    CHECK(IsNotification({ 0xA0, 0x01 }));
    CHECK(IsNotification({ 0xA3 }));
    CHECK(IsNotification({ 0xFA, 0xFB, 0x07, 0x00, 0x00, 50 }));
    CHECK(IsNotification({ 0xFA, 0xFB, 0x06, 0x00 }));
    CHECK(!IsNotification({ 0xFA, 0xFB, 0x08 }));
    CHECK(IsWirelessDisconnect({ 0xFA, 0xFB, 0x06, 0x00 }));
    CHECK(!IsWirelessDisconnect({ 0xFA, 0xFB, 0x06, 0x01 }));

    // 応答の判定
    CHECK(IsReplyTo(Reply(0x05, 80), 0x05));
    CHECK(!IsReplyTo(Reply(0x04, 80), 0x05));          // 別のコマンドのエコー
    CHECK(!IsReplyTo(std::vector<uint8_t>(20, 0), 0x05));  // 短すぎる
    auto noEcho = Reply(0x05, 80);
    noEcho[0] = 0x00;
    CHECK(IsReplyTo(noEcho, 0x05));  // エコーがない形でも、Web ドライバーと同じく受け付ける

    if (failures) {
        std::printf("%d failure(s)\n", failures);
        return 1;
    }
    std::printf("vspo_protocol_test: OK\n");
    return 0;
}
