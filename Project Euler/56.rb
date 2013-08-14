puts [*1...100].product([*1..100]).map { |a, b| (a**b).to_s.chars.map(&:to_i).reduce(:+) }.max
