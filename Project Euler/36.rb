puts (1...1000000).select { |x| x.to_s == x.to_s.reverse && x.to_s(2) == x.to_s(2).reverse }.reduce(:+)
