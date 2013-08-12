require "prime"
puts (2..Float::INFINITY).take_while { |x| x.even? || x.prime? || Prime.each(x).map { |p| (x - p).even? && Math.sqrt((x - p) / 2).to_i**2 == (x - p) / 2 }.any? }.last + 1
