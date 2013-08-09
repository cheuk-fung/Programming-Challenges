require "set"
s = Set.new
(2..100).each { |a| (2..100).each { |b| s.add(a**b) } }
puts s.size
