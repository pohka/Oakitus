
move = {}

if _G.val == nil then
  _G.val = 0
  --_G.playerEntID = 0;
end

function move:onCreate()
  log("in onCreate")
  local sprite = entity:getComponent(COMP_SPRITE)
  sprite:setSrc("pepe.png")
  --playerEntID = entity:getID()

  local player = PlayerResource:getPlayer(1)
  player:assignEnt(entity)

  print(KEY.C)
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

  if Input:isKeyDown(KEY.E) then
    local rb = entity:getComponent(COMP_RIGIDBODY2D)
    if rb == nil then
      log("rigidbody is nil")
    else
      local mass = rb:getMass()
    end

    local player = PlayerResource:getPlayer(1)
    if player ~= nil then
      local playerID = player:getPlayerID()
      log("playerID: " .. playerID)
    end
  end

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

  --testing assign and unassign entity
  if Input:isKeyDown(KEY.BACKSPACE) then
    local player = PlayerResource:getPlayer(1)
    local ent = player:getAssignedEnt()
    if ent ~= nil then
      player:unassignEnt()
    else
      player:assignEnt(entity)
    end
  end

  --entity:moveBy(moveX, moveY)
  local player = PlayerResource:getPlayer(1)
  local c = player:getAssignedEnt()
  --local c = Entity:findByID(playerEntID)
  if c ~= nil then
    c:moveBy(moveX, moveY)
  end
end

