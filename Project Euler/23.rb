require "prime"
abundant = (2..28123).select { |x| x.prime_division.reduce(1) { |sum, (p, k)| sum * (p**(k + 1) - 1) / (p - 1) } - x > x }
h = {}
abundant.each { |x| abundant.each { |y| h[x + y] = true if y >= x && x + y <= 28123 } }
puts (1..28123).reduce(0) { |sum, x| sum + (h[x] ? 0 : x) }
