require "prime"
puts Prime.each(2000000).reduce(:+)
