require "prime"
max_n = 1
Prime.each(Float::INFINITY) do |p|
  break if max_n * p > 1000000
  max_n *= p
end
puts max_n
