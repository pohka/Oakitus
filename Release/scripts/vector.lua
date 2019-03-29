-- define a new metatable to be shared by all vectors
local mt = {}

function Vector(x, y)
  local v = {
      x = x,
      y = y
  }
  setmetatable(v, mt)
  return v
end

-- define some vector operations such as addition, subtraction:
function mt.__add(a, b)
  return Vector(
      a.x + b.x,
      a.y + b.y
  )
end

function mt.__sub(a, b)
  return Vector(
      a.x - b.x,
      a.y - b.y
  )
end

function mt.__mul(a, b)
  if type(a) == "number" then
      return Vector(b.x * a, b.y * a)
  elseif type(b) == "number" then
      return Vector(a.x * b, a.y * b)
  end
  return a.x * b.x + a.y * b.y
end

-- check if two vectors with different addresses are equal to each other
function mt.__eq(a, b)
  return a.x == b.x and a.y == b.y
end

-- custom format when converting to a string:
function mt.__tostring(a)
  return "(" .. a.x .. ", " .. a.y .. ")"
end

local methods = {}
function methods.length(self)
    return math.sqrt(self.x^2 + self.y^2)
end

function methods.normalized(self)
  local length = self:length()
  return Vector(
    self.x / length,
    self.y / length
  )
end

function methods.dot(self, other)
  return ((self.x * other.x) + (self.y * other.y))
end

mt.__index = methods
