require "prime"
max_length = 0
ans = 0
(-999..999).each do |a|
  Prime.each(1000) do |b|
    length = (0..Float::INFINITY).take_while { |n| Prime.prime?(n**2 + a * n + b) }.length
    if length > max_length
      max_length = length
      ans = a * b
    end
  end
end
puts ans
