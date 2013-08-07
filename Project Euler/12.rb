require "prime"
trinum = ->(n) { n * (n + 1) / 2 }
puts trinum[(1..Float::INFINITY).take_while { |x| Prime.prime_division(trinum[x]).reduce(1) { |prod, (_, count)| prod * (count + 1) } < 500 }.last + 1]
