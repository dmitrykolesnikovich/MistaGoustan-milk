local playerBehavior = { }

function playerBehavior:begin()	
end

function playerBehavior:update()
	local inputvec = Vector2D.new(0, 0)
	local speed = 3

	if Input.getKey(119) then
		inputvec.y = -1
	end
	if Input.getKey(115) then
		inputvec.y = 1
	end
	if Input.getKey(97) then
		inputvec.x = -1
	end
	if Input.getKey(100) then
		inputvec.x = 1
	end

	inputvec.x = inputvec.x * speed
	inputvec.y = inputvec.y * speed

	actor.move(self.actor, inputvec.x, inputvec.y)
end

function playerBehavior:destroyed()
end

return playerBehavior