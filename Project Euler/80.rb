def long_sqrt(n)
  pow = 2**(100 / Math.log10(2)).ceil

  root = Math.sqrt(n).to_s.chop.split('.')
  dec_length = (100 - root[0].length) * 2
  root = (root.join + '0' * (100 - root[0].length - root[1].length)).to_i

  (root + pow)**2 / 10**dec_length >= n ? pow /= 2 : root += pow while pow > 0
  root
end

puts (1..100).select { |n| Math.sqrt(n).floor**2 != n}.reduce(0) { |sum, n| sum + long_sqrt(n).to_s.chars.map(&:to_i).reduce(:+) }
