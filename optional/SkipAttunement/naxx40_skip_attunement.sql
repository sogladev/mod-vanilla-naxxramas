--
-- Warning: .ReapplyUpdates = 0 must be disabled (=0) in the .conf
--          or this will have no effect
-- Remove PrevQuestID for Echoes of War (kill quest) which is a requirement for T3 quests
-- Disable attunement quest completion before being able to pickup Echoes of War
UPDATE `quest_template_addon` SET `PrevQuestID` = 0 WHERE (`ID` = 9033);
UPDATE `quest_template_addon` SET `NextQuestID` = 0 WHERE (`ID` IN (9121, 9122, 9123));
