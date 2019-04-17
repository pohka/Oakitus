projectile = {}

function projectile:onCreate()
  setThink("destroy", "destroy", 2)
end

function projectile:onTick()
  local speed = 200 * getDeltaTime()
  entity:moveBy(speed, 0)
end


function projectile:destroy()
  entity:destroy()
end