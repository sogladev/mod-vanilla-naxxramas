# AzerothCore Module Vanilla Naxxramas

- Latest build status with azerothcore:

[![Build Status](
https://github.com/sogladev/mod-vanilla-naxxramas/actions/workflows/core-build.yml/badge.svg?branch=master&event=push)](https://github.com/sogladev/mod-vanilla-naxxramas)

This is a module for [AzerothCore](http://www.azerothcore.org) that reintroduces the vanilla version of Naxxramas back to 335.

This project is constrained by the 335 client, therefore vanilla naxx cannot be fully restored without a client-side patch. To ensure compatibility, no client-side change will be necessary to use this module. This also means there will be inaccuracies

If you encounter any issues or have suggestions, please post them as Github issues so that we can resolve them and improve this project.

## Some Features
* New Naxxramas difficulty 10man heroic which hosts level 60 version of Naxxramas
* Restores no longer accessible NPCs, quests and items related to the original Naxxramas
* Restore flying Naxxramas in Plaguewood
* Enter from either Stratholme instance, through a teleporter located in Plaguewood near the original entrance or the original entrance with an optional patch
* Power level adjustments (WIP) to vanilla values

![See Wiki for a summary of changes with pictures](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/02-Summary-of-changes-with-pictures)

![See Wiki for a full detailed list of changes](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/04-List-of-changes-in-detail)

https://github.com/sogladev/mod-vanilla-naxxramas/assets/46423958/2b56a239-001a-442a-aad4-df3717b21e9a

## How to install

![See Wiki for installation instructions](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/03-How-to-Install)

## Known Issues

Some are due to being limited by 335a client. Some of these could be fixed by client-side patch

- [ ] Icons are different for some spells e.g. Mark of Mograine, Loatheb's Deathbloom
- [ ] Mechanics: Sapphiron's frost aura should tick every 1s instead of 2s, Blaumeux' Void Zone range should be 3yd instead of 2yd
- [ ] Plaguewood Entrance was replaced with a Cauldron
- [ ] Some models like Deathknight's use wrath death knight starter gear instead of the original armor set

Not all vanilla mechanics are yet implemented yet due to scripts being ported from Azerothcore's WOTLK Naxx

- [ ] Maexxna Web Wrap should stick to the wall

Other issues are due to potential upstream bugs

* Thaddius not moving
* OOC RP of Razuvious' DK Study
* OOC RP of Heigans Eye Stalk
* Gothik visuals (WIP)

![See Wiki for a list of work to be done](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/05-Work-To-Be-Done)

## Breaking

The same instance is used for both the vanilla, 10 and 25 man difficulties. This means that same instance/boss/spell script(s) are used. Changes to Azerothcore's Naxxramas may cause breakage; more likely to the WOTLK version. So far only the Naxxramas instance script and Sapphiron are shared.

## Acknowledgements
- [cmangos](https://github.com/cmangos), [vmangos](https://github.com/vmangos) for vanilla game data
- [ZhengPeiRu21](https://github.com/ZhengPeiRu21/mod-individual-progression) Integrating V1 Naxx40 scripts into [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) and allowing Naxx40 to co-exist alongside WOTLK Naxx
- [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) contributors and players for PR's and creating issues
- AzerothCore: [repository](https://github.com/azerothcore) - [website](https://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)

## License

GNU Affero General Public License v3.0

[LICENSE](./../LICENSE)
