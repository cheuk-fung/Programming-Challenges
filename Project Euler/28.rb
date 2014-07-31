n = 1001 / 2
# puts (1..n).reduce(1) { |sum, i| sum + (4 * i**2 - 2 * i + 1) * 4 + 12 * i }
puts 1 + 4 * (4 * n * (n + 1) * (2 * n + 1) / 6 + n * (n + 1) / 2 + n)
