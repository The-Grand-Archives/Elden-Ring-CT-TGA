# Changelog
## [Unreleased]
### Added
 - Give all Crystal Tears script to MassItemgib
 - Item Discovery x10 script to Scripts->QoL
 - Faster respawn script to Scripts->QoL
 - ThrowMan symbol
 - Event Flags for Varré by RBT
### Changed
 - Cleaned up Discardable Items script
 - Moved Discardable Items to Scripts->QoL
 - Moved World Map Cursor Speed to Scripts->QoL
 - Moved Warp out of uncleared mini-dungeons to Scripts->QoL
 - Reorganised Event Flags->Bosses
 - Use process (LUA) or $process (AA) to support renamed executables
 - Cleaned up base address finders, no longer using autoAssemble()
### Fixed
 - CSTrophy symbol missing

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

[unreleased]: https://github.com/inunorii/Elden-Ring-CT-TGA/compare/v0.7.0...HEAD
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