--create("player_unit", 80.0, 0.0)
createEnt("player_unit", 80.0, 0.0)

local v1 = Vector(2.0, 0.0)
local v2 = Vector(0.5, 0.866)
print(v1.x .. "," .. v1.y)
local s = v1:toStr()



print(s)

local a = v1:normalized()
local b = v2:normalized()
local dot = a:dot(b)
print("dot:" .. dot)

print("len3D:" .. v1:length())
print("len2D:" .. v1:length2D())

local cross = a:cross(b)
local crossStr = cross:toStr()
print("cross:" .. crossStr)

--local add = a + b + b
local sub = v1 - v2
print(sub.x .. "," .. sub.y)

local foo = Vector(2.0, 3.0) * -Vector(2.0, 3.2)
print("foo:" .. foo.x .. "," .. foo.y)

  --[[
require("scripts/vector")


function activate()
  print("active")
  create("player_unit", 0.0, 0.0)
  --create("sample", 80.0, 0.0)

  print(_VERSION)

  

 -- local obj = MyObject(42)
--print(obj:get())    -- 42


  local a = Vector(0,1)
  local b = Vector(1,0)
  local c = a + b
  local d = a * 4;
  print(c.x .. "," .. c.y)
  print(d)
  local dot = a:dot(b)
  print("dot:" .. dot)

  local mag = a:length()
  print("mag:" .. mag)
  local n = a:normalized()
  print("normalized:")
  print(n)
  --v.log()
  local a = create("saample", -40.0, 0.0)
  print("a:" .. a)
  --local ent = newEntity();
  --local ent = {
  --  { "sprite", "board.png", 64, 64 }
  --}

  --addCommand("move", 1)
 
end

activate()

 ]]
