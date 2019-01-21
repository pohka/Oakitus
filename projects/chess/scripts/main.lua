
print("hello world")

function precacheResouces()
  precache("texture", "board.png");
end

function activate()
  print("active")

  --local ent = newEntity();
  --local ent = {
  --  { "sprite", "board.png", 64, 64 }
  --}

end

precacheResouces()
activate()
