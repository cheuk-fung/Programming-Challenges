puts (2 + 99.downto(1).reduce(Rational(0, 1)) { |sum, i| 1 / ((i % 3 == 2 ? 2 * (i / 3.0).ceil : 1) + sum) }).numerator.to_s.chars.map(&:to_i).reduce(:+)
