require "prime"
phi = ->(n) { n.prime_division.reduce(1) { |prod, (p, k)| prod * p**(k - 1) * (p - 1) } }
puts (2..1000000).reduce(0) { |count, n| count + phi[n] }
