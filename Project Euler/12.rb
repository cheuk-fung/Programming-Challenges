require "prime"
trinum = ->(n) { n * (n + 1) / 2 }
puts trinum[(1..Float::INFINITY).detect { |x| trinum[x].prime_division.reduce(1) { |prod, (_, count)| prod * (count + 1) } >= 500 }]
