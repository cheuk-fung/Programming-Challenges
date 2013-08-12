require "prime"
max_length = 0
ans = 0
(-999..999).each do |a|
  Prime.each(1000) do |b|
    length = (0..Float::INFINITY).take_while { |n| (n**2 + a * n + b).prime? }.length
    max_length, ans = length, a * b if length > max_length
  end
end
puts ans
