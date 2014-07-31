# http://en.wikipedia.org/wiki/Partition_function_(number_theory)#Generating_function
pentagonal = ->(n) { [n * (3 * n - 1) / 2, n * (3 * n + 1) / 2] }
p = Hash.new { |h, k| h[k] = k < 0 ? 0 : k == 0 ? 1 : (1..Float::INFINITY).take_while { |i| k >= pentagonal[i][0] }.reduce(0) { |sum, i| sum + (-1)**(i - 1) * (p[k - pentagonal[i][0]] + p[k - pentagonal[i][1]]) } % 1000000 }
puts (1..Float::INFINITY).detect { |n| p[n] == 0 }
