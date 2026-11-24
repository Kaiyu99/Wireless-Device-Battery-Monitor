# 配布用の zip（dist\WirelessBattery-Otokov-portable.zip）を作る。
# build.bat で WirelessBattery.exe をビルドし、exe・LICENSE.txt・installer\portable\ の中身（説明書）を
# WirelessBattery フォルダにまとめて zip にする。
# 実行方法（リポジトリのフォルダで）: powershell -ExecutionPolicy Bypass -File scripts\make-portable.ps1
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
Set-Location $root

& cmd /c build.bat
if ($LASTEXITCODE -ne 0) { throw 'build.bat が失敗しました' }

$stage = Join-Path $root 'build\portable'
$app = Join-Path $stage 'WirelessBattery'
if (Test-Path $stage) { Remove-Item $stage -Recurse -Force }
New-Item -ItemType Directory -Path $app | Out-Null
Copy-Item (Join-Path $root 'WirelessBattery.exe') $app
Copy-Item (Join-Path $root 'LICENSE') (Join-Path $app 'LICENSE.txt')
Copy-Item (Join-Path $root 'installer\portable\*') $app

$dist = Join-Path $root 'dist'
New-Item -ItemType Directory -Force -Path $dist | Out-Null
$zip = Join-Path $dist 'WirelessBattery-Otokov-portable.zip'
if (Test-Path $zip) { Remove-Item $zip -Force }
Compress-Archive -Path $app -DestinationPath $zip
Write-Host "作成しました: $zip"
