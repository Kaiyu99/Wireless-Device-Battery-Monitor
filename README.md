# Wireless Battery

[![Support me on Ko-fi](https://img.shields.io/badge/Ko--fi-Support%20me-FF5E5B?logo=ko-fi&logoColor=white)](https://ko-fi.com/krisgfx)
[![Donate with PayPal](https://img.shields.io/badge/PayPal-Donate-00457C?logo=paypal&logoColor=white)](https://www.paypal.com/paypalme/krisgfx)
[![GitHub Sponsors](https://img.shields.io/badge/GitHub-Sponsor-EA4AAA?logo=githubsponsors&logoColor=white)](https://github.com/sponsors/krisgfx9)
[![Join our Discord](https://img.shields.io/badge/Discord-Join%20us-5865F2?logo=discord&logoColor=white)](https://discord.gg/ZgDDUPP8ye)
[![Star on GitHub](https://img.shields.io/github/stars/krisgfx9/Wireless-Device-Battery-Monitor?style=flat&logo=github&label=Star)](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor)
[![Share on Reddit](https://img.shields.io/badge/Reddit-Share-FF4500?logo=reddit&logoColor=white)](https://www.reddit.com/submit?url=https%3A%2F%2Fgithub.com%2Fkrisgfx9%2FWireless-Device-Battery-Monitor&title=Wireless%20Battery%3A%20battery%20levels%20of%20your%20wireless%20devices%20on%20the%20Windows%20taskbar)
[![Report a device](https://img.shields.io/badge/Report-a%20device-2EA44F?logo=github&logoColor=white)](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/issues/new)
[![Help translate](https://img.shields.io/badge/Help-translate-6F42C1?logo=googletranslate&logoColor=white)](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/pull/129)

ワイヤレスのマウス、ヘッドセット、キーボード、コントローラーのバッテリー残量を、Windows のタスクバーに直接表示します。

![タスクバー上の Wireless Battery](docs/screenshot.png)

> **とにかく使いたいだけなら:** 最新リリースから **[WirelessBattery-Setup](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/releases/latest)** をダウンロードし、実行して画面に従って進めるだけです。
>
> **詳しい方は** ポータブル版の zip を使ったり、[コマンドラインオプション](#command-line)を使ったり、`make` や `build.bat` で[ソースからビルド](#build)したりできます。
>
> **気に入りましたか？** Wireless Battery は無料のオープンソースです。メーカーのソフトを開く手間が省けたなら、[Ko-fi](https://ko-fi.com/krisgfx)、[PayPal](https://www.paypal.com/paypalme/krisgfx)、[GitHub Sponsors](https://github.com/sponsors/krisgfx9) で支援していただけます。学業のかたわらアプリを無料で続けるための助けになります。寄付が難しい場合も、⭐ スター、共有、`--dump` を添えた未対応デバイスの報告が同じくらい力になります。

- **小さい**: 約 350 KB のアプリで、メモリ使用量は約 2 MB。素の C++/Win32 で作られており、ランタイムもバックグラウンドサービスも不要。管理者権限なしで数秒でインストールできます。
- **メーカーのソフトは不要**: デバイスと直接やり取りします。G HUB、Synapse、iCUE、GG、NGenuity は閉じたままで構いません（起動したままでも競合しません）。
- **多くのブランドに対応**: Logitech、Razer、SteelSeries、Corsair、HyperX、Glorious、Jabra、JBL、PlayStation と Xbox のコントローラー、Samsung Galaxy Buds、Windows がバッテリー残量を把握しているすべての Bluetooth デバイス、同梱の [HeadsetControl](https://github.com/Sapd/HeadsetControl) が対応するすべてのヘッドセット。

## 表示

**タスクバー上（既定）:** 通知領域の隣に `🎧 30%  🖱 93%` のように、Windows のアイコンフォントで表示します。
- **バッテリー低下:** 数字が赤いときは 15% 以下です（しきい値はメニューの *バッテリー低下の警告* で変更できます）。
- **充電中:** 数字の横に青い ⚡ が表示されます。
- **スリープ中:** 文字が薄いときはデバイスがスリープ中で、最後に確認した値を表示しています。
- **同じ種類のデバイスが 2 台:** マウス 2 台（やコントローラー 2 台など）はどちらも同じアイコンになるため、それぞれのアイコンの角に、名前から取った最大 3 文字の小さなキャプション（`MX`、`PRO`）を付けます。名前で区別できない場合は番号を付けます。その種類のデバイスが 1 台だけならキャプションは付きません。
- **テーマ:** ライト / ダークモードと DPI スケーリングに追従します。
- **透明なタスクバーのテーマ**（Windhawk の Taskbar Styler など）: メニューの *タスクバーの文字の背景* をオンにすると、壁紙の上でも文字が読みやすくなります。
- **複数のモニター:** ウィジェットは各モニターのタスクバーの時計の隣に表示されるので、ゲームを全画面で動かしている間も見えます。メニューの *ウィジェットの表示先* で *すべてのモニター*、*メインモニターのみ*、またはディスプレイ 1 台（例: *ディスプレイ 3* のみ）を選べます。
- **その他の表示オプション:** *パーセントの上にアイコン* は各アイコンを残量の上に積んで幅を節約します。*ブランドカラー* は知られたブランドをその色（Razer の緑、HyperX の赤など）と小さな残量バーで表示します。同じ種類のデバイス 2 台には区別用の小さなキャプションが付きます。左右に置いたタスクバーではデバイスが縦 1 列に並びます。
- **言語:** English、العربية、Deutsch、Español、Français、עברית、日本語、Polski、Português (Brasil)、Русский、Türkçe、简体中文、繁體中文。アプリは Windows の表示言語に従い、メニューの *言語* でほかの言語も選べます。言語の追加や改善は[翻訳](#translations)を参照してください。
- **ブランドカラー:** 知られた 15 ブランドのデバイスはメーカーの色で表示され、やわらかな光彩と、パーセントの下に細い残量バーが付きます: Razer の緑、Logitech の青、SteelSeries のオレンジ、Corsair の黄色、HyperX / ROG / ZOWIE の赤、PlayStation、Xbox、Samsung、Apple、Jabra、JBL、Cooler Master、Steam。各色には暗いタスクバー用と明るいタスクバー用の色合いがあります。ブランドは、デバイスを見つけたドライバー、次にベンダー ID、最後に名前から判定します。色と判定ルールは `src/brands.cpp` にあります。メニューの *ブランドカラー* でオフにできます。

**トレイアイコン:** デバイスごとに数字入りのアイコンを 1 つ表示し、残量が 15% になると「バッテリー残量低下」の通知を出します（しきい値はメニューで変更可能）。タスクバーが縦向きのときや見つからないときは、自動でこの表示に切り替わります。

マウスを重ねると詳細が表示されます。クリックするとメニューが開きます: 各デバイス（クリックで表示 / 非表示）、表示方法、*バッテリー低下の警告*、*充電完了の通知*、*今すぐ更新*、*Windows の起動時に開始*、*終了*。残量は 60 秒ごとに更新され、デバイスを接続したときや PC がスリープから復帰したときはすぐに更新されます。

## 対応デバイス

| メーカー | デバイス | 方式 |
|---|---|---|
| **ASTRO** | A50 X（`046D:0B0B`、動作確認済み）、A50 Gen 5（`046D:0B1C`）、A50 Gen 4（`9886:002C` は動作確認済み、`002D`/`002A`）、A50 Gen 3（`9886:0014`/`0015`/`0018`/`001D`/`0026`）、A20 Wireless（`9886:0037`–`0045`）。USB ベースステーション経由 | バッテリー残量、充電状態、ドックへの装着状態 |
| **Logitech** | Unifying、Bolt、Lightspeed（PRO X3 SUPERSTRIKE のドングル `046D:C54F` を含む）、Nano の各レシーバー、または USB / Bluetooth で接続したマウスとキーボード。G シリーズのヘッドセット（G533、G535、G633/G635/G733/G933/G935、G PRO/PRO X）。新しい `046D:0ADF` ドングルの G435 | 機能検出付きの HID++ 1.0 / 2.0: unified battery、battery level、電圧、ADC。G435: CRC-16 でフレーム化したメーカー独自レポート、mV 単位の `GET_BATTERY` |
| **Razer** | ワイヤレスのマウス、キーボード、ドングル。BlackShark V2 HyperSpeed、V2 Pro（2020/2023）、V3 / V3 Pro / V3 X ヘッドセット。2.4 GHz レシーバー（`1532:0550`）の Barracuda X（2022）。Barracuda Pro（`1532:053A`） | Razer のフィーチャーレポートのプロトコル。BlackShark 独自のプロトコル（V3 / V3 Pro / V3 X は 5 分ごとに問い合わせ）。Barracuda X: レシーバー経由で Airoha のバッテリーとケーブルを問い合わせ |
| **SteelSeries** | Arctis 1/7/7+/9/Pro/Pro Wireless、Arctis Nova 3P/5/7/7X/7P/Pro Wireless（`1038:225D` を含む）、Arctis Nova Elite（ベースステーション `1038:2244`）、GameBuds。Aerox 3/5/9 Wireless、Prime Wireless、Rival 3 Wireless（Gen 2）、Rival 650、Rival Pro | メーカー独自の HID レポート |
| **Corsair** | Void / Void Pro / Void Elite / HS70 / HS80 ワイヤレス。Bragi デバイス（Virtuoso、Void V2、HS80 MAX、Slipstream のマウスとキーボード。新しい Slipstream レシーバー `1B1C:2B00` を含む。例: Scimitar Elite SE Wireless） | メーカー独自の HID レポート、Bragi の `GET`（読み取り専用） |
| **Corsair** | Void / Void Pro / Void Elite / HS70 / HS80 ワイヤレス。Bragi デバイス（Virtuoso、Void V2、HS80 MAX、Slipstream のマウスとキーボード。例: Dark Core RGB Pro SE） | メーカー独自の HID レポート、Bragi の `GET`（読み取り専用） |
| **Razer** | ワイヤレスのマウス、キーボード、ドングル。BlackShark V2 HyperSpeed、V2 Pro（2020/2023）、V3 / V3 Pro / V3 X ヘッドセット。2.4 GHz レシーバー（`1532:0550`）の Barracuda X（2022） | Razer のフィーチャーレポートのプロトコル。BlackShark 独自のプロトコル（V3 / V3 Pro / V3 X は 5 分ごとに問い合わせ）。Barracuda X: レシーバー経由で Airoha のバッテリーとケーブルを問い合わせ |
| **Razer** | ワイヤレスのマウス、キーボード、ドングル。BlackShark V2 HyperSpeed、V2 Pro（2020/2023）、V3 / V3 Pro / V3 X ヘッドセット。2.4 GHz レシーバー（`1532:0550` または `1532:0552`）の Barracuda X（2022） | Razer のフィーチャーレポートのプロトコル。BlackShark 独自のプロトコル（V3 / V3 Pro / V3 X は 5 分ごとに問い合わせ）。Barracuda X: レシーバー経由で Airoha のバッテリーとケーブルを問い合わせ |
| **SteelSeries** | Arctis 1/7/7+/9/Pro/Pro Wireless、Arctis Nova 3P/5/7/7X/7P/Pro Wireless、GameBuds。Aerox 3/5/9 Wireless、Prime Wireless、Rival 3 Wireless（Gen 2）、Rival 650、Rival Pro | メーカー独自の HID レポート |
| **SteelSeries** | Arctis 1/7/7+/9/Pro/Pro Wireless、Arctis Nova 3P/5/7/7X/7P/Pro Wireless（`1038:225D` を含む）、GameBuds。Aerox 3/5/9 Wireless、Prime Wireless、Rival 3 Wireless（Gen 2）、Rival 650、Rival Pro | メーカー独自の HID レポート |
| **Corsair** | Void / Void Pro / Void Elite / HS70 / HS80 ワイヤレス。Bragi デバイス（Virtuoso、Void V2、HS80 MAX、Slipstream のマウスとキーボード。新しい Slipstream レシーバー `1B1C:2B00` を含む。例: Scimitar Elite SE Wireless、Dark Core RGB Pro SE）。Sabre V2 Pro Ultralight Wireless（`1B1C:2B2A`） | メーカー独自の HID レポート、Bragi の `GET`（読み取り専用）、Compx の 17 バイトのバッテリープロトコル（読み取り専用） |
| **Cooler Master** | MM712、MM731（2.4 GHz ドングルまたは USB ケーブル） | メーカー独自の HID ステータスレポート（読み取り専用） |
| **HyperX** | Cloud III Wireless、Cloud III S Wireless、Cloud II Wireless（HP、Kingston、DTS）、Cloud II Core Wireless、Cloud Alpha Wireless、Cloud Alpha 2 Wireless、Cloud Flight、Cloud Flight S、Cloud Stinger Core Wireless、Cloud Core Wireless DTS、Pulsefire Haste 2 Core Wireless（2.4 GHz ドングル）、Pulsefire Haste 2 Wireless | メーカー独自の HID レポート |
| **Glorious** | Model O / O- / D / D- Wireless、Model O 2 / D 2 PRO | メーカー独自のフィーチャーレポート |
| **Hitscan** | Hyperlight X、Hyperlight N | メーカー独自のフィーチャーレポート（Glorious と同じプロトコル） |
| **Kysona / Pulsar / ATK (VXE) / Hitscan** | Kysona M600 / Mercury、Pulsar と ATK VXE のワイヤレスマウス（例: VXE X3 Pro、VXE Dragonfly R1 / R1 Pro Max / R1 SE+、ATK F1 Extreme）、Hitscan Hyperlight | チェックサム付きの応答を返す共通のメーカー独自プロトコル |
| **Pulsar X2 V3** | 1K ドングル（`3710:5402`）または USB ケーブル（`3710:3402`）の X2 V3。8K ドングル（`3710:5403`）または USB ケーブル（`3710:3406`）の X2 V3 eS | 64 バイトのメーカー独自フィーチャーレポート、バッテリーレジスター `08 81 01`（読み取り専用） |
| **ATK / VXE NK** | NK mouse NANO ドングル（`373B:1216`）の VXE R1 NK とその他の NearLink マウス | `FF05:0001` 上の ATK BITMOUSE 出力レポート 08（バッテリーと充電） |
| **ATK のヘッドセット** | ATK N9 Pro、N9 Ultra（第 1 世代） | 仮想 COM ポートのプロトコル（ATK のデスクトップアプリは閉じておく必要あり） |
| **G-Wolves** | Fenrir、Fenrir Pro / Max / Asym、HTX、HTS、HSK、HTR、HT-S2、Lycan、WARG、VUK とその 8K ドングル | モデルに応じて Glorious または Kysona のプロトコル |
| **Keychron のマウス** | 2.4 GHz レシーバーの M4 とその他の Keychron マウス。Keychron 4K Link レシーバー（`3434:D038`）の 4K マウス（M4 4K、M3 4K、M3 mini 4K、M6 4K ...）。TurboLink 8K レシーバーの 8K マウス（M5 8K、G6 HE 8K ...）。1K レシーバー（`3434:D030` / `D031`）の旧モデル（M1、M2、M3、M3 mini、M6、M7 ...）。Link-KM レシーバーまたはケーブルの Nape Pro トラックボール | Keychron Launcher のメーカー独自レポート（1K レシーバー: Keychron のデスクトップアプリと同じフィーチャーレポート 51 06。Nape Pro: raw HID A7 31） |
| **CHERRY** | 2.4 GHz ドングル（`046A:00EA`、動作確認済み）または USB ケーブル（`046A:00E3`、動作確認済み）の MX 3.0S Wireless キーボード | `FF1C:0092` 上のメーカー独自 HID 問い合わせ `1A`（読み取り専用）。USB 給電の状態も取得。Bluetooth は Bluetooth 対応でカバー |
| **Arbiter Studio** | Akitsu（`373E:000A` 8K レシーバー、`373E:0009` ケーブル）、Akitsu 3950（`373E:0039` 8K レシーバー、`373E:0038` ケーブル）、Akitsu Medium（`373E:0067` 8K レシーバーと `373E:0066` ケーブル。どちらも動作確認済み） | Arbiter Web HUB の、`FFFF:0000` 上の読み取り専用メーカー独自フィーチャーレポート `0x83`（バッテリーと充電） |
| **LAMZU** | Maya X、Maya、Maya M、Tachi、Inca、Paro、Thorn、Atlantis Mini / OG Champion、Orcus（ケーブル、1K と 4K/8K のドングル） | LAMZU Aurora のメーカー独自フィーチャーレポート |
| **Endgame Gear** | 4K ドングルの OP1w 4k（v1 / v2）、XM2w 4k（v1 / v2）。純正レシーバー（`3367:1961`）の XM2we | メーカー独自フィーチャーレポート `A1`、バッテリーコマンド `B4`（読み取り専用） |
| **ATK のキーボード** | 2.4 GHz レシーバー（`320F:5088`）または USB ケーブル（`320F:5055`）の ATK V75X | Evision 出力レポート `04`、バッテリーコマンド `1A`（ATK HUB より）。レシーバー経由では最短でも 10 分に 1 回だけ問い合わせ |
| **Audeze** | USB ドングル（`3329:4B19`）または USB-C ケーブル（`3329:4B1A`）の Maxwell。Xbox 版と Maxwell 2 の ID は未確認 | メーカー独自レポート `06` / 入力レポート `07`、バッテリー属性 `0CD6`（読み取り専用の問い合わせ 1 回） |
| **NZXT** | ドングル（`1E71:2101`）または USB ケーブル（`1E71:2129`）の Lift Elite Wireless | メーカー独自の読み取り `4E 02 81 .. B0`（NZXT CAM の通信キャプチャーより） |
| **Poly / Plantronics** | BT600 アダプター（`047F:02EE` / `02F7`）経由の Voyager 8200 UC とその他のヘッドセット | レポート `07` の get/set プロトコル、バッテリー項目 `0A 1A`（読み取り専用） |
| **WLMouse** | YING Magnesium（YING 8K レシーバー `36A7:A874`）。Beast X 8K、Beast X Mini / Mini Pro、Beast X Pro、Beast MAX、Sword X 8K（レシーバーまたはケーブル。Beast X 4K は除く）。Beast X V2（8K レシーバー `36A7:A856`） | メーカー独自フィーチャーレポート、ステータスコマンド `0x83`（YING: Glorious と同じプロトコル） |
| **VAXEE** | VAXEE 4K レシーバー（`3057:1002`）のワイヤレスマウス。USB ケーブル（`3057:1011`）の ZYGEN NP-01S V2 Wireless | `FF05:0001` 上の読み取り専用メーカー独自フィーチャーレポート `0E`。バッテリーは 5% 刻み、充電状態も取得（[プロトコルのメモ](docs/vaxee.md)） |
| **Finalmouse** | 2.4 GHz ドングル（`361D:0100`、動作確認済み）の UltralightX。ドングル（`361D:0300` / `0301`、動作確認済み）の Starlight X。マウス本体のケーブル接続では非対応 | `FF00` 上の xpanel のメーカー独自レポート: 読み取り専用の GET の後に *wake/all*（`0xE0`）。xpanel の曲線によるバッテリー電圧、または Starlight X 自身のパーセント、および充電状態 |
| **VAXEE** | VAXEE 4K レシーバー（`3057:1002`）または 8K レシーバー（`3057:2002`。例: NP-01 Ergo Wireless 8K）のワイヤレスマウス。USB ケーブル（`3057:1011`）の ZYGEN NP-01S V2 Wireless | `FF05:0001` 上の読み取り専用メーカー独自フィーチャーレポート `0E`。バッテリーは 5% 刻み、充電状態も取得（[プロトコルのメモ](docs/vaxee.md)） |
| **WLMouse** | YING Magnesium（YING 8K レシーバー `36A7:A874`）。Beast X 8K、Beast X Mini / Mini Pro、Beast X Pro、Beast MAX、Sword X 8K（レシーバーまたはケーブル。Beast X 4K は除く） | メーカー独自フィーチャーレポート、ステータスコマンド `0x83`（YING: Glorious と同じプロトコル） |
| **HECATE** | 同じレシーバーの G5M PRO とその他の HECATE マウス、および USB ケーブル `35BB:D3FA / D3FC / D3FD` | Kysona のプロトコル |
| **Redragon** | Compx ベースのワイヤレスマウス: M916 Pro 1K（動作確認済み）、M913 Impact Elite（トライモード）、G49（レシーバーまたはケーブル） | Kysona のプロトコル（Areson の `25A7` レシーバーは Areson の行に記載） |
| **Taidu (钛度)** | Compx 2.4 GHz レシーバー `3554:F5D5` の TSG808（動作確認済み） | Kysona のプロトコル |
| **Areson (Redragon)** | `25A7:FA07` / `FA08` レシーバーの M915RGB-WL（動作確認済み）、初代 M913 Impact Elite とその他のマウス | 17 バイトの `GetPower` フィーチャーレポート。残量は 10% 刻み、充電フラグあり |
| **Ninjutso** | 1K レシーバー（`1915:AE1C`、動作確認済み）または USB ケーブル（`1915:AE11`、動作確認済み）の Sora V2 | NinjaForce のフィーチャーレポート 0x05、ステータスコマンド 0x15。バッテリー、オンライン状態、充電状態 |
| **Ninjutso** | 1K レシーバー（`1915:AE1C`、動作確認済み）の Sora V2。Ten Air（レシーバー `093A:EB01` と USB ケーブル `093A:E020`、動作確認済み）/ Ten（`093A:EB01` / `E020`、未確認） | NinjaForce のフィーチャーレポート `0x05`（Sora V2 は `0x15`）と `0x06`（Ten / Ten Air は `0x13`/`0x12`/`0x11`） |
| **Sprime** | 2.4 GHz レシーバー（`1915:AC1C` は動作確認済み、`1915:AD8C`）または USB ケーブルの PM1 | 同じフィーチャーレポート 0x05、ステータスコマンド 0x15（Sprime の Web ドライバー sprime.pro より） |
| **AULA** | 2.4 GHz レシーバーの F75 / F87 Pro / F99 ワイヤレスキーボード | レポート 0x13 のフレーム、コマンド 0x4A、合計値のチェックサム（Bluetooth と有線モードは未確認） |
| **DAREU** | `260D:1074` 2.4 GHz レシーバーの EM901X（バッテリーの読み取りは動作確認済み、充電状態の変化は未確認） | バッテリー専用のフィーチャーレポート `08`、コマンド `04`。応答 `09` は別のメーカー独自コレクションに返る。入力 / フィーチャーの組が一意に決まる必要あり。USB ケーブルモードとほかのレシーバー ID は無効 |
| **SONiX キーボード（AJAZZ / AULA / EPOMAKER）** | `05AC:024F` 2.4G ドングルの AJAZZ AK820 MAX（動作確認済み）、EPOMAKER EA75（動作確認済み）、AULA F108 Pro。`0C45:FEFE` ドングルの AJAZZ AK980 V2 | 使用ページ FF60 上のメーカー独自レポート `20 01`、合計値のチェックサム（2.4G モードのみ。充電表示なし） |
| **DAREU** | `260D:1074` 2.4 GHz レシーバーまたは `260D:1090` USB ケーブルの EM901X（バッテリーの読み取りはどちらも動作確認済み。レシーバーでのドック装着 / 取り外し時の充電フラグの変化も動作確認済み） | バッテリー専用のフィーチャーレポート `08`、コマンド `04`。応答 `09` は別のメーカー独自コレクションに返る。プロダクト ID ごとに入力 / フィーチャーの組が一意に決まる必要あり。両方つながっているときは有効な USB の値を優先する。マウスの電源が切れていても、レシーバーはキャッシュした値を返すことがある |
| **SONiX キーボード（AJAZZ / AULA）** | `05AC:024F` 2.4G ドングルの AJAZZ AK820 MAX（動作確認済み）、AULA F108 Pro。`0C45:FEFE` ドングルの AJAZZ AK980 V2 | 使用ページ FF60 上のメーカー独自レポート `20 01`、合計値のチェックサム（2.4G モードのみ） |
| **ZOWIE** | 2.4 GHz レシーバーの EC1/EC2/EC3-CW、DW シリーズ（U2-DW、S2-DW ...）、U2 | コミュニティが解析した読み取り専用のメーカー独自コマンド |
| **Royal Kludge (RK)** | 2.4 GHz ドングル（`2E3C:00A6` / `00E6`）または USB ケーブル（`2E3C:00A5` / `00E5`）の MG6 Pro | RK の Web ドライバーの QiWang 64 バイトフレーム、`GET_BATTER_VOL` の読み取り（パーセント、電圧、充電） |
| **ASUS ROG** | Strix Scope II 96 (RX)、Azoth、Falchion キーボード。Keris、Harpe、Gladius、Chakram、Spatha、Pugio、Strix Impact マウス。Pelta ヘッドセット（2.4 GHz ドングル）。Omni Receiver | ROG の HID バッテリー問い合わせ |
| **Machenike** | `248A:FF4C` 2.4 GHz レシーバーまたは `248A:FF4E` USB ケーブルの L7 Arctic / L7 Mix（どちらも動作確認済み） | 読み取り専用のフィーチャーレポート `51`、ステータスコマンド `06`。バッテリーと充電。[プロトコルのメモ](docs/machenike.md) |
| **MCHOSE** | 2.4 GHz レシーバーまたは USB ケーブルの L7 / L7 Pro / L7 Ultra（L7 Ultra は動作確認済み）、M7 / M7 Ultra、A7 / A7 Ultra、K7 マウス。G3 V2（2.4 GHz レシーバー `3837:4245` と USB ケーブル `3837:418C`） | メーカー独自フィーチャーレポート、反転したペイロード（プロトコルは alexfrih/mchose-linux より）。G3 V2: `FF01:0010` 上の読み取り専用メーカー独自問い合わせ |
| **MSI** | 2.4 GHz ドングル（`0DB0:9E22`）の VERSA 300 ELITE WIRELESS。CLUTCH GM31 Lightweight Wireless（2.4 GHz レシーバー `0DB0:0D3C` は動作確認済み、USB ケーブル `0DB0:0D3B`）と CLUTCH GM41 Lightweight Wireless（レシーバー `0DB0:0D4C` / ケーブル `0DB0:0D4B`。所有者の通信キャプチャーより） | `FF0D:00B0` と `FF00:0001` 上の読み取り専用メーカー独自問い合わせ `0F 20`。バッテリーと充電フラグは 1 バイトに格納（プロトコルは MSI Center の Gaming Gear モジュールより）。GM41: `FF10:0006` 上で受動的に届く `A0 xx 07 …` レポート |
| **MCHOSE** | 2.4 GHz レシーバーまたは USB ケーブルの L7 / L7 Pro / L7 Ultra（L7 Ultra は動作確認済み）、M7 / M7 Ultra、A7 / A7 Ultra、K7 マウス。A5 V2 Ultra（2.4 GHz レシーバー `3837:100C`、動作確認済み）、K7 Ultra（2.4 GHz レシーバー `3837:1001`、動作確認済み。A7 V2 Ultra+ `3837:100B` も動く見込み、issue 227）。G3 V2（2.4 GHz レシーバー `3837:4245` と USB ケーブル `3837:418C`） | メーカー独自フィーチャーレポート、反転したペイロード（プロトコルは alexfrih/mchose-linux より）。Realtek の `3837` ドングルは同じ問い合わせに、vid フィールドを `41E4`（A5 V2 Ultra）または `3837`（K7 Ultra）にして応答する。G3 V2: `FF01:0010` 上の読み取り専用メーカー独自問い合わせ |
| **MCHOSE** | 2.4 GHz レシーバーまたは USB ケーブルの L7 / L7 Pro / L7 Ultra（L7 Ultra は動作確認済み）、M7 / M7 Ultra、A7 / A7 Ultra、K7 マウス。G3 V2（2.4 GHz レシーバー `3837:4245` と USB ケーブル `3837:418C`）。2.4 GHz レシーバー `3837:1014` の K7 V2 Ultra+（動作確認済み。新ファミリーのほかのレシーバー ID `1018`、`1016`、`102C`、`102D` は未確認） | メーカー独自フィーチャーレポート、反転したペイロード（プロトコルは alexfrih/mchose-linux より）。G3 V2: `FF01:0010` 上の読み取り専用メーカー独自問い合わせ。K7 V2 Ultra+: `FF01:0001` 上の 64 バイトのレポート `0x4D`、デバイス情報コマンド `0x0900`（プロトコルは M HUB の Web ドライバーより） |
| **MCHOSE のヘッドセット** | 2.4 GHz ドングル（`3837:6011`、動作確認済み）の V9 Pro 2 | `FF07:0222` 上の M HUB の読み取り専用 "MC" バッテリーフレーム（レポート `0x55`、サブコマンド `0x0B`）。バッテリーと充電フラグは 1 バイトに格納（プロトコルは M HUB の Web ドライバーより） |
| **AULA / MCHOSE のキーボード** | 2.4 GHz レシーバー（`3554:FA09`、`41E4:2001`）の AULA F75 / F87 Pro / F99、MCHOSE K99 V2、G75 Pro、X75 とその他の M HUB キーボード | レポート 0x13 のフレーム、コマンド 0x4A（MCHOSE のモデルは M HUB と同じくコマンド 0x05 で判別）。Bluetooth と有線モードは非対応 |
| **AULA HERO 68 Air** | 8K Wireless Receiver（`372E:106C`）の HERO 68 Air | 使用ページ FF60 上の、応答確認付き 20 バイトフレーム（1 メッセージにつきデータフレーム 4 つと末尾フレーム 1 つ）、読み取り専用のバッテリーコマンド 0x87、残量の後ろに充電フラグ 0x10。Bluetooth と有線モードは非対応 |
| **ASUS ROG** | Strix Scope II 96 (RX)、Azoth、Falchion キーボード。Keris、Harpe、Gladius、Chakram、Spatha、Pugio、Strix Impact マウス。Omni Receiver | ROG の HID バッテリー問い合わせ |
| **ZOWIE** | EC1/EC2/EC3-CW と DW シリーズ（U2-DW、S2-DW ...） | コミュニティが解析した読み取り専用のメーカー独自コマンド |
| **Rapoo VT** | VT3 Max Gen 2（動作確認済み）。同じステータスインターフェースを持つ、その他の Nordic 54L 搭載 VT マウス。旧 VT3 Pro（試験的） | `FF00:0002` 上で受動的に届く HID ステータスレポート `07`。旧方式の `BB` は VT3 Pro `1215/4415` に限定。レシーバーと USB ケーブル、充電状態あり |
| **Rapoo VT** | VT3 Max Gen 2（動作確認済み）。同じステータスインターフェースを持つ、その他の Nordic 54L 搭載 VT マウス。旧 VT3 Pro（試験的）。VT1 Pro Max（所有者の USB 通信キャプチャーより） | `FF00:0002` 上で受動的に届く HID ステータスレポート `07`。旧方式の `BB` は VT3 Pro `1215/4415` と VT1 Pro Max `1233/4433` に限定。レシーバーと USB ケーブル、充電状態あり |
| **Motospeed / Delux / Ajazz** | Motospeed X6、Delux M900 Pro（Xenta のモデル 30/50。旧 3D）、Delux M800 Pro、Ajazz AJ179 系。3151 レシーバーの AJ159 とその他の AJ シリーズのマウス。AJ139 V2 MC（`A8A5:2255` レシーバー、`A8A4:2255` ケーブル） | メーカー独自レポート（M900 Pro: 受動的に届く Xenta のイベント 40/41。AJ シリーズ: 0xF7 のステータス取得の後、フィーチャーレポート 0x05） |
| **Rapoo VT** | VT3 Max Gen 2（動作確認済み）。VT9 Gen 2（動作確認済み）。同じステータスインターフェースを持つ、その他の Nordic 54L 搭載 VT マウス。旧 VT3 Pro（試験的）。VT1 Pro Max（所有者の USB 通信キャプチャーより） | `FF00:0002` 上で受動的に届く HID ステータスレポート `07`（16 または 19 バイト）。旧方式の `BB` は VT3 Pro `1215/4415` と VT1 Pro Max `1233/4433` に限定。レシーバーと USB ケーブル、充電状態あり |
| **Motospeed / Delux / Ajazz** | Motospeed X6、Delux M900 Pro、Delux M800 Pro、Ajazz AJ179 系。3151 レシーバーの AJ159 とその他の AJ シリーズのマウス。AJ139 V2 MC（`A8A5:2255` レシーバー、`A8A4:2255` ケーブル） | メーカー独自レポート（Delux: 受動的に届くステータス、またはフィーチャーの問い合わせ。AJ シリーズ: 0xF7 のステータス取得の後、フィーチャーレポート 0x05） |
| **Incott** | G23 V2 / G24（`093A:522C` レシーバー、`093A:622C` ケーブル） | 読み取り専用のステータスフィーチャーレポート 09 |
| **Attack Shark などの中国ブランド** | Rongyuan のレシーバー（81 モデル: Attack Shark R3、K86、X82 PRO HE、Ajazz のキーボード、一部の MSI など。Bluetooth 接続の K86 はキーボードとして表示）。Xenta のレシーバー（Attack Shark X6 / R1、X11、X3 Max、V3 Pro、V6）。Semico 1A2C のキーボード（`1A2C:8FFF` ドングルの Attack Shark X98 は動作確認済み、`1A2C:A034` ケーブルも。`1A2C:8FFF` / `1A2C:A036` の AJAZZ AK820 Max Plus） | Rongyuan のステータスレポート。Xenta は受動的に届くブロードキャスト。Semico は読み取り専用の `0x0E` ステータス問い合わせ（`FF02:0002` 上の `AA 55 CC 33`。X98 はバッテリー駆動中も充電中も `state=1` を返すため、充電フラグは使わない） |
| **Wraith** | W1 / W1 Freestyle（`093A:522C` レシーバー、`093A:622C` ケーブル。Incott と ID が同じで、モデルコードで区別する） | 全ボタンに対するボタンごとの読み取り専用リード `86`（フィーチャーレポート 09）の後、送られてくるステータス入力レポート 09 |
| **Fantech** | Helios Go XD5（有線 `25A7:FA7B`、2.4 GHz ドングル `25A7:FA7C`） | メーカー独自フィーチャーレポート `08`、コマンド `04`、合計が `0x55` になるチェックサム |
| **Sony** | DualShock 4、DualSense、DualSense Edge（USB、Bluetooth、ワイヤレスアダプター）。INZONE H9 II と H5 ヘッドセット。INZONE Buds（USB-C ドングル） | 入力レポート。INZONE 独自のプロトコル |
| **Fractal Design** | 2.4 GHz ドングルまたは USB-C ケーブルの Scape ヘッドセット | Fractal の Web アプリ Adjust Pro のメーカー独自問い合わせ `GET_DEVICE_STATE`（使用ページ FF00） |
| **Jabra** | Jabra Link 380a / 380c / 390 ドングル（USB-A と USB-C、UC 版と MS 版: Evolve2 / Evolve3 など）経由のヘッドセット。名前はヘッドセットから読み取る | 使用ページ FF00 上の GNP ステータス問い合わせ（class 12 / op 02） |
| **Flydigi** | Vader 5 Pro / 黑武士 5 Pro（`37D7:2401`）。2.4 GHz レシーバーまたは USB | `FFA0:0001` 上のメーカー独自 HID 情報問い合わせ。0〜5 の残量段階を 20% 刻みで 0〜100% に変換し、充電状態も取得。Space Station サービスは不要 |
| **GameSir** | 2.4 GHz レシーバーの Nova Lite、Nova 2、Nova 2 Lite。USB の Nova 2 Lite。Xbox（GIP）モードの G7 Pro（動作確認済み: ゼンレスゾーンゼロ エディション、レシーバー `3537:105E`）とその他の GameSir パッド。Cyclone 2（XInput モード、レシーバーまたはケーブル） | メーカー独自のデバイス情報問い合わせ（使用ページ FF7A）。Xbox モードでは Windows.Gaming.Input のバッテリー情報（実際の %）。Cyclone 2: メーカー独自のバッテリー要求（使用ページ FFF0） |
| **8BitDo** | D-input モード（`2DC8:6012`: B を押しながら電源を入れる）の Ultimate 2 Wireless。2.4 GHz ドングル、USB ケーブル、Bluetooth。ファームウェア 1.03 以降。X-input モード（`2DC8:310B`）ではドングルが残量を報告しない | ゲームパッドの入力レポート `01` のバッテリーバイト（読み取り専用）、充電状態あり |
| **BEITONG** | 2.4 GHz レシーバー（`20BC:5128`、XInput モード、動作確認済み）の KP20 / BTP-KP20。BEITONG iControl は不要 | 使用ページ `00FF` 上のメーカー独自の "get base info" 問い合わせ（レポート `02`、ニブル単位でスクランブルされたペイロード）、充電状態あり |
| **8BitDo** | Ultimate 2 Wireless（X-input `2DC8:310B` は 2.4 GHz ドングルで動作確認済み、D-input `2DC8:6012` はファームウェア 1.03 以降）、Ultimate 2C Wireless、Ultimate 3-mode、Ultimate 2.4G、Ultimate Bluetooth、Pro 3、Pro 2、SN30 Pro、SF30 Pro | メーカー独自の HID ステータス問い合わせ（`FF7A`/`FFA0`）と SDL のゲームパッド入力レポート `01`/`04`、充電状態あり |
| **Samsung** | Galaxy Buds、Buds+、Buds Live、Buds Pro、Buds2、Buds2 Pro、Buds FE、Buds Core、Buds3 / Buds3 Pro / Buds3 FE（Bluetooth） | イヤホンが Samsung の RFCOMM（SPP）サービスで送ってくるステータスフレーム（読み取り専用）。トレイには残量の少ない側のイヤホンを表示し、ツールチップに左・右・ケースを表示。Galaxy Buds アプリは閉じておく必要あり |
| **Sony** | DualShock 4、DualSense、DualSense Edge（USB、Bluetooth、ワイヤレスアダプター）。INZONE H9 II と H5 ヘッドセット | 入力レポート。INZONE 独自のプロトコル |
| **MOONDROP** | 2.4 GHz ドングル（`35D8:0133`）の GM01 Pro ヘッドセット。USB ケーブルでは、最後の残量のまま充電中として表示 | レポート `4B` 上の WalkPlay のメーカー独自読み取りコマンド（読み取り専用） |
| **JBL** | Quantum 650 Wireless（動作確認済み、2.4 GHz ドングル）。Quantum 520、650X、850、950、950X Wireless（ドングルまたは USB ケーブル、同じプロトコル、未確認） | バッテリー機能に対する JBL の "HIDV3" デバイス情報問い合わせ（使用ページ FF12）、充電状態あり |
| **JBL** | Quantum 350 Wireless（Windows で `0ECB:206B` 2.4 GHz レシーバーにより動作確認済み） | ワイヤレス接続とバッテリー残量の HIDV1 フィーチャーレポート |
| **GameSir** | 2.4 GHz レシーバーの Nova Lite、Nova 2、Nova 2 Lite。USB の Nova 2 Lite | メーカー独自のデバイス情報問い合わせ（使用ページ FF7A） |
| **Xbox** | Xbox ワイヤレスアダプター、USB、Bluetooth で接続したコントローラー。コントローラーに挿したヘッドセット | Windows.Gaming.Input のバッテリー情報（実際の %）、XInput へのフォールバック |
| **Switch Pro 互換** | `057E:2009` として認識されるコントローラー（動作確認済み: Switch モードで 2.4 GHz レシーバー経由の GameSir Tarantula Pro） | Steam Input などのホストがフルレポートを有効にした後、HID レポート `0x30` から 5 段階の残量 |
| **Apple AirPods / Beats** | AirPods Max（動作確認済み、`200A` Lightning と `201F` USB-C）、AirPods Pro 3（動作確認済み、`2027`）、AirPods Pro 1 / 2、AirPods 1〜5、Beats のヘッドホン / イヤホン | BLE の "proximity pairing"（`0x07`）ブロードキャスト（AirPods Max と Beats のヘッドホンはバッテリー 1 つ、イヤホンは左・右・ケース。10% 刻み、充電状態あり）を、ペアリング済みのモデルと照合 |
| **スマートフォン（スマホ連携）** | Microsoft のスマホ連携（Phone Link）でつないだ Android スマートフォン。Wi-Fi または Bluetooth（動作確認済み: Nothing Phone (4a) Pro） | スマホ連携が Windows 11 のスタートメニューのカード用に書き出す情報（`StartMenuCompanion.json`）からバッテリーを取得。Bluetooth は不要 |
| **Darmoshark** | Windows で 2.4 GHz レシーバー（`248A:FF30`）の M3 | マウスの識別とバッテリーの HID フィーチャーレポート |
| **Alienware** | 2.4 GHz ドングル（`413C:A515`、動作確認済み）の AW920H ヘッドセット。Bluetooth 接続は Bluetooth の行でカバー | `FF13:0001` 上のメーカー独自問い合わせ `06 C0 0A`、XOR チェックサム付きの応答レポート `07`。残量、充電、危険レベルの各フィールドは Alienware Command Center の AW920H プラグインの解析に従う |
| **Niceboy** | 2.4 GHz レシーバー（`248A:FA02`、動作確認済み）の MW400 | 読み取り専用のレポート `05` による問い合わせ `24 FA 48`。バッテリー電圧をメーカーアプリの表で 10% 刻みに変換、充電フラグあり |
| **Bluetooth** | *設定 → Bluetooth とデバイス* にバッテリーが表示されるもの全般（イヤホン、ヘッドホン、BLE のマウスやキーボード） | Windows のデバイスプロパティ |
| **汎用 HID** | 標準の HID *Battery Strength* 使用法を報告するデバイス | HID 使用ページ 0x06 / 0x85 |
| **HeadsetControl** | [HeadsetControl が対応するすべてのヘッドセット](https://github.com/Sapd/HeadsetControl#supported-headsets)（Audeze、Jabra、Sony INZONE、新しめの Logitech など） | 同梱。`headsetcontrol -o json` を実行 |
| **MAONO PD200W** | 2.4 GHz レシーバー（352F:040E） | バッテリー残量。実機で動作確認済み |


**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）、Finalmouse UltralightX（ドングル `361D:0100`）と Finalmouse Starlight X（専用ドングル）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）、HyperX Cloud Stinger Core Wireless（PlayStation 用レシーバー `0951:1713`。充電は未確認）と HyperX Cloud Core Wireless DTS（レシーバー `0951:173F`。満充電時の値は未確認）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、MSI VERSA 300 ELITE WIRELESS（ドングル `0DB0:9E22`。充電とスリープの扱いは未確認）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）と HyperX Cloud Stinger Core Wireless（PlayStation 用レシーバー `0951:1713`。充電は未確認）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、MSI VERSA 300 ELITE WIRELESS（ドングル `0DB0:9E22`。充電とスリープの扱いは未確認）、MSI Clutch GM31 Lightweight Wireless（レシーバー `0DB0:0D3C`。GM41 は所有者の通信キャプチャーをもとに同じドライバーを使用）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、HyperX Pulsefire Haste 2 Core Wireless（ドングル `03F0:0AB5`。Haste 2 Wireless のドングルは未確認）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、AirPods Max（Bluetooth、モデル `200A`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、AULA HERO 68 Air（8K Wireless Receiver `372E:106C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）、Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）と Ninjutso Ten Air（レシーバー `093A:EB01` と USB ケーブル `093A:E020`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
ほかにも実機で動作確認済み: Machenike L7 Arctic / L7 Mix（`248A:FF4C` レシーバーと `248A:FF4E` ケーブル）。充電と、ケーブル / レシーバーの重複表示の抑制も含みます。Bluetooth と、バッテリー低下 / 満充電の境界は実機で確認していません。
ほかにも実機で動作確認済み: MCHOSE V9 Pro 2（`3837:6011` ドングル）。バッテリー残量の読み取りのみ確認、充電とスリープは未確認。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、MCHOSE K7 Ultra（レシーバー `3837:1001`）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、MCHOSE K7 V2 Ultra+（レシーバー `3837:1014`。充電状態は未確認）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）。
ほかにも実機で動作確認済み: `05AC:024F` 2.4 GHz レシーバーの EPOMAKER EA75。[PR #60](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/pull/60) の既存の SONiX ドライバーを使用。バッテリー残量、レシーバーの再接続、電源投入時の復帰を確認しました。充電表示と有線でのバッテリー報告はこのドライバーでは非対応で、Bluetooth でのバッテリー報告は未確認です。USB 給電をつなぐと報告されるパーセントが 100% に跳ねることがあり、充電の目安としては当てになりません。

**実機で動作確認済み:** Glorious Model O Wireless、HyperX Cloud III Wireless、Cooler Master MM712（ドングル）、Rapoo VT3 Max Gen 2（レシーバー `24AE:1417` と USB ケーブル `24AE:4617`。ほかの Rapoo モデルは未確認、[Rapoo のプロトコルのメモ](docs/rapoo.md)を参照）Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Redragon M916 Pro 1K（レシーバー `3554:F55D`）、Taidu TSG808（レシーバー `3554:F5D5`）、Redragon M915RGB-WL（レシーバー `25A7:FA07`。ほかの Areson モデルは未確認、[Areson のプロトコルのメモ](docs/areson.md)を参照）、SteelSeries Rival 650 Wireless（レシーバー `1038:1726` と USB ケーブル `1038:172B`）、HECATE G5M PRO（レシーバー `35BB:D3FB`）、WLMouse YING Magnesium（8K レシーバー `36A7:A874`）、ATK N9 Ultra（レシーバー `373B:1204`）、Corsair Scimitar Elite SE Wireless（Slipstream レシーバー `1B1C:2B00`）、DAREU EM901X（レシーバー `260D:1074`。充電とスリープ / 復帰は未確認）、Link 390 経由の Jabra Evolve3 75（`0B0E:2E51`）、MCHOSE G3 V2（レシーバー `3837:4245` と USB ケーブル `3837:418C`）、MCHOSE K7 V2 Ultra+（レシーバー `3837:1014`。充電状態は未確認）、AJAZZ AK820 MAX（ドングル `05AC:024F`）、AirPods Pro 3（Bluetooth、モデル `2027`）、Sprime PM1（レシーバー `1915:AC1C`）、MOONDROP GM01 Pro（ドングル `35D8:0133`）、SteelSeries Arctis Nova Pro Wireless（ベースステーション `1038:225D`。バッテリーの読み取りは確認済み、充電と電源状態の変化は未確認）、Delux M800 Pro（レシーバー `248A:5B2F`）、Razer Barracuda X（2022）（レシーバー `1532:0550`。バッテリー残量の読み取りのみ確認、充電状態の変化は未確認）、Razer BlackShark V3 X（HyperSpeed ドングル `1532:057D`）、Fantech Helios Go XD5（ドングル `25A7:FA7C`）と Corsair Dark Core RGB Pro SE（Slipstream レシーバー `1B1C:1BDC`）、Corsair Sabre V2 Pro Ultralight（2.4 GHz レシーバー `1B1C:2B2A`。バッテリーの読み取りは確認済み）。
**プロトコルの資料やほかのプロジェクトをもとに実装し、まだ動作確認していないもの:** 上記以外のすべて。これらのデバイスをお持ちの方は、[issue を作成](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/issues)して動作したかどうかを教えてください。

## インストール

[![Latest version](https://img.shields.io/github/v/release/krisgfx9/Wireless-Device-Battery-Monitor?label=latest%20version&style=for-the-badge)](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/releases/latest)

1. [最新リリース](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor/releases/latest)から **`WirelessBattery-Setup-<version>.exe`** をダウンロードします。
2. 実行して画面に従って進めます。**管理者権限は不要**で、**ほかに何もインストールする必要はありません**: ランタイムもドライバーもメーカーのアプリも不要です。HeadsetControl は同梱されています。

インストーラーはスタートメニューの項目とアンインストーラー（*設定 → アプリ*）を追加し、サインイン時にアプリを起動するよう設定することもできます。インストーラーを使いたくない場合は、`WirelessBattery-<version>-portable.zip` をダウンロードして好きな場所に展開し、`WirelessBattery.exe` を実行してください。

**注意:**
- **SmartScreen の警告:** exe にコード署名がないため、Windows が「Windows によって PC が保護されました」と表示することがあります。*詳細情報 → 実行* をクリックするか、自分でビルドしてください。
- **Windows 11 でのトレイアイコン表示:** 新しいトレイアイコンは `^` の隠れたアイコンの中に入ります。タスクバーにドラッグするか、*設定 → 個人用設定 → タスクバー → その他のシステムトレイアイコン* で有効にしてください。
- **特定のデバイスにアプリを触らせない:** アプリの実行中にデバイスの動作がおかしくなる場合は、`HKCU\Software\WirelessBattery` のレジストリ文字列 `IgnoreDevices` に `VID:PID` の組として登録します（16 進、カンマ区切り。例: `28BD:0947, 1234:ABCD`。ID は `--dump` で確認できます）。登録したデバイスはアプリが一切開かなくなります。ペンタブレットは自動で除外されます。

<a id="command-line"></a>
## コマンドライン

```
WirelessBattery.exe --list     # すべてのデバイスとバッテリー残量を出力して終了
WirelessBattery.exe --dump     # すべての HID コレクション、開けなかった HID デバイス、すべての USB デバイス（HID インター
                               # フェースがないものも）、Bluetooth デバイス。%TEMP%\WirelessBattery-dump.txt にも保存
WirelessBattery.exe --report   # 「デバイスのサポートをリクエスト」ウィンドウを開く
WirelessBattery.exe --demo     # 実際のデバイスの代わりに全ブランドのサンプルを表示（スクリーンショット、色の確認用）
WirelessBattery.exe --quit     # 実行中のアプリを終了
```

**デバイスが表示されない場合:** ウィジェットまたはトレイアイコンを右クリックし、**デバイスのサポートをリクエスト...** を選びます。デバイスを選び、送信される内容（デバイス名、種類、USB/HID の ID とインターフェース構成、任意で入力した名前とメモが、そのまま表示されます）を確認して **送信** をクリックします。送信内容は [krisgfx.com/tools](https://krisgfx.com/tools/#requested) の公開一覧に載り、GitHub の issue が作成または更新されます。**完全なレポートをコピー** を押すと、issue 用に `--dump` の全文がクリップボードにコピーされます。アプリがインターネットに接続するのはこのウィンドウだけで、それも「送信」をクリックしたときだけです。

<a id="build"></a>
## ビルド

[MinGW-w64](https://www.mingw-w64.org/) が必要です。たとえば [MSYS2](https://www.msys2.org/) から入手できます（`pacman -S mingw-w64-x86_64-gcc make`）。

```
make            # MSYS2 / make が使えるシェル
build.bat       # g++ と windres に PATH が通った通常の cmd
```

インストーラーとポータブル版の zip を作るには、[Inno Setup](https://jrsoftware.org/isinfo.php) をインストールして `powershell -File installer\build-installer.ps1 -Version 1.0.0` を実行します。固定されたバージョンの HeadsetControl をダウンロードし、チェックサムを検証します。GitHub Actions はこれをすべて自動で行います: `v1.0.0` のようなタグをプッシュすると、インストーラー、ポータブル版の zip、HeadsetControl のソースコード（GPL ライセンスの要件）を含むリリースが公開されます。

`WirelessBattery.exe` 単体でも動作します。隣に（または `PATH` 上に）`headsetcontrol.exe` がない場合は、追加のヘッドセットが使えなくなるだけです。

## Linux（試験的）

Windows アプリと並んで Linux 版のビルドもあります。同じメーカー別ドライバーを、hidraw ベースの HID バックエンドと GTK4 の StatusNotifierItem によるトレイアイコンで使います。Windows のコードの動作は変わりません。
Linux 専用のファイルはすべて `linux/` と `src/linux/` にあり、`build-linux.sh` でビルドします（Windows は引き続き `build.bat` を使います）。

| | Fedora | Ubuntu / Debian |
|---|---|---|
| コンパイラーと make | `sudo dnf install gcc-c++ make` | `sudo apt install g++ make` |
| GTK4 + Cairo | `sudo dnf install gtk4-devel cairo-devel` | `sudo apt install libgtk-4-dev libcairo2-dev` |

追加の HID ライブラリは不要です（hidraw を直接使います）。

```sh
./build-linux.sh
./build-linux.sh test         # HID レポートディスクリプターのパーサーの単体テスト
./wireless-battery --list     # 検出した残量を出力して終了
./wireless-battery --dump     # HID コレクションを一覧表示
./wireless-battery --quit     # 実行中のトレイアプリを終了
```

HID にアクセスするには udev ルールが必要です。ないとアプリは起動してもデバイスを見つけられません:

```sh
sudo cp linux/99-wireless-battery.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
# 一度ログアウトして、ログインし直す
```

トレイアイコンは KDE Plasma ではそのまま動きます。GNOME では `gnome-shell-extension-appindicator` などの AppIndicator ホストが必要です。ランチャーを使う場合は `linux/wireless-battery.desktop` を使います（これと `linux/wireless-battery.svg`、実行ファイルを `~/.local/` にインストールします）。

フェーズ 1 では Logitech、Razer、SteelSeries、Corsair、HyperX、PlayStation、Cooler Master、Glorious、Finalmouse と、共通の Kysona/Pulsar/ATK/G-Wolves プロトコルに対応しています。Bluetooth/UPower へのフォールバック、HeadsetControl、残りのメーカーは今後のフェーズで予定しています。

## 制限事項

- **メインモニターのみ:** タスクバーのウィジェットはメインモニターのタスクバーに置かれます。
- **混み合ったタスクバー:** 中央寄せの Windows 11 タスクバーがアプリのボタンでいっぱいになると、ボタンがウィジェットまで届くことがあります。Windows 10 ではタスクボタンの領域が自動で狭められます。
- **スマートフォン:** スマホ連携がスタートメニューのカード用に書き出すファイルから読み取ります。これは公開された API ではないため、スマホ連携の更新で変わる可能性があります。スマホ連携が接続中と報告している間だけ表示され、3 時間より古いカードの情報は薄く表示されます。充電状態は取得できません。
- **スリープ中のデバイス:** スリープ中のデバイスは応答しないことがあります。その場合は最後の値を薄く表示し続けます。Logitech のレシーバーはスリープ中のデバイスを接続から外すため、最後の値を 30 分間保持します。
- **Keychron のキーボード:** バッテリーを報告するのは Bluetooth 接続のときだけです（Bluetooth 対応経由で表示）。2.4 GHz レシーバー経由ではファームウェアが公開していません。Keychron のマウスには対応しています。
- **Baseus AeQur GH02 ヘッドセット:** 2.4 GHz ドングル（`10D6:4802`、Actions のチップ）が運ぶのは音声、メディアキー、チップのファームウェア更新用チャンネルだけで、バッテリーは含まれません。残量を見るにはヘッドセットを Bluetooth で接続してください（Windows が残量を報告すれば Bluetooth 対応経由で表示されます）。
- **Rapoo:** 対応する VT マウスはステータスを自分から送ってくるため、更新は該当インターフェースごとに最大 4 秒待つことがあります。スリープ中のマウスは、最大 30 分間最後の値のまま薄く表示されることがあります。対応しているのは Nordic 54L のレポート `07` と旧 VT3 Pro の `BB` です。CH584 のレポート `08`、オフィス向けの MT/M シリーズのマウス、その他のファームウェアのプロトコルには、このドライバーは対応していません。
- **Rapoo:** 対応する VT マウスはステータスを自分から送ってくるため、更新は該当インターフェースごとに最大 4 秒待つことがあります。スリープ中のマウスは、最大 30 分間最後の値のまま薄く表示されることがあります。対応しているのは Nordic 54L のレポート `07` と旧方式の `BB`（VT3 Pro、VT1 Pro Max）です。CH584 のレポート `08`、オフィス向けの MT/M シリーズのマウス、その他のファームウェアのプロトコルには、このドライバーは対応していません。
- **Flydigi:** このドライバーの対象は Vader 5 Pro だけで、Bluetooth とほかの Flydigi モデルには対応していません。パーセントは大まかな残量段階を表します。実装は SDL と Windows でのハードウェアのトレースに基づいており、手元の実機での検証はまだです。
- **未対応:** VERSA 300 ELITE と CLUTCH GM31 / GM41 以外の MSI のワイヤレスマウス、MSI のワイヤレスキーボード、Razer Kraken ヘッドセット、`1532:0550` の Barracuda X（2022）以外の Barracuda モデル、HyperX Pulsefire マウス、Xbox アダプター経由の Xbox Wireless Headset: これらはバッテリーのプロトコルが公開されていません。Xbox Wireless Headset は Bluetooth なら動作します。対応を追加するには、所有者による USB の通信キャプチャー（CONTRIBUTING.md 参照）が必要です。
- **未対応:** MSI のワイヤレスマウスとキーボード、Razer Kraken ヘッドセット、`1532:0550` の Barracuda X（2022）以外の Barracuda モデル、その他の HyperX Pulsefire マウス、Xbox アダプター経由の Xbox Wireless Headset: これらはバッテリーのプロトコルが公開されていません。Xbox Wireless Headset は Bluetooth なら動作します。対応を追加するには、所有者による USB の通信キャプチャー（CONTRIBUTING.md 参照）が必要です。
- **その他のデバイス:** 一部の 2.4 GHz デバイスは公開されていないプロトコルを使っており、まだ対応していません。対応の追加に協力する方法は [CONTRIBUTING.md](CONTRIBUTING.md) を参照してください。

## 仕組み

[`src/drivers/`](src/drivers) にある各メーカー別ドライバーは、USB のベンダー ID とプロダクト ID で自分のデバイスを認識し、読み取り専用のバッテリー問い合わせだけを送ります。不明なデバイスに書き込むことは一切ありません。汎用のフォールバック（HID のバッテリー使用法、Bluetooth、XInput、HeadsetControl）は、どのメーカー別ドライバーも扱わなかったデバイスだけを調べます。

タスクバーのウィジェットは `Shell_TrayWnd` のレイヤードな子ウィンドウで、`TrayNotifyWnd` の左に置かれます。エクスプローラーが再起動した場合は作り直されます。

<a id="translations"></a>
## 翻訳

各言語は [`lang/`](lang) にあるプレーンな UTF-8 のテキストファイルです。左側が英語、右側が訳文です。

```
@code = it
@name = Italiano
Refresh now = Aggiorna ora
{name} is at {percent}% = {name} è al {percent}%
```

- **自分の言語をすぐに使う:** メニューで *言語 → 自分の言語を追加...* を選びます。`%APPDATA%\WirelessBattery\lang` が開き、すべてのフレーズが並んだ `_template.txt` があります。これを `it.txt` などにコピーし、`@code`、`@name`、訳文を書き込むと、その言語がメニューに表示されます（再起動は不要）。組み込みの言語と同じ `@code` のファイルをここに置くと、その訳を置き換えるので、手元で 1 単語だけ直すこともできます。
- **みんなと共有する:** ファイルを [`lang/`](lang) へのプルリクエストとして送ってください。ビルドはそのフォルダーのファイルをすべて自動で含めるので、コードの変更は不要です。
- `{placeholders}` はそのまま残し、右から左に書く文字の言語には `@rtl = 1` を追加してください。空のままのフレーズは英語で表示されるので、一部だけの翻訳でも問題ありません。
- `--list` と `--dump` の出力は、あえて英語のままにしています: GitHub の issue に貼り付けるためです。

## クレジット

アプリのアイコンは [nik-txt](https://github.com/nik-txt) によるものです（[`res/app.svg`](res/app.svg)）。

プロトコルは、次のプロジェクトの調査結果に基づいています:

- [HeadsetControl の Astro ドライバー](https://github.com/Sapd/HeadsetControl/blob/master/lib/devices/logitech_astro_a50.hpp)、[eh-fifty](https://github.com/tdryer/eh-fifty)、[AstroBar](https://github.com/nichtlegacy/AstroBar): Astro A50 X / Gen 5 / Gen 4 / Gen 3 / A20 のバッテリープロトコル

- [mouse-battery-monitor](https://github.com/stuffz/mouse-battery-monitor) (stuffz): VAXEE のバッテリーと充電のコマンド（[プロトコルの資料](https://github.com/stuffz/mouse-battery-monitor/blob/main/docs/VAXEE.md)）

- [HeadsetControl](https://github.com/Sapd/HeadsetControl): SteelSeries、Corsair、HyperX、Logitech、Sony INZONE のヘッドセット
- [inzone-buds-battery-tray](https://github.com/kinako19/inzone-buds-battery-tray)（kinako19）と [inzone-buds-battery-tray](https://github.com/takamachi66/inzone-buds-battery-tray)（takamachi66）: Sony INZONE Buds
- [OpenRazer](https://github.com/openrazer/openrazer): Razer
- [Solaar](https://github.com/pwr-Solaar/Solaar) と Logitech の HID++ 2.0 の資料: Logitech
- [g435-battery-percentage](https://github.com/portyporty/g435-battery-percentage) と [logitech-g435-battery](https://github.com/deddroid/logitech-g435-battery): Logitech G435（`0ADF` ドングル）
- [rivalcfg](https://github.com/flozz/rivalcfg): SteelSeries のマウス（Rival Pro はプルリクエスト #294 より）
- [glorious-indicator](https://github.com/ikajdan/glorious-indicator) と [glorious-ctl](https://github.com/louis4craft/glorious-ctl): Glorious
- Hitscan の Web 設定ツール（[control.hitscan.com](https://control.hitscan.com)）: Hitscan
- Linux `hid-kysona`（Lode Willems）: Kysona、Pulsar、ATK
- ATK の Web 設定ツール（[hub.atk.pro](https://hub.atk.pro)）: ATK のマウスと N9 Pro / N9 Ultra ヘッドセット
- [PulsarBattery](https://github.com/darthsoup/PulsarBattery): Pulsar X2 V3 / X2 V3 eS
- ATK の Web 設定ツール（[hub.atk.pro](https://hub.atk.pro)）: ATK のマウスと N9 Pro ヘッドセット
- [HaloBattery](https://github.com/HeyOkay/HaloBattery) の PR #350 と [mouse-battery](https://github.com/qwr79/mouse-battery): ATK / VXE の NK NANO ドングル
- [HaloBattery](https://github.com/HeyOkay/HaloBattery)（MIT）: Audeze Maxwell、NZXT Lift Elite、Poly BT600、Razer Barracuda Pro、SteelSeries Arctis Nova Elite、ATK V75X、Endgame Gear XM2we。各プロバイダーから移植（各ドライバーに出典を記載）
- G-Wolves の Web ドライバー（[mouse.xyz](https://mouse.xyz)）: G-Wolves の各モデルとそのプロトコル
- [BatteryWatch](https://github.com/B1Chat/BatteryWatch): 2.4 GHz ドングルの CHERRY キーボード（フレーム形式とバッテリー問い合わせ）
- Keychron Launcher（[launcher.keychron.com](https://launcher.keychron.com)）: Keychron のマウス
- [NinjaForce](https://www.ninjaforce.co/) と [ninjutso-battery-tray](https://github.com/DrStopor/ninjutso-battery-tray): Ninjutso Ten / Ten Air のフィーチャー問い合わせ
- [nape_pro](https://github.com/nvalis/nape_pro) と [KeychronNapeBatteryWidget](https://github.com/gtun/KeychronNapeBatteryWidget): Link-KM レシーバーの Keychron Nape Pro
- LAMZU Aurora（[lamzu.net](https://www.lamzu.net)）: LAMZU のマウス
- [vole](https://github.com/johanneszab/vole) と [Endgame_Gear_Web_Configurator](https://github.com/Janlhin/Endgame_Gear_Web_Configurator): Endgame Gear の 4K マウス
- [mouse-gauge](https://github.com/djnawara/mouse-gauge) と [HaloBattery](https://github.com/Waturus/HaloBattery): WLMouse
- [OpenMouse mouse-protocol](https://github.com/OpenMouse-Project/mouse-protocol) と [FinalmousePollingRateSwitcher](https://github.com/xBambooz/FinalmousePollingRateSwitcher): Finalmouse UltralightX / Starlight X（Finalmouse の xpanel より）
- [redragon-battery-omarchy](https://github.com/EliottV17/redragon-battery-omarchy) と [g49-web-control](https://github.com/pingpingjinping/g49-web-control): Redragon の ID
- [m913-ctl](https://github.com/Qehbr/m913-ctl) と [redragon-m913-battery-tray](https://github.com/Doomguy-BFG9000/redragon-m913-battery-tray): Areson `25A7` のフレーム構成と `GetPower` コマンド
- [peripheral-battery-tray](https://github.com/SteveWang92/peripheral-battery-tray) / [G-Helper](https://github.com/seerge/g-helper): ASUS ROG
- [peripheral-battery-tray](https://github.com/SteveWang92/peripheral-battery-tray) / [G-Helper](https://github.com/seerge/g-helper): ASUS ROG。[pelta-control](https://github.com/jimm0thy/pelta-control) / [BatteryWatch](https://github.com/B1Chat/BatteryWatch): ROG Pelta
- [zowie-battery](https://github.com/yleshchuk/zowie-battery) と [zowie-battery-tray](https://github.com/IgnacioBarb/zowie-battery-tray): ZOWIE EC-CW と DW
- RK の Web ドライバー（[drive.rkgaming.com](https://drive.rkgaming.com)）: Royal Kludge MG6 Pro
- [MCHOSE-Monitor](https://github.com/Jstdi001/MCHOSE-Monitor): MCHOSE G3 V2
- [LGSTrayBattery-MotospeedX6](https://github.com/Jacobz888/LGSTrayBattery-MotospeedX6)、[omarchy-delux-m900](https://github.com/AeonArcHQ/omarchy-delux-m900)、[aj179-linux](https://github.com/Rockeyxx/aj179-linux): Motospeed、Delux、Ajazz
- [AreYouLowBattery](https://github.com/ryan-mant/AreYouLowBattery): Delux M900 Pro の CompX レシーバーのレポート
- [ajazz-aj139-macos](https://github.com/werquess/ajazz-aj139-macos) と [AjazzAJ139V2](https://github.com/nico2525nn/AjazzAJ139V2): Ajazz AJ139 V2
- [Incott-Manager](https://github.com/OmarK6/Incott-Manager)、[incott-mouse-app](https://github.com/HeHaoren/incott-mouse-app) と [MouseBattery](https://github.com/FelixNg21/MouseBattery): Incott
- Wraith の Web ドライバー（[w1.software](https://www.w1.software/)）: Wraith W1
- OpenRazer PR #2794 と [omarchy-blackshark-v3](https://github.com/ReedME/omarchy-blackshark-v3): BlackShark V3
- OpenRazer PR #2862 と [HaloBattery](https://github.com/HeyOkay/HaloBattery): BlackShark V2 Pro (2023)
- [razer-barracuda-x-battery](https://github.com/mehdibouchami/razer-barracuda-x-battery) と [barracuda-x-battery](https://github.com/nightdevx/barracuda-x-battery): `1532:0550` レシーバーの Razer Barracuda X（2022）。[razer-barracuda-battery-tray](https://github.com/KhromotozzDevOut/razer-barracuda-battery-tray): `1532:0552` レシーバーのフレーム構成
- [OpenRazer PR #2899](https://github.com/openrazer/openrazer/pull/2899): BlackShark V3 X
- [HyperXWM](https://github.com/Medprj/HyperXWM): HyperX Cloud III Wireless
- [HyperHeadset](https://github.com/LennardKittner/HyperHeadset): HyperX Cloud III S、Cloud II Core、Cloud Flight S
- [HyperBatteryMonitor](https://github.com/davidsantanaalves/HyperBatteryMonitor): HyperX Cloud Stinger Core Wireless
- [BatteryTray](https://github.com/qu1ncky/BatteryTray): Rongyuan と Xenta のレシーバー（Attack Shark など）
- [sonix-keyboard-studio](https://github.com/donglover69/sonix-keyboard-studio): 2.4G ドングルの SONiX キーボード（AJAZZ AK820 MAX、AK980 V2、AULA F108 Pro）
- [openajazz](https://github.com/shrey715/openajazz) と [Kraber](https://github.com/AkashPanja/Kraber): Semico `1A2C`（`AA 55 CC 33` / `0x0E`） の、Attack Shark X98 と AJAZZ AK820 Max Plus 向けステータスプロトコル
- [coolermaster-usb-protocol](https://github.com/syntactic-spice/coolermaster-usb-protocol) と [MM731-Controller](https://github.com/riVFerd/MM731-Controller): Cooler Master MM712 と MM731
- [GamesirBatteryTray](https://github.com/WWWyyy452/GamesirBatteryTray) と [Gamesir-Nova-2-Lite-Battery-Detection](https://github.com/AJAY0406/Gamesir-Nova-2-Lite-Battery-Detection): GameSir Nova
- [jabridge](https://github.com/Watchdog0x/jabridge): Jabra の GNP プロトコル（Link 380 / 390 ドングル）
- [xd5-go-web](https://github.com/jarjut/xd5-go-web): Fantech Helios Go XD5
- Linux `hid-playstation`: DualShock 4 / DualSense のレポート構成
- [SDL の Flydigi HID ドライバー](https://github.com/libsdl-org/SDL/blob/main/src/joystick/hidapi/SDL_hidapi_flydigi.c) と [HaloBattery の issue #191](https://github.com/HeyOkay/HaloBattery/issues/191): Vader 5 Pro の問い合わせのフレーム構成とバッテリーの配置
- [SDL の 8BitDo HID ドライバー](https://github.com/libsdl-org/SDL/blob/main/src/joystick/hidapi/SDL_hidapi_8bitdo.c): 8BitDo Ultimate 2 のバッテリーバイト
- BEITONG iControl（KP20 のページとレシーバーの USB 通信）: BEITONG KP20 のバッテリー問い合わせとペイロードのスクランブル
- [SDL の 8BitDo HID ドライバー](https://github.com/libsdl-org/SDL/blob/main/src/joystick/hidapi/SDL_hidapi_8bitdo.c) と [8bitdo-ultimate2-linux](https://github.com/MiguelSanzBr/8bitdo-ultimate2-linux): 8BitDo のバッテリーバイトとメーカー独自の HID プロトコル
- JBL QuantumENGINE（HIDV3 のデバイス情報メッセージ）: JBL Quantum ヘッドセット
- [HaloBattery](https://github.com/HeyOkay/HaloBattery/blob/main/docs/protocols.md): Corsair Sabre V2 Pro Ultralight、`FF02:0002` 上の Compx プロトコル
- JBL QuantumENGINE: Quantum 350 の HIDV1 による接続とバッテリーのレポート、新しめの Quantum ヘッドセットの HIDV3 デバイス情報メッセージ

## ライセンス

[GNU General Public License v3.0 以降](LICENSE)。このソフトウェアは使用、改変、再配布ができますが、これをもとにして配布するものは、ソースコードとともに同じライセンスで公開する必要があります。
