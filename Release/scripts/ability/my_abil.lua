my_abil = {}

function my_abil:onSpellCast()
  print("on spell cast")
  if thisAbility ~= nil then
    --local mana = thisAbility:getManaCost()
    --local owner = thisAbility:getUnitOwner()
    
  end
end

function my_abil:onSpellStart()
  print("on spell start")
  local pos = thisEntity:getPosition()
  local bullet = Game:createEnt("bullet", pos)
  thisAbility:levelUp()
end
