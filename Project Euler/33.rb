puts [*1..9].product([*1..9]).product([*1..9]).select { |((a, b), c)| a < b && a != c && b != c && [a, c].permutation.map(&:join).product([b, c].permutation.map(&:join)).map { |ac, bc| Rational(ac, bc) }.include?(Rational(a, b)) }.reduce(Rational(1)) { |r, ((a, b), _)| r * Rational(a, b) }.denominator