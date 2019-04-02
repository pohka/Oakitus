if isKeyDown("W") then
  print("key down")
elseif isKeyUp("W") then
  print("key up")
elseif isKeyPressed("W") then
  print("pressed")
end

if isMouseButtonDown(0) then
  print("mouse left down")
end