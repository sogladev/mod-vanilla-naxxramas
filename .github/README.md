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
* Add the original beta Naxxramas entrance in the back of Stratholme
* Restore Naxxramas attunement and a shortcut in EPL usable after entering  once through the Stratholme entrance
* Add a shortcut to Naxxramas via a teleporter gameobject in EPL located in the closest Ziggurath to the Cauldron placed at the original Naxx teleporter location. An optional patch to restore the original entrance in EPL is added in `/optional`
* Power level adjustments to vanilla values. [Feedback wanted](https://github.com/sogladev/mod-vanilla-naxxramas/discussions/58)

![See Wiki for a summary of changes with pictures](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/02-Summary-of-changes-with-pictures)

![See Wiki for a full detailed list of changes](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/04-List-of-changes-in-detail)

https://github.com/sogladev/mod-vanilla-naxxramas/assets/46423958/2b56a239-001a-442a-aad4-df3717b21e9a

## How to install

![See Wiki for installation instructions](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/03-How-to-Install)

## Known Issues

Some are due to being limited by 335a client. Some of these could be fixed by client-side patch

- [ ] Requires `Expansion = 2` in your `worldserver.conf`. Similarly, players must have an account with expansion set to 2. For details see https://github.com/sogladev/mod-vanilla-naxxramas/issues/17
- [ ] Plaguewood Entrance was replaced with a Cauldron. The original entrance can be reintroduced with optional/PlaguewoodHub
- [ ] Icons are different for some spells e.g. Mark of Mograine, Loatheb's Deathbloom
- [ ] Mechanics: Sapphiron's frost aura should tick every 1s instead of 2s, Blaumeux' Void Zone range should be 3yd instead of 2yd
- [ ] Some models like Deathknight's use wrath death knight starter gear instead of the original armor set

Not all vanilla mechanics are yet implemented yet due to scripts being ported from Azerothcore's WOTLK Naxx

- [ ] Maexxna Web Wrap should stick to the wall

Other issues are due to potential upstream bugs

* Thaddius not moving
* OOC RP of Heigans Eye Stalk

![See Wiki for a list of Work To Be Done](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/05-Work-To-Be-Done)

## Breaking

The same instance is used for both the vanilla, 10 and 25 man difficulties. This means that same instance/boss/spell script(s) are used. Changes to Azerothcore's Naxxramas may cause breakage. So far only the Naxxramas instance script and Sapphiron are shared.

## Module compatibility

[See Wiki for Module Compatibility](https://github.com/sogladev/mod-vanilla-naxxramas/wiki/06-Module-Compatibility#scaling-modules)

## Acknowledgements
- [cmangos](https://github.com/cmangos), [vmangos](https://github.com/vmangos) for vanilla game data
- [ZhengPeiRu21](https://github.com/ZhengPeiRu21/mod-individual-progression) Integrating V1 Naxx40 scripts into [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) and allowing Naxx40 to co-exist alongside WOTLK Naxx
- [mod-individual-progression](https://github.com/ZhengPeiRu21/mod-individual-progression) contributors and players for PR's and creating issues
- AzerothCore: [repository](https://github.com/azerothcore) - [website](https://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)

## License

GNU Affero General Public License v3.0

[LICENSE](./../LICENSE)


## How to create your own module

1. Use the script `create_module.sh` located in [`modules/`](https://github.com/azerothcore/azerothcore-wotlk/tree/master/modules) to start quickly with all the files you need and your git repo configured correctly (heavily recommended).
1. You can then use these scripts to start your project: https://github.com/azerothcore/azerothcore-boilerplates
1. Do not hesitate to compare with some of our newer/bigger/famous modules.
1. Edit the `README.md` and other files (`include.sh` etc...) to fit your module. Note: the README is automatically created from `README_example.md` when you use the script `create_module.sh`.
1. Publish your module to our [catalogue](https://github.com/azerothcore/modules-catalogue).

