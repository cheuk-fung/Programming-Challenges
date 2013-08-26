L = 1500000
count = Hash.new(0)
(1..Math.sqrt(L).floor).each do |m|
  (1...m).each do |n|
    next if m.gcd(n) > 1 || (m.odd? && n.odd?)
    a = m**2 - n**2
    b = 2 * m * n
    c = m**2 + n**2
    l = a + b + c
    break if l > L
    (1..(L / l)).each { |k| count[k * l] += 1 }
  end
end

puts count.count { |_, v| v == 1 }
