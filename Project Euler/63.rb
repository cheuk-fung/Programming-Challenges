puts (1...10).reduce(0) { |count, k| count + (1..Float::INFINITY).detect { |n| (k**n).to_s.length < n }.downto(1).count { |n| (k**n).to_s.length == n } }
