projectile = {}

function projectile:onCreate()
  --setThink("destroy", "destroy", 2)
  local duration = thisScript:getKV("duration")
  print(duration)
  thisEntity:destroy(duration)
end

function projectile:onTick()
  local speed = 200 * getDeltaTime()
  thisEntity:moveBy(speed, 0)
end


function projectile:destroy()
  entity:destroy()
end