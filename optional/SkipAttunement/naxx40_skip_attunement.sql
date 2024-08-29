--
-- Warning: .ReapplyUpdates = 0 must be disabled (=0) in the .conf
--          or this will have no effect
-- Remove PrevQuestID for Echoes of War (kill quest) which is a requirement for T3 quests
-- Disable attunement quest completion before being able to pickup Echoes of War
UPDATE `quest_template_addon` SET `PrevQuestID` = 0 WHERE (`ID` = 9033);
UPDATE `quest_template_addon` SET `NextQuestID` = 0 WHERE (`ID` IN (9121, 9122, 9123));
-- Remove reputation requirements for quests
UPDATE `quest_template_addon` SET `RequiredMinRepValue` = 0
WHERE `RequiredMinRepValue` > 0 AND `RequiredMinRepFaction` = 529
AND `ID` IN (
9232, 9033, 9230, 9229, 9120, 9082, 9101, 9102, 9038, 9034, 9099,
9237, 9057, 9042, 9037, 9039, 9041, 9036, 9233, 9089, 9118, 9098,
9081, 9040, 9100, 9115, 9080, 9048, 9070, 9110, 9109, 9046, 9105,
9096, 9112, 9114, 9111, 9117, 9097, 9079, 9116, 9077, 9106, 9113,
9047, 9103, 9044, 9083, 9087, 9242, 9045, 9049, 9088, 9060, 9084,
9236, 9078, 9071, 9043, 9090, 9107, 9061, 9240, 9244, 9073, 9074,
9241, 9054, 9068, 9075, 9069, 9095, 9050, 9234, 9072, 9059, 9058,
9245, 9093, 9056, 9243, 9091, 9104, 9108, 9246, 9086, 9092, 9055,
9235, 9238, 9239, 9378);
