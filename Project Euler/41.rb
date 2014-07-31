require "prime"
largest_pandigital_prime = ->() { 7.downto(1).each { |i| i.downto(1).to_a.permutation { |p| return p.join.to_i if p.join.to_i.prime? } } }
puts largest_pandigital_prime.call
