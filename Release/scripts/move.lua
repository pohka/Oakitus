
move = {}

if _G.val == nil then
  _G.val = 0
  _G.playerEntID = 0;
end

function move:onCreate()
  log("in onCreate")
  local sprite = entity:getComponent(COMP_SPRITE)
  sprite:setSrc("pepe.png")
  playerEntID = entity:getID()
end

function move:onTick() 
  if Input:isKeyDown("Q") then
    local e = Entity:create("sample", Vector(-200.0 + val, 0.0))
    playerEntID = e:getID()
    local sprite = e:getComponent(COMP_SPRITE)
    if sprite == nil then
      log("sprite is nil")
    else
      local src = sprite:getSrc()
      if src == nil then
        log("src is nil")
      else
        log("src:" .. src)
      end

      sprite:setSrc("pepe.png")
    end
    
    val = val + 100

    --entity:moveTo(val, 100.0)
    log("x:" .. val)


    if e ~= nil then
      log(e:getID() .. "=" .. e:getName())
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

  --entity:moveBy(moveX, moveY)

  local c = Entity:findByID(playerEntID)
  if c ~= nil then
    c:moveBy(moveX, moveY)
  end
end
