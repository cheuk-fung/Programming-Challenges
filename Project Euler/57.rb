check = ->(r) { r.numerator.to_s.length > r.denominator.to_s.length }
part = Hash.new { |h, k| h[k] = k == 1 ? Rational(1, 2) : 1 / (2 + h[k - 1 ]) }
puts (1..1000).count { |i| check[1 + part[i]] }
