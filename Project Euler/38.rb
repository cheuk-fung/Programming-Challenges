def gen_pandigital(x)
  cp = ''
  (1..9).each do |i|
    cp += (x * i).to_s
    break if cp.length >= 9
  end
  cp.length == 9 && !cp.include?('0') && cp.chars.uniq.size == 9 ? cp.to_i : -1
end

puts (1...10000).reduce(123456789) { |max_pandigital, x| [max_pandigital, gen_pandigital(x)].max }
