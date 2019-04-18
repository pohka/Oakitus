control = {}

function control:onCreate()
  script:setKV("score", 100)
end

function control:onTick()
  local player = PlayerResource:getPlayer(1)
  local unit = player:getAssignedEnt()

  --control.val = 1
  --print("val" .. control.val)

  --movement
  local speed = 200
  local moveX = 0
  local moveY = 0

  if Input:isKeyPressed(KEY.W) then
    moveY = speed
  end
  if Input:isKeyPressed(KEY.S) then
    moveY = moveY -speed
  end
  if Input:isKeyPressed(KEY.A) then
    moveX = -speed
  end
  if Input:isKeyPressed(KEY.D) then
    moveX = moveX + speed
  end

  
  if unit ~= nil then
    moveX = moveX * getDeltaTime()
    moveY = moveY * getDeltaTime()
    unit:moveBy(moveX, moveY)
  end

  --shooting
  if Input:isKeyDown(KEY.SPACE) then
    local score = script:getKV("score")
    print(score)
    score = score + 100;
    script:setKV("score", score)

    local pos = unit:getPosition()
    local bullet = Game:createEnt("bullet", pos)
    local proj = bullet:getScript("projectile")
    --proj:setKV("duration", 1)
  end

  --print("in lua")

  if Input:isKeyPressed(KEY.U) then
   -- return -1
   setThink("test", "test", 2)
  end
end
