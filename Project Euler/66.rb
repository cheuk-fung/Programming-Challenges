# http://en.wikipedia.org/wiki/Pell's_equation
solution = (1..1000).reject { |d| Math.sqrt(d).floor**2 == d }.each_with_object([0, 0, 0]) do |d, res|
  x, y = -Math.sqrt(d).floor, 1
  hp, kp = -x, y
  hpp, kpp = 1, 0
  (0..Float::INFINITY).detect do |i|
    x, y = -x, (d - x**2) / y
    x -= y * (a = ((Math.sqrt(d) + x) / y).floor)
    hp, kp, hpp, kpp = a * hp + hpp, a * kp + kpp, hp, kp
    hp**2 - d * kp**2 == 1
  end
  res[0], res[1], res[2] = hp, kp, d if hp > res[0]
end

puts solution.inspect
