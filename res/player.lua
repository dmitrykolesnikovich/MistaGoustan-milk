-- player script

local playerScript = {
 }

function playerScript:begin()	
end

function playerScript:update()
	local inputvec = Vector2D.new(0, 0)
	local speed = 2

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

	self.actor:move(inputvec.x, inputvec.y)
end

function playerScript:destroyed()
end

return playerScript