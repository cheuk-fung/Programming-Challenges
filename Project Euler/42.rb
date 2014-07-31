check_triangle_number = ->(k) { Math.sqrt(1 + 8 * k).floor**2 == 1 + 8 * k && Math.sqrt(1 + 8 * k).floor.odd? ? 1 : 0 }
puts File.open('words.txt', 'r').read.gsub('"', '').split(',').reduce(0) { |sum, word| sum + check_triangle_number[word.chars.map { |c| c.ord - 'A'.ord + 1 }.reduce(:+)] }
