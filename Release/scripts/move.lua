
move = {}
_G.val = 0

function move:tick() 
  if Input:isKeyDown("W") then
    print("tick in lua: " .. val)
    
    local e = createEnt("sample", -200.0 + val, 0.0)
    val = val + 100

    if e ~= nil then
      print(e:getID() .. "=" .. e:getName())
    end


  end
end

function other()
  print("other in luia")
end


return foo
--[[

_G.foo = 1

if isKeyDown("W") then
  print("key down")
  foo = foo + 1
elseif isKeyUp("W") then
  print("key up")
elseif isKeyPressed("W") then
  print("pressed")
end

if isMouseButtonDown(0) then
  print("mouse left down")
end


if isKeyUp("A") then
  print("creating ent")
  createEnt("sample", 30.0, 0.0)
end

local v = Vec2(0.0, 1.0)
--v:setX(3.0)
--print(v:getX())
--print(v.x)

local v1 = Vec3(1.0, 2.0, 3.0)
--v1:x = 3.0
v1.x = v1.x + 3.0
--v1:foo()
--print c val
--local str = "(" .. v1.x .. ", " .. v1.y .. ", " .. v1.z .. ")"
--print(str)

--v1 + v1
local entID = 1
--print(foo)
--setEntPos(entID, v1)


function tick(x, y)
  print("ticking in lua")
end
]]
