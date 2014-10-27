move = 100

function init()
	entity.setPosition(100, 100)
	entity.setSize(50, 50)
end

function tick(dt)
	x = entity.getX()
	y = entity.getY()

	entity.setColor(0.8, 0.3, 0.1)

	if keyPressed(Up) then
		entity.setPosition(x, y - move * dt)
	end
	if keyPressed(Down) then
		entity.setPosition(x, y + move * dt)
	end
	if keyPressed(Left) then
		entity.setPosition(x - move * dt, y)
	end
	if keyPressed(Right) then
		entity.setPosition(x + move * dt, y)
	end
end