-- Add invisible teleport trigger NPC to plaguewood naxx entrance
-- (REQUIRES) CUSTOM PATCH to avoid breaking
DELETE FROM `creature` WHERE `guid` = 352043;
INSERT INTO `creature` (`guid`, `id1`, `id2`, `id3`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `wander_distance`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(352043, 351097, 0, 0, 0, 139, 2277, 1, 1, 0, 3132.8572, -3731.2629, 138.622925, 4.71395, 300, 0, 0, 6986, 0, 0, 0, 0, 0, '', 0);
