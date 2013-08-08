d = File.open('triangle.txt', 'r').readlines.map(&:split).map { |row| row.map(&:to_i) }
f = [0] * d.last.length
d.length.times { |i| (d[i].length - 1).downto(0) { |j| f[j] = d[i][j] + [f[j], j > 0 ? f[j - 1] : 0].max } }
puts f.max
