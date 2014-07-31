require "prime"
prime_count = 8
(5..Float::INFINITY).each do |i|
  side_length = i * 2 - 1
  prime_count += (1..3).count { |j| (side_length**2 - (side_length - 1) * j).prime? }
  if prime_count.to_f / (side_length * 2 - 1) < 0.1
    puts side_length
    break
  end
end
