-- Warning: .ReapplyUpdates = 0 must be disabled (=0) in the .conf
--          or this will have no effect
-- Warning: Scaling may have already been applied in the naxx40_creatures.sql
-- Warning: Only run this once after applying naxx40*sql scripts
SET @DAMAGE_MULTIPLIER:= 0.80;
SET @HEALTH_MULTIPLIER:= 1.00;
SET @ARMOR_MULTIPLIER:=  1.00;

UPDATE `creature_template`
SET
    `DamageModifier` = `DamageModifier` * @DAMAGE_MULTIPLIER,
    `HealthModifier` = `HealthModifier` * @HEALTH_MULTIPLIER,
    `ArmorModifier`  = `ArmorModifier`  * @ARMOR_MULTIPLIER
WHERE `entry` IN (
    SELECT `id1`
    FROM `creature`
    WHERE `map` = 533 AND `spawnMask` = 4
);
