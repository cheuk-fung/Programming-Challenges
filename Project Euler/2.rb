puts (1..Float::INFINITY).lazy.map { |x| x.times.reduce([0, 1]) { |(a, b), _| [b, a + b] }[0] }.take_while { |fx| fx <= 4000000 }.select { |fx| fx.even? }.reduce(:+)
