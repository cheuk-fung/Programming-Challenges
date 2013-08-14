require "prime"
max_length = 0
ans = 0
(-999..999).each do |a|
  Prime.each(1000) do |b|
    length = (1..Float::INFINITY).detect { |n| !(n**2 + a * n + b).prime? }
    max_length, ans = length, a * b if length > max_length
  end
end
puts ans
