def check(x)
  x = x.to_s
  x == x.reverse
end

def count(x)
  l, r = 0, @valid.length
  while l < r
    mid = (l + r - 1) >> 1
    if @valid[mid] <= x
      l = mid + 1
    else
      r = mid
    end
  end
  l
end

@valid = []
10000010.times { |x| @valid << x * x if check(x) && check(x * x) }

tasks = gets.to_i
tasks.times do |task|
  a, b = gets.split(" ").map(&:to_i)
  puts "Case ##{task + 1}: #{count(b) - count(a - 1)}"
end
