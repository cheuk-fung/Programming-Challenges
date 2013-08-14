require "prime"
truncatable_prime = []
Prime.each(Float::INFINITY).lazy.each do |p|
  next if p <= 7
  truncatable_prime << p if (1...p.to_s.length).all? { |i| p.to_s[0...i].to_i.prime? && p.to_s[i..-1].to_i.prime? }
  break if truncatable_prime.size == 11
end
puts truncatable_prime.reduce(:+)
