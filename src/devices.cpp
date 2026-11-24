// すべてのドライバーを順番に実行する。メーカー別ドライバーが先に動き、自分が扱うデバイスを確保する。
// 汎用のフォールバックは、残ったデバイスだけを調べる。
#include "devices.h"

#include <algorithm>
#include <cstdio>
#include <cwchar>

#include "drivers/drivers.h"
#include "report.h"
#include "hid.h"

namespace {

// HKCU\Software\WirelessBattery\IgnoreDevices（REG_SZ）: 16 進の "VID:PID" を空白・カンマ・セミコロンで
// 区切って並べたもの（例: "28BD:0947, 046D:C547"）。ここにあるデバイスはどのドライバーも開かない（issue #232）。
std::vector<std::pair<USHORT, USHORT>> IgnoredDevices() {
    std::vector<std::pair<USHORT, USHORT>> out;
    wchar_t buf[1024];
    DWORD size = sizeof(buf);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\WirelessBattery", L"IgnoreDevices", RRF_RT_REG_SZ, nullptr, buf, &size) !=
        ERROR_SUCCESS)
        return out;
    for (const wchar_t* p = buf; *p;) {
        unsigned vid = 0, pid = 0;
        int used = 0;
        if (swscanf(p, L" %x:%x%n", &vid, &pid, &used) == 2 && used > 0) {
            out.push_back({ (USHORT)vid, (USHORT)pid });
            p += used;
        } else {
            p++;
        }
        while (*p == L',' || *p == L';' || *p == L' ') p++;
    }
    return out;
}

}  // namespace

std::vector<DeviceStatus> PollAllDevices() {
    PollContext ctx;
    ctx.colls = EnumHid();
    auto ignored = IgnoredDevices();
    if (!ignored.empty())
        ctx.colls.erase(std::remove_if(ctx.colls.begin(), ctx.colls.end(), [&](const HidColl& c) {
                            return std::find(ignored.begin(), ignored.end(), std::make_pair(c.vid, c.pid)) != ignored.end();
                        }),
                        ctx.colls.end());
    PollGlorious(ctx);
    PollAula(ctx);       // Kysona より前: 3554 のベンダー ID を共有しており、Kysona が先に問い合わせてしまうため
    PollDareu(ctx);
    PollDarmoshark(ctx);
    PollAtkSerial(ctx);  // Kysona より前: ATK のベンダー ID を共有しているため
    PollAtkKeyboard(ctx);
    PollPulsar(ctx);     // Kysona より前: Kysona も 3710 のベンダー ID を走査するため
    PollAtkBitmouse(ctx);  // Kysona より前: Kysona が NK ドングルに間違ったプロトコルで問い合わせてしまうため
    PollKysona(ctx);
    PollKeychron(ctx);
    PollCherry(ctx);
    PollArbiter(ctx);    // Lamzu より前: 373E のベンダー ID を共有しているため
    PollLamzu(ctx);
    PollEndgame(ctx);
    PollEndgameWe(ctx);
    PollVaxee(ctx);
    PollWlmouse(ctx);
    PollFinalmouse(ctx);
    PollNinjutso(ctx);
    PollSprime(ctx);
    PollRongyuan(ctx);
    PollSonix(ctx);
    PollSemico(ctx);
    PollVspo(ctx);
    PollSonyInzone(ctx);
    PollFractal(ctx);
    PollJabra(ctx);
    PollJbl(ctx);
    PollRog(ctx);
    PollZowie(ctx);
    PollRoyalKludge(ctx);
    PollMchose(ctx);
    PollRapoo(ctx);
    PollAreson(ctx);
    PollMchoseG3(ctx);
    PollMsi(ctx);
    PollMachenike(ctx);  // PollMiscMice の Ajazz より前: L7 の 248A ベンダー ID を共有しているため
    PollNiceboy(ctx);    // 248A:FA02 の完全一致。これも Ajazz / Delux のポーリングより前
    PollMchoseModern(ctx);
    PollMchoseHeadset(ctx);
    PollMiscMice(ctx);
    PollFantech(ctx);
    PollRazerHeadsets(ctx);  // 汎用 Razer ドライバーより前: ベンダー ID を共有しているため
    PollBarracudaPro(ctx);   // これも汎用 Razer ドライバーより前
    PollHyperX(ctx);
    PollLogitechG435(ctx);  // HID++ ドライバーより前: ベンダー ID を共有しているため
    PollAstro(ctx);
    PollLogitech(ctx);
    PollRazer(ctx);
    PollSteelSeriesElite(ctx);
    PollSteelSeries(ctx);
    PollAudeze(ctx);
    PollNzxt(ctx);
    PollPlantronics(ctx);
    PollCorsair(ctx);
    PollCoolerMaster(ctx);
    PollPlayStation(ctx);
    PollSwitchPro(ctx);
    PollSteamController(ctx);
    PollGameSir(ctx);
    PollFlydigi(ctx);
    PollGameSirCyclone(ctx);
    Poll8BitDo(ctx);
    PollBeitong(ctx);  // XInput のフォールバックより前: XInput はレシーバーを有線としか認識しないため
    PollAirPods(ctx);  // Bluetooth のフォールバックより前: そちらでは AirPods の残量が取れないため
    PollPhoneLink(ctx);
    PollGalaxyBuds(ctx);  // Bluetooth のフォールバックより前: そちらは名前ですでに一覧にあるデバイスを飛ばすため
    PollMoondrop(ctx);
    PollAlienware(ctx);
    PollMaono(ctx);  // MAONO PD200W のレシーバー（352F:040E）。バッテリー問い合わせは試験的
    PollHeadsetControl(ctx);
    PollBluetooth(ctx);   // 汎用 HID チェックより前: 同じデバイスなら Windows 自身の残量を優先する
    PollGenericHid(ctx);
    PollXInput(ctx);
    return ctx.out;
}

std::wstring DumpHidCollections() {
    std::wstring out = L"VID:PID    IF  UsagePg:Usage  In  Out Feat  Product\n";
    for (const auto& c : EnumHid()) {
        wchar_t line[160];
        swprintf(line, 160, L"%04X:%04X  %2d  %04X:%04X    %3u %3u %3u   ", c.vid, c.pid, c.iface, c.page(), c.usage(), c.inLen(), c.outLen(),
                 c.featLen());
        out += line + HidProduct(c) + L"\n";
    }
    out += report::DumpExtras();  // 開けなかった HID コレクション、HID 以外の USB デバイス、Bluetooth デバイス
    out += DumpXentaFrames();
    return out;
}
