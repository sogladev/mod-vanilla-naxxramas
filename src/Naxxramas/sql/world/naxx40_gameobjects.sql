-- Custom GUIDs
-- `gameobject_template` 361000, 361001, 193166
-- `gameobject` 181056, 193166
SET @ENTRY:=361000;
SET @GUID:=5330300

SET @ENTRY_GO:=@ENTRY+000;
SET @GUID_GO:=@GUID+209;
SET @ENTRY_REFERENCE_LOOT:=314800;
SET @GUID_TRANSPORT:=21;

-- Four Horseman chest
DELETE FROM `gameobject_template` WHERE `entry`=@ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@ENTRY_GO, 3, 1387, 'Four Horsemen Chest', '', '', '', 1, 1634, @ENTRY, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);
REPLACE INTO `reference_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `GroupId`, `MinCount`, `MaxCount`) VALUES
(@ENTRY_REFERENCE_LOOT, 22349, 0, 0.0, 0, 1, 1, 1),
(@ENTRY_REFERENCE_LOOT, 22350, 0, 0.0, 0, 1, 1, 1),
(@ENTRY_REFERENCE_LOOT, 22351, 0, 0.0, 0, 1, 1, 1);
REPLACE INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `GroupId`, `MinCount`, `MaxCount`) VALUES
(@ENTRY_GO, @ENTRY_REFERENCE_LOOT, @ENTRY_REFERENCE_LOOT, 100, 0, 0, 2, 2),
(@ENTRY_GO, 22691, 0, 0, 0, 2, 1, 1),
(@ENTRY_GO, 22726, 0, 30, 0, 0, 1, 1),
(@ENTRY_GO, 22809, 0, 0, 0, 2, 1, 1),
(@ENTRY_GO, 22811, 0, 0, 0, 2, 1, 1),
(@ENTRY_GO, 23025, 0, 0, 0, 2, 1, 1),
(@ENTRY_GO, 23027, 0, 0, 0, 2, 1, 1),
(@ENTRY_GO, 23071, 0, 0, 0, 2, 1, 1);

-- Add Entrance transporter object. Necromantic Runestone (id: 189314, displayID: 7786)
SET @TRANSPORTER_COOLDOWN:= 5;
SET @TRANSPORTER_X:= 3123.26;
SET @TRANSPORTER_Y:= -3869.36;
SET @TRANSPORTER_Z:= 138.34;
SET @TRANSPORTER_O:= 0.2175;
SET @DISPLAY_ID:=7786;
DELETE FROM `gameobject_template` WHERE (`entry` = @ENTRY+001);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@ENTRY+001, 10, @DISPLAY_ID, 'Teleport To Naxxramas', '', '', '', 1, 0, 0, 0, 0, @TRANSPORTER_COOLDOWN, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'gobject_naxx40_tele', 12340);
DELETE FROM `gameobject` WHERE `id`=@ENTRY+001 AND `map`=0;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(@GUID_GO+000, @ENTRY+001, 0, 0, 0, 1, 1, @TRANSPORTER_X, @TRANSPORTER_Y, @TRANSPORTER_Z, @TRANSPORTER_O, 0, 0, -0.063658, -1, 1, 0, 1, '', 0);

-- Add Floating Naxx Object (id: 181056)
-- Node 0 of PathID 436 in taxiPathNode
-- https://wow.tools/dbc/?dbc=taxipathnode&build=3.3.5.12340#page=1&colFilter%5B1%5D=436
DELETE FROM `gameobject` WHERE `id`=181056 AND `map`=0;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(@GUID_GO+001, 181056, 0, 0, 0, 1, 1, 3067.1255, -3533.4387, -331.89944, 0.0, 0.0, 0.0, 0, 0, 900, 100, 1, '', 0);
DELETE FROM `transports` WHERE `guid`=@GUID_TRANSPORT AND `entry`=181056;
INSERT INTO `transports` (`guid`, `entry`, `name`, `ScriptName`) VALUES
(@GUID_TRANSPORT, 181056, 'Naxxramas floating in Plaguewood - Eastern Plaguelands', '');
-- https://wow.tools/dbc/?dbc=taxipathnode&build=3.3.5.12340#page=1&colFilter[1]=436
-- Set speed (Data1) and map (Data6)
UPDATE `gameobject_template` SET `Data1`=1,`Data6`=0 WHERE `entry`=181056;

-- Meeting Stone
-- specific Naxxramas in Eastern Kingdoms
DELETE FROM `gameobject` WHERE `id`=193166 AND `map`=0;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(@GUID_GO+002, 193166, 0, 0, 0, 1, 1, 3072.64, -3886.67, 130.449, 2.4011, 0.0, 0.0, -0.932239, -0.361844, 300, 0, 1, '', 0);
-- Update meeting stone requirements (previous: minLevel 15)
-- AreaTable ID: 3456 ContinentID: 533
-- https://wow.tools/dbc/?dbc=areatable&build=3.3.5.12340#page=1&search=3456
SET @MIN_LEVEL:=58;
UPDATE `gameobject_template` SET `Data0` = @MIN_LEVEL WHERE (`entry` = 193166);
