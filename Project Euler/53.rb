combination = Hash.new { |h, (n, r)| h[[n, r]] = r == 0 || r == n ? 1 : h[[n - 1, r]] + h[[n - 1, r - 1]] }
puts (1..100).map { |n| (1..n).map { |r| combination[[n, r]] }.select(&1000000.method(:<)).size }.reduce(:+)
