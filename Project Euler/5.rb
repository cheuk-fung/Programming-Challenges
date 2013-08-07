require "prime"
puts Prime.each(20).reduce(1) { |prod, x| prod * x ** (1..20).reduce(0) { |max_count, y| [max_count, (1..Float::INFINITY).take_while { |_| y % x == 0 ? (y /= x) >= 1 : false }.last || 0].max } }
