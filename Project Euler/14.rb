h = Hash.new { |h, k| h[k] = k == 1 ? 1 : (k.even? ? h[k / 2] : h[3 * k + 1]) + 1 }
puts (1..1000000).reduce(1) { |n, x| h[x] > h[n] ? x : n }
