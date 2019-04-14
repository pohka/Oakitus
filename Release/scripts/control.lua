control = {}

function control:onCreate()
  
end

function control:onTick()
  local player = PlayerResource:getPlayer(1)
  local unit = player:getAssignedEnt()

  --control.val = 1
  --print("val" .. control.val)

  --movement
  local speed = 2
  local moveX = 0
  local moveY = 0

  if Input:isKeyPressed(KEY.W) then
    moveY = speed
  end
  if Input:isKeyPressed(KEY.S) then
    moveY = -speed
  end
  if Input:isKeyPressed(KEY.A) then
    moveX = -speed
  end
  if Input:isKeyPressed(KEY.D) then
    moveX = speed
  end

  
  if unit ~= nil then
    unit:moveBy(moveX, moveY)
  end

  --shooting
  if Input:isKeyDown(KEY.SPACE) then
    local pos = unit:getPosition()
    local bullet = Game:createEnt("bullet", pos)
  end

end