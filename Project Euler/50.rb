require "prime"
UPPER_LIMIT = 1000000
p = [0] + Prime.each(UPPER_LIMIT).to_a
p.map!.with_index { |x, i| i > 0 ? x + p[i - 1] : x }
max_length = 21
the_prime = 953
(2...p.length).each do |i|
  ((i + max_length)...p.length).each do |j|
    break if p[j] - p[i - 1] >= UPPER_LIMIT
    if (p[j] - p[i - 1]).prime?
      max_length = j - i + 1 
      the_prime = p[j] - p[i - 1]
    end
  end
end
puts the_prime
