require "prime"
h = Hash.new { |h, k| h[k] = Prime.prime_division(k).reduce(1) { |sum, (p, c)| sum * (p**(c + 1) - 1) / (p - 1) } - k }
puts (2...10000).select { |x| h[x] != x && h[h[x]] == x }.reduce(:+)
