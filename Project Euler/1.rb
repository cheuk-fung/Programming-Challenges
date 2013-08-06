puts 1000.times.map { |x| x % 3 == 0 || x % 5 == 0 ? x : 0}.reduce(:+)
