--
-- Add invisible teleport trigger NPC to plaguewood naxx entrance
DELETE FROM `creature` WHERE `guid` = 352043 and `id`=351097;
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(352043, 351097, 0, 0, 0, 139, 2277, 1, 1, 0, 3132.8572, -3731.2629, 138.622925, 4.71395, 300, 0, 0, 6986, 0, 0, 0, 0, 0, '', 0);

-- Add Naxxramas green portal hub effect
DELETE FROM `gameobject` WHERE (`id` = 181476);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`) VALUES
(5330510, 181476, 0, 139, 2277, 1, 1, 3132.780029, -3731.290039, 134.720001, 0, 0, 0, 0, 0, 0, 0, 1, '', 0);

-- Move meeting stone near hub
DELETE FROM `gameobject` WHERE `id`=193166 and `map`=0;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `VerifiedBuild`, `Comment`) VALUES
(5330511, 193166, 0, 0, 0, 1, 1, 3172.67, -3752.99, 133.944, 1.93617, 0, 0, -0.823802, -0.566877, 300, 0, 1, '', 0, 0);
