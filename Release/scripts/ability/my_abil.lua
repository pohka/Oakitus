my_abil = {}

function my_abil:onSpellCast()
  print("on spell cast")
  if thisAbility ~= nil then
    local abilName = thisAbility:getName()
    local entName = thisEntity:getName()
    print(entName .. ":" .. abilName)

    local pos = thisEntity:getPosition()
    local bullet = Game:createEnt("bullet", pos)
    print("created bullet")
  end
end

function my_abil:onSpellStart()
  print("on spell start")
end
