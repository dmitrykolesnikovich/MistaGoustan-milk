-- player script

local playerScript = {
	speed = 2,
	f_down_last_frame = false,
	flipped_x = false
 }

function playerScript:begin()
	self.actor:set_animation('main')
end

function playerScript:update()
	-- hackish. will be hacking until Input class doesn't suck
	if Input.getKey(102) and not self.f_down_last_frame then
		self.f_down_last_frame = true
		game.window:toggle_fullscreen()
	end
	if not Input.getKey(102) and self.f_down_last_frame then
		self.f_down_last_frame = false
	end

	local inputvec = Vector2D.new(0, 0)

	if Input.getKey(119) then
		inputvec.y = -1
	end
	if Input.getKey(115) then
		inputvec.y = 1
	end
	if Input.getKey(97) then
		inputvec.x = -1

		if (not self.flipped_x) then
			self.flipped_x = true
			self.actor:flip_x()
		end
	end
	if Input.getKey(100) then
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