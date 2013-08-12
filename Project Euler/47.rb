require "prime"
puts (1..Float::INFINITY).take_while { |x| !(0..3).map { |i| (x + i).prime_division.size == 4 }.all? }.last + 1
