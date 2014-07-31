factorial = (0..9).map { |x| (1..x).reduce(:*) || 1 }
puts (10..(factorial[9] * 7)).select { |x| x.to_s.chars.map { |c| factorial[c.to_i] }.reduce(:+) == x }.reduce(:+)
