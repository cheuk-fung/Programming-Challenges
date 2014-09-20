def check(ztime, xtime, t)
  ztime.each do |a, b|
    xtime.each do |c, d|
      break if c + t > b
      next if b < c + t
      return true if (c + t).between?(a, b) || (d + t).between?(a, b)
      return true if a.between?(c + t, d + t) || b.between?(c + t, d + t)
    end
  end

  false
end

p, q, l, r = gets.split.map(&:to_i)

ztime = []
p.times { ztime << gets.split.map(&:to_i) }

xtime = []
q.times { xtime << gets.split.map(&:to_i) }

puts l.upto(r).select { |t| check(ztime, xtime, t) }.size
