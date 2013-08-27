mat = []
File.open('matrix.txt', 'r').each_line { |line| mat << line.split(',').map(&:to_i) }

f = Hash.new(Float::INFINITY)
(0...mat.length).each { |i| f[[i, 0]] = mat[i][0] }
(1...mat[0].length).each do |j|
  (0...mat.length).each { |i| f[[i, j]] = [f[[i - 1, j]], f[[i, j - 1]]].min + mat[i][j] }
  (0...(mat.length - 1)).reverse_each { |i| f[[i, j]] = [f[[i, j]], f[[i + 1, j]] + mat[i][j]].min }
end

puts (0...mat.length).reduce(Float::INFINITY) { |min_path, i| [min_path, f[[i, mat[0].length - 1]]].min }
