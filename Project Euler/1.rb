puts 1000.times.select { |x| x % 3 == 0 || x % 5 == 0 }.reduce(:+)
