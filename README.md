# Elden Ring Cheat Table

![Cheat Table Version](https://img.shields.io/github/v/release/The-Grand-Archives/Elden-Ring-CT-TGA?include_prereleases&label=Cheat%20Table&sort=semver&logo=github)
![Downloads](https://img.shields.io/github/downloads/The-Grand-Archives/Elden-Ring-CT-TGA/total?label=Downloads&logo=github)
[![Discord](https://img.shields.io/discord/334557263203401729?label=Discord&logo=discord)](https://discord.io/the-grand-archives)  
Elden Ring Cheat Engine table maintained by The Grand Archives.

## Discord

Our community, make sure to read the rules carefully.  
[The Grand Archives](https://discord.io/the-grand-archives)

## Latest Release

[![Download](https://img.shields.io/badge/dynamic/json.svg?label=download&url=https://api.github.com/repos/The-Grand-Archives/Elden-Ring-CT-TGA/releases/latest&query=$.assets[0].name&style=for-the-badge)](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/releases/latest)  
[Changelog](/CHANGELOG.md)

### Requirements

Cheat Engine: [7.4](https://github.com/cheat-engine/cheat-engine/releases)  
Game: App ver. 1.09.1

## How to use

### Info

This table is not meant to be used online and you will most likely be banned if you attempt to do so.

### Cheat Table (Windows)

1. Download and install Cheat Engine either from [Github](https://github.com/cheat-engine/cheat-engine/releases) or from its [website](https://cheatengine.org/)
2. Download the [Cheat Table](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/releases)
3. Unpack the .CT file anywhere, a recommendation would be your **My Cheat Tables** folder (e.g. `%USERPROFILE%\Documents\My Cheat Tables`)
4. Disable EasyAntiCheat and run the game, see [Disabling EasyAntiCheat](#disabling-easyanticheat)
5. Load the .CT file directly via double-click or selecting it and pressing enter, or launch Cheat Engine and load the .CT file via File->Load or by clicking on the folder icon
6. Activate the "Open" script by ticking its box

### Cheat Table (Linux)

I expect you to already have Steam, Wine, Proton, and the game installed

1. Launch the game at least once via Steam to have your wine prefix set up
2. Install [protonhax](https://github.com/jcnils/protonhax) (On Arch you should grab [protonhax-git](https://aur.archlinux.org/packages/protonhax-git))
3. Download and install the **Windows** version of Cheat Engine from [Github](https://github.com/cheat-engine/cheat-engine/releases) or from its [website](https://cheatengine.org/) using **Wine**
4. Download the [Cheat Table](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/releases)
5. Unpack the .CT file anywhere, a recommendation would be somewhere you can easily find within the wine prefix created for the game (e.g. `~/.steam/steam/steamapps/compatdata/1245620/pfx/drive_c/`)
6. In Steam, set the game's launch options to `protonhax init %command%`
7. Run the game via Steam ([Disabling EasyAntiCheat](#disabling-easyanticheat) is optional)
8. Run Cheat Engine via `protonhax run 1245620 /path/to/Cheat\ Engine.exe` in your terminal of choice or put it in a shell script (replace `/path/to/` with your actual path to where you installed CE)
9. Load the .CT file via File->Load or by clicking on the folder icon
10. Activate the "Open" script by ticking its box

### Disabling EasyAntiCheat

#### Method 1 - Recommended

1. Unpack `steam_appid.txt` from the [latest release](https://github.com/The-Grand-Archives/Elden-Ring-CT-TGA/releases/latest)
2. Locate your Elden Ring folder (e.g. `C:\Program Files\Steam\steamapps\common\ELDEN RING\Game` or `~/.steam/steam/steamapps/common/ELDEN RING/Game/`)
3. Move `steam_appid.txt` into the same folder as your Elden Ring executable (`eldenring.exe`)
4.
   - Windows: Run the game via `eldenring.exe`
   - Linux: Add `eldenring.exe` as a non-steam app and run that

#### Method 2 - Compatibility

1. Download LukeYui's Offline Launcher from [Nexusmods](https://www.nexusmods.com/eldenring/mods/98) or [Github](https://github.com/LukeYui/launch_modded_eldenring)
2. Locate your Elden Ring folder (e.g. `C:\Program Files\Steam\steamapps\common\ELDEN RING\Game` or `~/.steam/steam/steamapps/common/ELDEN RING/Game/`)
3. Move the downloaded .exe file into the same folder as your Elden Ring executable (`eldenring.exe`)
4.
   - Windows: Run the game via the **Offline Launcher**
   - Linux: Add the **Offline Launcher** to Steam as a non-steam app and run that

#### Method 3 - Legacy

1. Locate your Elden Ring folder (e.g. `C:\Program Files\Steam\steamapps\common\ELDEN RING\Game` or `~/.steam/steam/steamapps/common/ELDEN RING/Game/`)
2. Rename `start_protected_game.exe` to something else (e.g. `start_protected_game.exe.bak`)
3. Rename `eldenring.exe` to `start_protected_game.exe`
4. Run the game via Steam or `start_protected_game.exe`

## Credits

The Grand Archives | Reason
------------- | ---------------------
Ametalon | Table contributions (DS3)
Apricus | Event Flags, MassItemGib
Careless Esper | Grace ID Names
[Coinsworth](https://github.com/LukeYui/) | Table contributions, advice
Dalvik | Advice, ideas
[Dasaav](https://github.com/Dasaav-dsv) | Functionality reworks and additions
[hery](https://github.com/heryoff) | Grace ID Names
[Igromanru](https://github.com/igromanru) | Param Patcher, advice
[inuNorii](https://github.com/inuNorii) | Porting, maintaining, research
Jouta Kujo | Param scripts
RBT | Param scripts, Event Flags
Relinquished001 | Table contributions
[sfix](https://github.com/garyttierney) | Table contributions, param dumps, advice
Silence | Spreadsheet
The-Raid-Boss | MassItemGib additions
[tremwil](https://github.com/tremwil/) | CParamUtils and more table contributions

Github | Reason
------------- | ---------------------
[Mar-Veloz](https://github.com/Mar-Veloz) | Give all crafting materials x999
[qwelias](https://github.com/qwelias) | ReinforceLv pointer

Seamless PvP Community | Reason
------------- | ---------------------
Jacky Dima | Script contributions
Jouta Kujo | Script contributions
Orang | Script contributions

Other | Reason
------------- | ---------------------
AssassinXMod | Unlock all Summoning Pools
Pav | Free Camera
