def d(x)
  return x if x < 10
  (1..Float::INFINITY).each do |i|
    count = i * (10**i - 10**(i - 1))
    return x % i == 0 ? (x / i  - 1) % 10 : (10**(i - 1) + (x / i)).to_s.chars[x % i - 1].to_i if count >= x
    x -= count
  end
end

puts (0..6).reduce(1) { |prod, k| prod * d(10**k) }
