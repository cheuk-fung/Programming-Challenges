puts File.open('names.txt', 'r').read.gsub('"', '').split(',').sort.map.with_index { |name, index| name.chars.map { |c| c.ord - 'A'.ord + 1 }.reduce(:+) * (index + 1) }.reduce(:+)
