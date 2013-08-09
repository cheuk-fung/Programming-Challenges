fib = Hash.new { |h, k| h[k] = k < 2 ? k : h[k - 1] + h[k - 2] }
puts (1..Float::INFINITY).take_while { |x| fib[x].to_s.length < 1000 }.last + 1
