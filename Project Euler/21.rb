require "prime"
h = Hash.new { |h, k| h[k] = k.prime_division.reduce(1) { |sum, (p, c)| sum * (p**(c + 1) - 1) / (p - 1) } - k }
puts (2...10000).select { |x| h[x] != x && h[h[x]] == x }.reduce(:+)
