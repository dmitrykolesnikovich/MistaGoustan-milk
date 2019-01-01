local player = {
	speed = 2,
	flipped_x = false
 }

function player:begin()
	self.actor:set_animation('idle')
	self.actor:make_cam_target()
end

function player:update()
	if Input.get_key_pressed(102) then
		game.window:toggle_fullscreen()
	end

	if Input.get_key_pressed(114) then
		game:loadScene('res/testmap.xml');
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

	if (inputvec == Vector2D.new(0, 0)) then
		self.actor:set_animation('idle')
	else
		self.actor:set_animation('run')
	end

	inputvec = inputvec * self.speed

	self.actor:move(inputvec.x, inputvec.y)
end

function player:on_collision(e)
	if e.other.actor.name == 'door' then
		game:loadScene('res/testmap.xml')
	end
end

function player:destroyed()
end

return player