
move = {}

if _G.val == nil then
  _G.val = 0
end

function move:onCreate()
  log("in onCreate")
end

function move:onTick() 
  if Input:isKeyDown("Q") then
    local e = Entity:create("sample", Vector(-200.0 + val, 0.0))
    val = val + 100

    --entity:moveTo(val, 100.0)
    log("x:" .. val)


    if e ~= nil then
      logd(e:getID() .. "=" .. e:getName())
    end


  end

  local speed = 2
  local moveX = 0
  local moveY = 0

  if Input:isKeyPressed("W") then
    moveY = speed
  end
  if Input:isKeyPressed("S") then
    moveY = -speed
  end
  if Input:isKeyPressed("A") then
    moveX = -speed
  end
  if Input:isKeyPressed("D") then
    moveX = speed
  end

  entity:moveBy(moveX, moveY)
end

