dp = [[1] * 21] + [[1] * 20].transpose
puts [*1..20].product([*1..20]).map { |(x, y)| dp[x][y] = dp[x - 1][y] + dp[x][y - 1] }.last
