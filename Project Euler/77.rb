require "prime"
primes = Prime.each
p = [primes.next]
ways = Hash.new { |h, (i, j)| h[[i, j]] = i < 0 ? 0 : i == 0 ? 1 : j < 0 ? 0 : h[[i - p[j], j]] + h[[i, j - 1]] }
puts (2..Float::INFINITY).detect { |n| ways[[n, (n > p.last ? p << primes.next : p).length - 1]] > 5000 }
