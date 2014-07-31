def run(n, length, factorial)
  transform = ->(x) { x.to_s.chars.map(&:to_i).map { |k| factorial[k] }.reduce(:+) }

  k = n
  count = (1..60).detect { |_| length[k = transform[k]] }
  if count
    length[n] = length[k] + count;

    k = n
    (1...count).each { |i| length[k = transform[k]] = length[n] - i }

    length[n]
  else
    61
  end
end

length = Hash.new
length[145] = 1
length[169] = length[363601] = length[1454] = 3
length[871] = length[45361] = 2
length[872] = length[45362] = 2
factorial = (0..9).map { |x| x == 0 ? 1 : (1..x).reduce(:*) }
puts (1...1000000).count { |n| (length[n] ||= run(n, length, factorial)) == 60 }
