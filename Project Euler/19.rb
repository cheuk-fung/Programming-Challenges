require "date"
puts [*(1901..2000)].product([*(1..12)]).reduce(0) { |sum, (y, m)| sum + (Date.new(y, m, 1).wday == 0 ? 1 : 0) }
