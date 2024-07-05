-- Custom GUIDs
-- creature 352042
-- creature_template 351097
-- Add MapDifficulty DBC Override
-- https://wow.tools/dbc/?dbc=mapdifficulty&build=10.0.0.44895#page=1&search=533
DELETE FROM `mapdifficulty_dbc` WHERE `ID` = 754;
INSERT INTO `mapdifficulty_dbc` (`ID`, `MapID`, `Difficulty`, `Message_Lang_enUS`, `Message_Lang_Mask`, `RaidDuration`, `MaxPlayers`, `Difficultystring`) VALUES
(754, 533, 2, 'You must be level 60 and in a raid group to enter.', 16712190, 604800, 40, 'RAID_DIFFICULTY_40PLAYER');

-- Remove exit teleport and replace with script
DELETE FROM `areatrigger_teleport` WHERE `ID` IN (5196, 5197, 5198, 5199, 4156);

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (5196, 5197, 5198, 5199);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5196, 'naxx_exit_trigger'),
(5197, 'naxx_exit_trigger'),
(5198, 'naxx_exit_trigger'),
(5199, 'naxx_exit_trigger');

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (5191, 5192, 5193, 5194);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5191, 'naxx_northrend_entrance'),
(5192, 'naxx_northrend_entrance'),
(5193, 'naxx_northrend_entrance'),
(5194, 'naxx_northrend_entrance');

-- Update spawnMask of all creatures to 10man + 25man
UPDATE `creature` SET `spawnMask` = 3 WHERE `spawnMask` = 7 AND `map` = 533;
-- Update spawnMask of all gameobjects to all
UPDATE `gameobject` SET `spawnMask` = 7 WHERE `spawnMask` = 3 AND `map` = 533;

-- Lich King uses same entry in Naxx WotLK and Naxx40 - Allow spawning in all versions
UPDATE `creature` SET `spawnMask` = `spawnMask` | 4 WHERE `id1` = 16980;

-- Naxxramas Trigger (frogger) should also spawn in Naxx40
UPDATE `creature` SET `spawnMask` = `spawnMask`| 4 WHERE `id1` = 16082;

DELETE FROM `dungeon_access_template` WHERE `id`=122;
INSERT INTO `dungeon_access_template` (`id`, `map_id`, `difficulty`, `min_level`, `max_level`, `min_avg_item_level`, `comment`) VALUES (122, 533, 2, 60, 0, 0, 'Naxxramas - 40man');
