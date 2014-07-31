puts (2..(9**5 * 6)).reduce(0) { |ans, x| ans + (x.to_s.chars.map(&:to_i).reduce(0) { |sum, y| sum + y**5 } == x ? x : 0) }
