--create("player_unit", 80.0, 0.0)
createEnt("player_unit", 80.0, 0.0)

--testing vector
--[[
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

local sub = v1 - v2
print(sub.x .. "," .. sub.y)

local foo = Vector(2.0, 3.0) * -Vector(2.0, 3.2)
print("foo:" .. foo.x .. "," .. foo.y)
]]
