# AzerothCore Module Vanilla Naxxramas

- Latest build status with azerothcore:

[![Build Status](https://github.com/sogladev/mod-vanilla-naxxramas/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/sogladev/mod-vanilla-naxxramas)

This is a module for [AzerothCore](http://www.azerothcore.org) that reintroduces the vanilla version of Naxxramas back to 335.

This project is constrained by the 335 client, therefore vanilla naxx cannot be fully restored without a client-side patch. To ensure compatibility, no client-side change will be necessary to use this module. This also means there will be inaccuracies

If you encounter any issues or have suggestions, please post them as Github issues so that we can resolve them and improve this project.

## Some Features
* New Naxxramas difficulty 10man heroic which hosts level 60 version of Naxxramas
* Restores no longer accessible NPCs, quests and items related to the original Naxxramas
* Restore flying Naxxramas in Plaguewood
* Enter from either Stratholme instance, through a teleporter located in Plaguewood near the original entrance or the original entrance with an optional patch
* Power level adjustments (WIP) to vanilla values

TODO: wiki full list of features
TODO: wiki full list of options

![pictures: click here](../docs/picture_notes.md)

https://github.com/sogladev/mod-vanilla-naxxramas/assets/46423958/2b56a239-001a-442a-aad4-df3717b21e9a


## Known Issues

Some are due to being limited by 335a client. Some of these could be fixed by client-side patch

- [ ] Icons are different for some spells i.g. Mark of Mograine, Loatheb's Deathbloom
- [ ] Mechanics: Sapphiron's frost aura should tick every 1s instead of 2s, Blaumeux' Void Zone range should be 3yd instead of 2yd
- [ ] Plaguewood Entrance
- [ ] Some models like Deathknight's use wotlk death knight starter gear instead of the original armor set

Not all vanilla mechanics are yet implemented yet due to scripts being ported from Azerothcore's WOTLK Naxx

- [ ] Maexxna Web Wrap should stick to the wall

Other issues are due to potential upstream bugs

* Thaddius not moving
* OOC RP of Razuvious' DK Study
* OOC RP of Heigans Eye Stalk
* Gothik visuals

TODO: wiki full list of known issues

## How to install
clone into `/modules` so that `/modules/mod-vanilla-naxxramas`

compile and updater loads SQL when launching worldserver

TODO: wiki of install instructions

## Breaking

The same instance is used for both the vanilla, 10 and 25 man difficulties. This means that same instance/boss/spell may script(s) are used. Changes to Azerothcore's Naxxramas may cause breakage; more likely the WOTLK version. This module is setup so that Naxx10/25 should remain unaffected. So far only the Naxxramas instance script and Sapphiron are shared.

## History

Version 1: Overwriting Naxx10 with lvl 60 Naxxramas, autobalancer
https://github.com/azerothcore/mod-progression-system/pull/251/commits/0271f41137410efd06a6eb3c8a5619026f460345

Version 2: Naxx10HC difficulty, Stratholme entrance, Remove autobalancer, add boss scripts/trash scripts/smartAIs, damage adjustments, minor vanilla mechanics, scripts included in [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression)
https://github.com/sogladev/mod-progression-system-naxx25-60/tree/naxx

Version3: stand-alone custom-module `mod-vanilla-naxxramas`

## Acknowledgements
- [cmangos](https://github.com/cmangos), [vmangos](https://github.com/vmangos) for vanilla game data
- [ZhengPeiRu21](https://github.com/ZhengPeiRu21/mod-individual-progression) Integrating V1 Naxx40 scripts into [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) and allowing Naxx40 to co-exist alongside WOTLK Naxx
- [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) contributors and players for PR's and creating issues
- AzerothCore: [repository](https://github.com/azerothcore) - [website](https://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)

## License

GNU Affero General Public License v3.0

[LICENSE](./../LICENSE)
