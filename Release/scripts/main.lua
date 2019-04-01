require("scripts/vector")



function activate()
  print("active")
  create("sample", 40.0, 0.0)
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

  addCommand("move", 1)

end

activate()
