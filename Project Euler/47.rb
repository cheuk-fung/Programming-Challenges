require "prime"
puts (1..Float::INFINITY).each_cons(4).detect { |nums| nums.all? { |x| x.prime_division.size == 4 } }[0]
