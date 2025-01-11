# Optional files
* `PlaguewoodHub` contains a map edit to restore the original Plaguewood teleporter hub
* `SkipAttunement` contains DB changes that are needed when disabling attunement requirement `Naxxramas.RequireAttunement=0`
* `DamageHealthArmorModifierScaling` contains a single query to apply additonal scaling to all Naxx40 creatures

## PlaguewoodHub
this folder contains:
* `naxx40_*.sql` that needs to be run manually
* `patch-4-X.MPQ` needs to be renamed to be used e.g. `patch-4.MPQ`
* `maps/` with `*.adt` and `*wdt` files for development

`naxx40_*.sql` needs to be run manually on your `acore_world` database

`maps/` contains edited Eastern Kingdoms map to replace the cauldron
with the original vanilla Naxxramas entrance

`patch-4-X.MPQ` contains the `maps/` folder to be placed in the clients `WorldOfWarcraft/Data/` folder. This needs to be renamed to be used e.g. `patch-4.MPQ`

Note that pathing will be off without rerunning extractors, but it's not that noticable from my experience as there's very few mobs around the portal area. To fix this, you will need to re-run acore's map/vmap/mmap extractors for changes to reflect serverside. See below

### Fix pathing by extraction
This process may take several hours to complete

reference:
https://wotlkdev.github.io/wiki/your_first_mod/your_first_map_edit.html
https://www.azerothcore.org/wiki/server-setup#extractors

To build extractors you must enable it in the config
```
CTOOLS_BUILD=${CTOOLS_BUILD:-all}
```
After compiling Extractors can be found in `env/dist/bin`

1. `patch-4.MPQ` needs to be present in `/Data` folder
2. run `map_extractor vmap4_extractor vmap4_assembler mmaps_generator` from your wow directory
3. Move extracted files to `env/dist/bin`

Tools to help extract files:
* (linux) helper by me https://gist.github.com/jellemeeus/f56c44fb1b9f342d685056c4e864c199
* (windows) helper by acore, found in `/apps/extractor`

## Skip attunement
config option
```
VanillaNaxxramas.Naxxramas.RequireAttunement = 0
```
required database changes:
`naxx40_skip_attunement.sql` Removes attunement requirement for Echoes of War (kill quest) which is a requirement for T3 quests and some other quests
