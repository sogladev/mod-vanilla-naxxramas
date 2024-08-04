-- Based on the -Day36512- script for -ZhengPeiRu21/mod-individual-progression-

local NaxxKick = {}

function NaxxKick.OnLogin(event, player)
    local mapId = player:GetMapId()
	if mapId == 533 then
		player:Teleport(0, 3082.6, -3725.78, 132.41, 0)
	end
end

RegisterPlayerEvent(3, NaxxKick.OnLogin)
