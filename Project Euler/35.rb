require "prime"
puts Prime.each(1000000).count { |p| (1...p.to_s.length).all? { |i| p.to_s.chars.rotate(i).join.to_i.prime? } }
