puts (2..1000000).reduce(Rational(0, 1)) { |left, x| [left, Rational(((x * 3.0 - 1) / 7).floor, x)].max }.numerator
