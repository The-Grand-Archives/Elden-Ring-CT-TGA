# Changelog
## [Unreleased]
### Added
 - Support for "key items" in EquipInventoryData header and RemoveItem, getItemIdx, getItemByIdx, isInventoryFull functions
 - getInvData function, returns inventory offset, if it's a key item inventory, and inventory size
 - by [tremwil](https://github.com/tremwil): 
   - executeEzStateEvent(id, parameterArray, chrInsHandle), replacing the code for Npc Menus
 - by [Dasaav](https://github.com/Dasaav-dsv/):
   - getGoodsName, getWeaponName, getProtectorName, getAccessoryName, getMagicName, getArtsName, getNpcName, getPlaceName
### Deprecated
 - Npc Menus code
### Removed
 - Seamless PvP header
### Fixed
 - ItemGib: Container item max quantity counted against its own limit

## [v1.14.1] - 2024-07-30
### Changed
 - Supported version to 1.13.0
### Fixed
 - A copypaste error in Invasion Regions that prevent the script from working
 - ItemGib, getGoodsAddr_func AOB broke
 - SpEffect.add / .erase
 - Set flask level

## [v1.14.0] - 2024-07-29
### Added
 - by [Dasaav](https://github.com/Dasaav-dsv/)
   - Save Character Flags, saves a list of all your flags to a file
   - Event Flags lua rewrite
 - New lua functions:
   - booltonumber(bool)
   - getPlayerIns(addr_or_slot) / getEnemyIns(addr)
### Changed
 - ItemGive now sets maxNum depending on potGroupId when relevant
 - Functions made accessible from anywhere:
   - Lua rewrite of AddSoul
   - Lua rewrite of ItemDrop
   - SpEffect.add, SpEffect.erase, SpEffect.remove
   - PlayAnimation
   - BulletSpawn.create
   - ef.getFlag rewrite
   - ef.setFlag rewrite
   - ef.batchSetFlags
### Fixed
 - "Remove by Item ID" for Storage Chest
 - "Unlock all Summoning Pools" thanks to [ivi](https://github.com/ividyon), also includes DLC summoning pools now
 - Session Info equipment for real
 - Focus, Stamina, Great Rune offsets
 - Currently Equipped Magic helper shows correct spell more reliably
 - Invasion Regions code by SeriouslyCasual and [Dasaav](https://github.com/Dasaav-dsv/)
 - Teleport to Map-Relative Coordinates offsets

## [v1.13.0] - 2024-07-05
### Added
 - full EquipItemData header
 - "Unequip slot" for EquipItem
 - Lua rewrite of Warp
 - Warp under Scripts -> Functions (now under both Functions and Build Creation, where it has been before)
 - DLC grace IDs, thanks to [Nordgaren](https://github.com/Nordgaren)
 - Storage chest support for EquipInventoryData, getItemIdx, getItemByIdx, and RemoveItem (including Remove all duplicates)
 - "Loading screen stuck fix" for Seamless Co-op users
### Changed
 - Seamless Co-op header was unnecessarily a script, now it's just a header
### Fixed
 - "Give build starting items" in MassItemGib
 - some chrasm pointers
 - "Remove Seamless Co-op Items" script
 - EquipItem's unequip function
 - Free Camera
 - Session Info equipment offsets

## [v1.12.1] - 2024-07-05
### Fixed
 - ItemPopup address, replaced with AOB

## [v1.12.0] - 2024-07-05
### Added
 - Scadutree Blessing and Revered Spirit Ash Blessing pointers to Statistics
 - DLC ashes of war to ItemGib dropdowns
 - "Give build starting items" in MassItemGib
 - New functions
   - ItemPopup
   - missingDlc
 - Npc menus
   - Moore
   - Thiollier
   - Grand Altar of Dragon Communion
   - Communion with Bayle
 - Event Flags
   - by Signum:
     - "Show DLC Map" to "Unlock all maps"
     - Labeled DLC regions for Invasion Regions
### Changed
 - DLC Larval Tear label to "Larval Tear (SotE)"
 - Gesture scripts now have fake item popups
 - "Remove Seamless Co-op items" script updated for mod rewrite
 - ItemGib now adjusts projectile and consumable quantity based on inventory and storage
 - MassItemGib quantities
 - Npc Menus version to v2.02.3 (app ver 1.12.3)
 - Supported game version to v2.02.3 (app ver 1.12.3)
### Fixed
 - ChangeMagic
 - EquipType in ItemGib->Detailed
 - Set flask level
 - ItemGib inventory and storage check
 - Event Flags script compatibility with Seamless Co-op

## [v1.11.2] - 2024-06-28
### Fixed
 - ItemGib getWeaponAddr hotfix for weapon level check

## [v1.11.1] - 2024-06-27
### Added
 - DLC check to ChangeMagic
### Fixed
 - copy paste mistake in event flag "unlock all" scripts

## [v1.11.0] - 2024-06-27
### Added
 - Print active SpEffects
 - Npc Menus -> Remembrance Duplication
 - Parts of player storage to EquipInventoryData header
 - Played Area header (WIP) to Hero header
 - ItemGib dropdown for DLC items, requires dlc license
 - Equipment of Champions shop menu
 - Global Functions->Test functions:
   - isOwnDlc
   - isDlcMagic
   - isInventoryFull / isStorageFull
 - Event Flags
   - by Signum:
     - DLC graces
     - DLC cookbooks
     - DLC maps
     - DLC bosses
### Changed
 - Replaced ItemGib with lua rewrite, old ItemGib code moved to Misc/WIP->Deprecated
 - MassItemGib weapon scripts made more easily customisable
### Fixed
 - Fix Unlock All Gestures scripts
 - Stastics->SaveLoad2
 - Invasion Regions, does NOT include DLC regions yet
 - Kill All Mobs, does NOT include DLC enemies yet
 - Statistics->Last Grace
 - Statistics->Misc header

## [v1.10.1] - 2024-06-22
### Added
 - Unlock all Shadow of the Erdtree gestures
 - more missing weapons to give all weapons (SotE)
 - MassItemGib additions for Shadow of the Erdtree:
   - Give all ashes of war
   - Give all remembrances
   - Give all bell bearings
   - Give all spirit ashes
   - Give all sorceries and incantations (should be split up later)
   - by Layka:
     - Give all crystal tears
     - Give all projectiles x99
   - by Bearmageddon:
     - Give all greases x999
     - Give all crafted pots x999
     - Give all misc consumables x999
     - Give all crafting materials x999
### Changed
 - CsDlc names
 - address_version text to specify "executable version" instead of "app ver"
### Fixed 
 - Fix Print Inventory
 - Remove All Duplicates
 - getItemIdx, getItemByIdx, getItemType
 - ChrAsm
 - GestureGameData
 - GestureEquipData
 - Unlock all gestures
 - EquipInventoryData
 - Npc Menus

## [v1.10.0] - 2024-06-21
### Added
 - ApplyEffect
 - Colosseum IDs to Event Flags
 - Party Member Info
 - ChangeMagic
 - ItemGive lua script under Global Functions
 - DLC items to MassItemGib
### Changed
 - Increase size of ItemGibArray alloc in ItemGib, might fix crashing
 - Improved getItemIdx
 - Renamed Shared Functions to Global Functions
 - Moved getItemIdx, getItemByIdx, and getItemType into a single script
 - Moved code of RemoveItem, equipItem, and changeMagic under Global Functions
 - "Remove Seamless Co-op items" now uses equipItem and RemoveItem
 - Supported game version to app ver 1.12 (executable v2.02)
### Fixed
 - RemoveItem

## [v1.9.0] - 2024-03-06
### Added
 - Misc/WIP > Dependencies > Shared Functions
   - getItemIdx
   - getItemByIdx
   - getItemType
 - EquipItem function, equip any item from inventory via inventory index or item id
 - "Remove by Item ID" for RemoveItem

## [v1.8.0] - 2024-02-24
### Added
 - Current magic slot and magic quantities (unused) to EquipMagicData
 - BulletSpawn
### Fixed
 - Npc Menus

## [v1.7.1] - 2024-01-18
### Added
 - Basic first time setup question for update check
### Changed
 - Supported game version to app ver 1.10.1 (executable v2.00.1)
### Fixed
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - Last Hit Npc Info
   - Free Camera

## [v1.7.0] - 2023-11-21
### Added
 - Hero > GameData > EquipInventoryData > Print Inventory
 - Scripts > Functions > RemoveItem
 - Scripts > Functions > RemoveItem > Remove All Duplicates
 - Scripts > Npc Menus has been greatly expanded to include more menus and made slightly easier to update
 - by [sovietspaceship](https://github.com/sovietspaceship):
   - Colosseum unlock state Event Flags
   - Unlock all Colosseums script
### Changed
 - OpenProcess approach now uses a table and for loop
### Fixed
 - Allocated memory in PlayAnimation should deallocate properly now

## [v1.6.1] - 2023-08-18
### Fixed
 - by [tremwil](https://github.com/tremwil):
   - CSEventFlagMan / CSFD4VirtualMemoryFlag symbols, which broke Event Flags

## [v1.6.0] - 2023-08-18
### Added
 - Functions header
 - PlayAnimation script
 - "Wraith Caller" and some other enemy to Kill all mobs
 - Scripts > Build Creation > Set flask level
 - Scripts > Build Creation > Add charge to flask
### Changed
 - Moved scripts from Scripts > Misc to Scripts > Functions
 - Removed Deathsbane Jerky, Deathsbane White Jerky, Drawstring Freezing Grease from ItemGib dropdown
 - Required CE files check now includes "luaclient-x86_64.dll"
 - by [tremwil](https://github.com/tremwil):
   - FD4Singleton finder rewritten

## [v1.5.0] - 2023-07-27
### Added
 - Npc Menus header
   - Level Up
   - Shop
   - Rebirth
   - Cosmetics
 - by [Dasaav](https://github.com/Dasaav-dsv):
   - setBit function
### Changed
 - Supported game version to app ver 1.10 (executable v2.00)

## [v1.4.0] - 2023-06-20
### Added
 - Death Num in GameData
 - Char flags No Hit, No Attack, No Move, No Update for npc helpers and hero header
 - Length played pointers for current animation
 - Debug Stuff > GAME > LOCK_TGT_MAN
 - game_title var
 - address_version function to throw an error for incompatible scripts that rely on addresses
 - Get Param List as table script (intended as example)
 - inArray lua function to check if an item is inside a specified array
 - Kill all mobs script
### Changed
 - Current Animation pointers changed for npc helpers and player
 - Renamed and moved some headers for consistency with Dark Souls III table
 - Free Camera script now uses address_version function
 - Tools in Param Mods now disable themselves after activation
### Fixed
 - Fix Last Hit Npc Info
 - Fix animation header for npc helpers

## [v1.3.1] - 2023-04-18
### Added
 - Check if user enabled dbk32 QueryMemoryRegionEx
 - Permanent lantern toggle script
### Changed
 - Supported game version to v1.09.1

## [v1.3.0] - 2023-04-02
### Added
 - Check if user has required TCC DLL
 - Seamless PvP Community:
   - by Orang:
     - Remove Water Effects
   - by Jacky Dima:
     - Remove No Attack
     - Cycling Tear
     - Heal using Bone Dart
     - Prevent Rot
   - by Jouta Kujo:
     - Auto Revive
### Changed
 - OptionsData -> Ray Tracing Quality setting moved up one header
 - Supported game version changed to v1.09
### Fixed
 - Version check for Free Camera script
 - Free camera updated for v1.09
 - Spacing on version check errors
 - NoGoodsConsume

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
 - Supported game version to v1.08.1
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


[unreleased]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.14.1...dev
[v1.14.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.14.0...v1.14.1
[v1.14.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.13.0...v1.14.0
[v1.13.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.12.1...v1.13.0
[v1.12.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.12.0...v1.12.1
[v1.12.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.11.2...v1.12.0
[v1.11.2]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.11.1...v1.11.2
[v1.11.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.11.0...v1.11.1
[v1.11.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.10.1...v1.11.0
[v1.10.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.10.0...v1.10.1
[v1.10.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.9.0...v1.10.0
[v1.9.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.8.0...v1.9.0
[v1.8.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.8.0...v1.9.0
[v1.8.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.7.1...v1.8.0
[v1.7.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.7.0...v1.7.1
[v1.7.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.6.1...v1.7.0
[v1.6.1]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.6.0...v1.6.1
[v1.6.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.5.0...v1.6.0
[v1.5.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.4.0...v1.5.0
[v1.4.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.3.1...v1.4.0
[v1.3.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.3.0...v1.3.1
[v1.2.0]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v1.2.0...v1.3.0
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
