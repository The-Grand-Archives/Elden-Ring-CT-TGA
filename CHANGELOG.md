# Changelog
## [Unreleased]
### Changed
 - OptionsData -> Ray Tracing Quality setting moved up one header
 - Supported game version changed to v1.09
### Fixed
 - Version check for Free Camera script
 - Free camera updated for v1.09
 - Spacing on version check errors

## [v1.2.0] - 2023-03-06
### Added
 - by [tremwil](https://github.com/tremwil):
   - New C library features:
     - `hde64.h`: HDE64 x86 dissembler
     - `vector.h`: macro-based STL-like "templated" dynamic array
     - `hashmap2.h`: macro-based STL-like "templated" linear probing hash table with dynamic bucket count
     - `code_utils.h`:
       - `virtual_alloc_near` function for allocating memory within short JMP distance of a memory region, similar to CE's `alloc(symbol, size, target.exe)`
       - `code_reloc` function for performing control flow analysis of a function and reassembling it in another region of memory
       - `call_hook` struct and related functions for call hooking game functions to C code hooks, with automatic thunk generation
     - `mem_region.h`
       - Support for quickly defining memory regions from module and section names via the region_from_module function
     - `pattern.h`
       - CE AOB syntax parsing via the pattern struct and pattern_init function
       - Easy CE-like easy_aob_scan function for performing a unique AOB scan given a module/section name and a CE AOB string
     - Example script making use of the new features in `Scripts > Misc`: AOB scanning for ItemDrop, relocating its code and call hooking it to allow for arbitrary spawn coordinates
 - by AssassinXMod:
   - Unlock all Summoning Pools
 - by Pav:
   - Free Camera
### Changed
 - "table_ver", "game_ver", and "ce_ver" are now global variables
 - Removed username from tga path
 - by [tremwil](https://github.com/tremwil):
   - Moved clangd hints from `.clangd` to VSCode workspace settings to allow for relative include paths on Windows
### Fixed
 - Spelling of names in Great Rune dropdown

## [v1.1.7] - 2023-01-12
### Changed
 - Moved code for C include path to not run before version checks
 - Singleton Finder timeout to 2000
 - Commented out linux check
### Fixed
 - Teleport to Map-Relative Coordinates

## [v1.1.6] - 2022-12-15
### Added
 - OptionData header
### Changed
 - Supported CE version is now required and option to download is given
 - Supported game version to 1.08.1
### Fixed
 - Pointers in the CSWindow header
 - Not being able to spawn more than one "Arrow"
 - Projectiles and other non-weapon items being spawned with the Ash of War value not being reset

## [v1.1.5] - 2022-12-08
### Fixed
 - AddSoul
 - Offsets used to reach PlayerGameData from WorldChrMan
 - Mistakes in "Targeted Npc Info" and "Last Hit Npc Info" helpers

## [v1.1.4] - 2022-12-07
### Changed
 - Supported version to v1.08

## [v1.1.3] - 2022-12-02
### Changed
 - Timeout for Singleton Finder to 1000

## [v1.1.2] - 2022-11-05
### Added
 - by [tremwil](https://github.com/tremwil):
   - runOnceForVersion feature that runs a function only once per table version
   - QoL scripts for invaders
### Fixed
 - by [tremwil](https://github.com/tremwil):
   - Singleton finder crash that affected some users

## [v1.1.1] - 2022-11-04
### Fixed
 - by [tremwil](https://github.com/tremwil):
   - ItemGib

## [v1.1.0] - 2022-11-04
### Added
 - by [tremwil](https://github.com/tremwil):
   - RTTI powered singleton (base) address finder that identifies and registers almost all singleton addresses extremely quickly
   - Archiving system so that a TGA C library can be packaged with the table (installed under `%PROGRAMDATA%/the-grand-archives/`)
### Changed
 - ItemGib replaced with its previous version using C code inbetween Assembly
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - "Unlock all ..." scripts now auto-disable on completion
 - by [tremwil](https://github.com/tremwil):
   - Updated C paramdefs & param field metadata
   - Reworked CParamUtils to use new C library (should now work under Wine)
   - Cleaned up "Table Tools"
### Fixed
 - "printProgress" check in scripts that use it
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - "Quit (Desktop)" script
 - by [tremwil](https://github.com/tremwil):
   - Bugs in CE symbol resolution breaking C code compilation and libc/winapi includes when running under Wine
   - Updated CSCRIPT with Wine compatibility and fixed synchronization bug
   - Teleport to Map-Relative Coordinates
### Removed
 - Linux check from scripts written in C that were previously incompatible with Linux

## [v1.0.1] - 2022-10-16
### Fixed
 - ItemGib ReinforceLv code using wrong data type

## [v1.0.0] - 2022-10-15
### Added
 - Flags for Royal Capital
 - Set flag when user is on Linux (Wine) and do not run CSCRIPT + CParamUtils
 - Errors for Linux incompatible scripts
 - 'printProgress' config option
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - "SaveLoad2" subsection, Statistics > SaveLoad2
   - Misc savefile related scripts and pointers
   - New "Invasion Regions" script to modify areas targeted by multi-area invasions and blue summons, Event Flags > Invasion Regions
   - New "Event Flags" script header
   - ef.getFlag, ef.setFlag, ef.batchSetFlags functions
   - Event Flags by ID subsection
   - Details, explanations and examples for the new functions in the "Event Flags" header script, as well as in:
     - Event Flags > Event Flags by ID > How to use
     - Event Flags > Event Flags by ID > Examples
   - Additional check in getGameVersion in case the game is running with EAC
   - New "Table Tools" header
   - Persistent table configuration, Table Tools > Configure Table
   - New config options:
     - Save symbols (speeds up lookup) (default: true)
     - Prevent opening table if game is not running (default: true)
     - Check game version (default: true)
     - Check Cheat Engine version (default: true)
     - Check table version (Github) (default: true)
   - Default config section in the table initialization script
   - Functionality to register new config variables in the default config section
   - Functionality to cache (save) symbol addresses (speeding up their subsequent lookup)
   - Table Tools > Clear Symbol Cache to delete all cached symbols
   - The table FAQ now opens the first time the table is opened
   - Table Tools > Clear runOnce Memory to delete all identifiers tga:runOnce has saved running functions
   - Default TGA files path: %PROGRAMDATA%/the-grand-archives/
   - "tga" class for file manipulation functions: tga:loadConfig, tga:saveConfig, tga:loadSymbolCache, tga:saveSymbolCache, tga:clearSymbolCache, tga:runOnce, tga:clearRunOnce
   - isdir and mkpath file manipulation functions 
   - sanitizeUsername, getGameVersion functions
   - getAddressProcessSafe, registerBaseByKey functions
   - cacheSymbol, AOBScanProcessCached, registerBaseByKeyCached cache interacting functions
   - Details, explanations and examples for the new functions in the table initialization script
 - by [sfix](https://github.com/garyttierney):
   - "Event Flags" script as a basis for event flag manipulation by ID
### Fixed
 - "Boost for low FPS" script
 - Targeted Npc Info
 - Last Hit Npc Info
### Changed
 - Removed Dungeons from Unlock all Maps
 - No longer using synchronize
 - Replaced ItemGib's ReinforceLv C code with ASM for better compatibility
 - Some entries in statistics no longer marked as unsafe
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - Unlock all Graces, Whetblades, Cookbooks, Maps scripts to use flag IDs instead of pointers
   - Reorganized table initialization script structure
   - Table initialization to utilize config variables
   - Significantly reduced the time it takes to open the table by caching base addresses (config option)
   - Table can now be opened without the game being launched (config option)
   - Reorganized base AOBs into a Lua table
   - Table will now open in case of not finding all AOBs
   - Missing AOBs are printed in the Lua console output
   - Table initialization variable game_ver now contains a version string, formatted like "1.XX.Y"
   - Unsupported game version warning message now displays the current and supported game versions
 - by [tremwil](https://github.com/tremwil):
   - CParamUtils early initialization fix
### Removed
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - Old method of getting base addresses from AOBs in the table initialization
### Deprecated
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - Old "Event Flags" header with flag pointers moved to Event Flags > Deprecated

## [v0.8.2] - 2022-10-13
### Fixed
 - Compatibility for App ver. 1.07

## [v0.8.1] - 2022-08-10
### Added
 - More NPC flags and door flags by RBT
### Changed
 - Update supported game version to v1.06
### Fixed
 - Upgrades Need No Materials

## [v0.8.0] - 2022-07-13
### Added
 - Give all Crystal Tears script to MassItemgib
 - Item Discovery x10 script to Scripts->QoL
 - Faster respawn script to Scripts->QoL
 - ThrowMan symbol
 - Event Flags for some doors and many NPCs by RBT
 - steam_appid.txt will now be shipped with releases
### Changed
 - Cleaned up Discardable Items script
 - Moved Discardable Items to Scripts->QoL
 - Moved World Map Cursor Speed to Scripts->QoL
 - Moved Warp out of uncleared mini-dungeons to Scripts->QoL
 - Reorganised Event Flags->Bosses
 - Use process (LUA) or $process (AA) to support renamed executables
 - Cleaned up base address finders, no longer using autoAssemble()
 - Improved some of the AOBs
 - Updated README: Removed latest version changelog, added "How to use"
### Fixed
 - CSTrophy symbol missing
 - Map-Relative Teleport within legacy dungeons
 - CParamUtils (C Param Patcher) script crashes

## [v0.7.0] - 2022-06-14
### Added
 - Event Flags now have dropdowns
 - Low FPS boost script by Jouta Kujo
### Changed
 - Update supported game version to v1.05
 - Improve Warp script compatibility
### Fixed
 - Potential solution to MassItemGib crashes

## [v0.6.1] - 2022-06-07
### Added
 - Check if the user forgot to launch without EAC

## [v0.6.0] - 2022-06-06
### Added
 - Give all crafting materials x999 by Mar-Veloz
 - Give all upgrade materials x999
 - Address based helpers and address finders
 - TROPHY section with achievement unlocker
 - Teleport to Map-Relative Coordinates by tremwil
 - Some ParamPatcher2 scripts, including Warp out of mini dungeons
 - Version check for game, CE, and cheat table
 - Some event flags and fix the names of some
 - "Unlock all ..." scripts for event flags
 - Draw Throw Area
 - CSCRIPT - CE C scripting extensions by tremwil
 - CParamUtils (C Param Patcher) by tremwil
### Changed
 - ItemGib now uses $ccode instead of $luacode
### Fixed
 - ParamUtils error spam should be gone, hopefully
 
## [v0.5.2] - 2022-04-21
### Removed
 - Roped Freezing Pot in ItemGib

## [v0.5.1] - 2022-04-21
### Removed
 - Miranda's Prayer in ItemGib
### Fixed
 - ItemGib reading Player ReinforceLv as int instead of byte

## [v0.5.0] - 2022-04-20
### Added
 - Additional Grace ID names (by Careless Esper)
 - Great Rune selection
 - Param Patcher: BuddyParam class, Blaidd Spirit Ash
 - MassItemGib: all ashes of war, all limited quantity craftables, all prattling pates, misc consumables (by The-Raid-Boss)
 - MassItemGib: all bell bearings (by Apricus)
 - Event Flags: Whetblades, Cookbooks, Graces, Maps (by Apricus)
 - Maps, Whetblades, and Cookbooks removed from ItemGib dropdown
 - Idle Animation IDs (summon anims, fog wall)
 - Coordinates and Camera sections
 - Complete FaceData header
 - Budget inventory viewer (EquipInventoryData) and other misc stuff in Hero
 - Npc Helpers added
 - Toughness and SuperArmor info for player and NPCs
### Changed
 - Last x highlighted helpers now use proper paramdefs
 - ID Helpers now use proper paramdefs and rely on Param Patcher
 - ItemGib will now handle upgrade level in a better way
### Removed
 - Cut content stripped from ItemGib
### Fixed
 - Missing items
 - MassItemGib crashes hopefully resolved

 ## [v0.4.2] - 2022-04-19
 ### Fixed
 - Updated AOBs for v1.04
 
## [v0.4.1] - 2022-03-19
### Fixed
 - Some Warp IDs
 - ItemGib issues: Bloodhound Claws not taking enhancements, Mohgwyn's Sacred Spear missing
 - Fixed Hero>Stats

## [v0.4.0] - 2022-03-17
### Added
 - ReinforceLv, Rune Arc, Character Type, Team Type, ClearCount added under Statitics
 - Resistances, EquipMagicData, GestureGameData,SpecialEffects>Active Effects added under Hero
 - Igromanru's Param Patcher v2 ported, Param Classes are still WIP and may not work as expected
 - New scripts: Unlock All Regular Gestures, Upgrades Need No Materials, Custom FOV
 - Easier to use Helpers are now available
### Changed
 - Warp function adjusted to work with the same IDs as Last Grace, dropdowns with names have been added as well
### Fixed
 - AOBs fixed for latest update (v1.03.0)

## [v0.3.1] - 2022-03-06
### Fixed
 - ItemGib adjusted to hopefully fix MassItemGib related crashes
 - MassItemGib expanded

## [v0.3] - 2022-03-05
### Added
 - PlayerParam updated
 - ChrAsm (dec), ChrAsm 2 (hex)
 - FaceData, still WIP but full AOB is available
 - ItemGib now features a complete dropdown for items, as well as selection of Upgrade, Reinforce Level, and Ash of War
 - WIP MassItemGib: Weapons and Projectiles
 - Warp function, IDs will be added at a later time
 - Save Slot and Last Grace
 - Debug Stuff > Damage management | ダメージ管理, contains attack hitbox display
### Changed
 - Corrected names of Character Flags

## [v0.2.2] - 2022-03-01
### Added
 - Added script to use the table with eldenring.exe renamed to start_protected_game.exe

## [v0.2.1] - 2022-02-28
### Fixed
 - Param Spreadsheet link in Table FAQ
 
## [v0.2] - 2022-02-28
### Added
 - Helpers: Weapon, Protector, Accessory, Goods, Bullet, SpEffectParam, Magic
 - Full list of params
 - Character Flags: NoDead, NoStaminConsumption, NoFPConsumption, NoDead, NoGoodsConsume
 
## [v0.1] - 2022-02-26
### Added
 - Stats, Attributes, WIP PlayerParam
 - AddSoul, ItemGib, ItemDrop
 - Custom FPS Limit


[unreleased]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.2.0...dev
[v1.1.7]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.7...v1.2.0
[v1.1.7]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.6...v1.1.7
[v1.1.6]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.5...v1.1.6
[v1.1.5]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.4...v1.1.5
[v1.1.4]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.3...v1.1.4
[v1.1.3]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.2...v1.1.3
[v1.1.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.1...v1.1.2
[v1.1.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.1.0...v1.1.1
[v1.1.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.0.1...v1.1.0
[v1.0.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.0.0...v1.0.1
[v1.0.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.8.2...v1.0.0
[v0.8.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.8.1...v0.8.2
[v0.8.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.8.0...v0.8.1
[v0.8.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.7.0...v0.8.0
[v0.7.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.6.1...v0.7.0
[v0.6.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.6.0...v0.6.1
[v0.6.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.5.2...v0.6.0
[v0.5.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.5.1...v0.5.2
[v0.5.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.5.0...v0.5.1
[v0.5.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.4.2...v0.5.0
[v0.4.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.4.1...v0.4.2
[v0.4.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.4.0...v0.4.1
[v0.4.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.3.1...v0.4.0
[v0.3.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.3.0...v0.3.1
[v0.3]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.2.2...v0.3
[v0.2.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.2.1...v0.2.2
[v0.2.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.2...v0.2.1
[v0.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.1...v0.2
[v0.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/releases/tag/v0.1
