local running = true
local index = -1
while (running) do
  index = index + 1
  wait(1)
  if (index == 100) then
    running = false
  end
end
