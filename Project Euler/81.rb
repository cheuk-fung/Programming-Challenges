f = Hash.new(Float::INFINITY)
File.open('matrix.txt', 'r').each_line.with_index { |line, i| line.split(',').map(&:to_i).each_with_index { |x, j| f[[i, j]] = i == 0 && j == 0 ? x : [f[[i - 1, j]], f[[i, j - 1]]].min + x } }
puts f.values.last
