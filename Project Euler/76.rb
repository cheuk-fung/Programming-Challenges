ways = Hash.new { |h, (i, j)| h[[i, j]] = i < 0 ? 0 : i == 0 ? 1 : j == 0 ? 0 : h[[i - j, j]] + h[[i, j - 1]] }
puts ways[[100, 100]] - 1
