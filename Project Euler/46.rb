require "prime"
puts (2..Float::INFINITY).detect { |x| x.odd? && !x.prime? && !Prime.each(x).any? { |p| (x - p).even? && Math.sqrt((x - p) / 2).to_i**2 == (x - p) / 2 } }
