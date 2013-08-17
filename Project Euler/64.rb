def period(n)
  x, y, p = -Math.sqrt(n).floor, 1, [] # (sqrt(n) + x) / y
  (1..Float::INFINITY).detect do |_|
    x, y = -x, (n - x**2) / y
    x -= y * (p << ((Math.sqrt(n) + x) / y).floor).last
    y == 1
  end
  p
end

puts (1..10000).count { |n| period(n).size.odd? if Math.sqrt(n).floor**2 != n }
