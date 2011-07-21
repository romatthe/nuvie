magic_casting_fade_effect()

local player_loc = player_get_location()

local player_x = player_loc.x
local player_y = player_loc.y
local player_z = player_loc.z

local foes_present = false

local i
for i=1,0x100 do
	local actor = Actor.get(i)

	if actor.obj_n ~= 0 and actor.alive == true and actor.visible == true and alignment_is_evil(actor.align) then

		local target_x = tmp_actor.x
		local target_y = tmp_actor.y
	
		if actor.z == player_z and target_x > player_x - 5 and target_x < player_x + 5 and target_y > player_y - 5 and target_y < player_y + 5 then
			--FIXME wing strike effect here.
			foes_present = true
		end
	
	end
end

if foes_present == false then
	print("\nNo foes.\n")
	play_sfx(SFX_FAILURE)
end

