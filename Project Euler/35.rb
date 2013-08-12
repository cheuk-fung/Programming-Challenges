require "prime"
puts Prime.each(1000000).select { |p| (1...p.to_s.length).map { |i| p.to_s.chars.rotate(i).join.to_i.prime? }.all? }.size
