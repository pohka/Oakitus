
move = {}
_G.val = 0

function move:tick() 
  if Input:isKeyDown("Q") then
    print("tick in lua: " .. val)
    
    local e = createEnt("sample", -200.0 + val, 0.0)
    val = val + 100

    entity:moveTo(val, 100.0)
    print("x:" .. val)

    if e ~= nil then
      print(e:getID() .. "=" .. e:getName())
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

