puts (1..12000).reduce(0) { |count, x| count + (((x + 1) / 3.0).ceil..((x - 1) / 2.0).floor).count { |n| x.gcd(n) == 1 } }
