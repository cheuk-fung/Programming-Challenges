require "prime"
puts [Prime.each(Math.sqrt(n = 600851475143)).select { |x| n % x == 0 }.reduce(0) { |memo, x| [memo, (n /= x while n % x == 0) || x].max }].push(n).max
