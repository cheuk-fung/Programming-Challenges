# can't prove that the first remarkable set found has the lowest sum

require "prime"

combine = ->(x, y) { x * 10**Math.log10(y + 1).ceil + y }
@can_cat = Hash.new { |h, (p1, p2)| h[[p1, p2]] = combine[p1, p2].prime? && combine[p2, p1].prime? }

def dfs(primes, remarkable_set, remain)
  if remain == 0
    puts remarkable_set.inspect
    puts remarkable_set.reduce(:+)
    exit
  end
  primes.each_with_index { |p, i| dfs(primes[(i + 1)..-1], remarkable_set + [p], remain - 1) if remarkable_set.all? { |x| @can_cat[[x, p]] } }
end

dfs([*Prime.each(10000)], [], 5)
