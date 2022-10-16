# Changelog
## [Unreleased]
### Fixed
 - "printProgress" check in scripts that use it
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - "Quit (Desktop)" script

## [V1.0.1] - 2022-10-16
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


[unreleased]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.0.0...HEAD
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
