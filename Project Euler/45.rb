# triangle = ->(n) { n * (n + 1) / 2 }
pentagonal = ->(n) { n * (3 * n - 1) / 2 }
hexagonal = ->(n) { n * (4 * n - 2) / 2 }
p, h = 166, 144
pentagonal[p] < hexagonal[h] ? p += 1 : h += 1 while pentagonal[p] != hexagonal[h]
puts hexagonal[h]
