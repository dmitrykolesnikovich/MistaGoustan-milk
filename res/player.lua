-- player script

local playerScript = {
	speed = 2,
	flipped_x = false
 }

function playerScript:begin()
	self.actor:set_animation('main')
end

function playerScript:update()
	if Input.get_key_pressed(102) then
		game.window:toggle_fullscreen()
	end

	local inputvec = Vector2D.new(0, 0)

	if Input.get_key(119) then
		inputvec.y = -1
	end
	if Input.get_key(115) then
		inputvec.y = 1
	end
	if Input.get_key(97) then
		inputvec.x = -1

		if (not self.flipped_x) then
			self.flipped_x = true
			self.actor:flip_x()
		end
	end
	if Input.get_key(100) then
		inputvec.x = 1

		if (self.flipped_x) then
			self.flipped_x = false
			self.actor:flip_x()
		end
	end

	inputvec.x = inputvec.x * self.speed
	inputvec.y = inputvec.y * self.speed

	self.actor:move(inputvec.x, inputvec.y)
end

function playerScript:destroyed()
end

return playerScript