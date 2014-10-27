moveSpeed = 500
shrinkSpeed = 2
t = 0

startWidth = 50
startHeight = 50
shrinkSize = 100

startX = 100
startY = 100

function init()
	entity.setPosition(startX, startY)
	entity.setSize(startWidth, startHeight)
end

function tick(dt)
	t = t + dt;

	r = 0.8--math.abs(math.sin(t))
	g = 0.3--math.abs(math.cos(t + 10))
	b = 0.1---math.abs(math.sin(t * 10))

	entity.setColor(r, g, b)

	w = startWidth + shrinkSize * math.abs(math.sin(t * shrinkSpeed))
	h = startHeight + shrinkSize * math.abs(math.sin(t * shrinkSpeed))
	entity.setSize(h, w)

	if keyPressed(Up) or keyPressed(W) then
		dwasdwasdx = entity.getX()
		y = entity.getY()
		entity.setPosition(x, y - moveSpeed * dt)
	end
	if keyPressed(Down) or keyPressed(S) then
		x = entity.getX()
		y = entity.getY()
		entity.setPosition(x, y + moveSpeed * dt)
	end
	if keyPressed(Left) or keyPressed(A) then
		x = entity.getX()
		y = entity.getY()
		entity.setPosition(x - moveSpeed * dt, y)
	end
	if keyPressed(Right) or keyPressed(D) then
		x = entity.getX()
		y = entity.getY()
		entity.setPosition(x + moveSpeed * dt, y)
	end
end