local playerBehavior = { }

function playerBehavior:begin()	
	print(self.actor.name)
end

function playerBehavior:update()
end

function playerBehavior:destroyed()
end

return playerBehavior