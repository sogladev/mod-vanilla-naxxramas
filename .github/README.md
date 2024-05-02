# AzerothCore Module Vanilla Naxxramas

- Latest build status with azerothcore:

[![Build Status](https://github.com/jellemeeus/mod-vanilla-naxxramas/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/jellemeeus/mod-vanilla-naxxramas)

This is a module for [AzerothCore](http://www.azerothcore.org) that reintroduces the vanilla version of Naxxramas back to 335.

This project is constrained by the 335 client, therefore vanilla naxx cannot be fully restored without a client-side patch. To ensure compatibility (and an easier development experience), no client-side change will be necessary to use this module. This also means there will be inaccuracies, such as Mograine (4 horsemen) casting Riverdare's Mark.

If you encounter any issues or have suggestions, please post them as Github issues so that we can resolve them and improve this project.

## Features
* New Naxxramas difficulty 10man heroic which hosts level 60 version of Naxxramas
* Power level adjustments to Vanilla values
* Entrance from either Stratholme instance or through a teleporter located in Plaguewood near the original entrance
* Restores no longer accessible NPCs, quests and items related to the original Naxxramas
* Restore flying Naxxramas in Plaguewood

wiki (to be written) hosts full list

TODO: wiki full list of features
TODO: wiki full list of options

## Known Issues

Some are due to being limited by 335a client. Some of these could be fixed by client-side patch

* Icons are different for some spells i.g. Mark of Mograine, Loatheb's Deathbloom
* Mechanics: Sapphiron's frost aura should tick every 1s instead of 2s, Blaumeux' Void Zone range should be 3yd instead of 2yd
* Plaguewood Entrance missing (WIP-stuck)
* Some models like Deathknight's use wotlk death knight starter gear instead of the original armor set

Not all vanilla mechanics are implemented yet due to scripts being ported from Azerothcore's WOTLK Naxx

* 4 horsemen
* Maexxna Web Wrap and missing Trash spell

Other issues are due to potential upstream bugs

* Thaddius not moving
* OOC RP of Razuvious' DK Study
* OOC RP of Heigans Eye Stalk
* Gothik visuals

TODO: wiki full list of known issues

## How to install
clone into /modules so that /modules/mod-vanilla-naxxramas
compile and updater loads SQL when launching worldserver

TODO: wiki of install instructions

## History

Version 1: Overwriting Naxx10 with lvl 60 Naxxramas, autobalancer
https://github.com/azerothcore/mod-progression-system/pull/251/commits/0271f41137410efd06a6eb3c8a5619026f460345

Version 2: Naxx10HC difficulty, Stratholme entrance, Remove autobalancer, add boss scripts/trash scripts/smartAIs, damage adjustments, minor vanilla mechanics, scripts included in [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression)
https://github.com/jellemeeus/mod-progression-system-naxx25-60/tree/naxx

Version3: stand-alone custom-module `mod-vanilla-naxxramas`

## Acknowledgements
- [cmangos], [vmangos] for vanilla game data
- [ZhengPeiRu21](https://github.com/ZhengPeiRu21/mod-individual-progression) Integrating V1 Naxx40 scripts into [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) and allowing Naxx40 to co-exist alongside WOTLK Naxx
- [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) contributors and players for PR's and creating issues
- AzerothCore: [repository](https://github.com/azerothcore) - [website](https://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)

## License

GNU Affero General Public License v3.0

[LICENSE](./../LICENSE)
