def recurring_cycle_length(x)
  residue = 1
  h = {}
  tail = (1..Float::INFINITY).take_while { |i| h[residue = residue * 10 % x] ? false : (h[residue] = i) }.last
  residue == 0 ? 0 : tail - h[residue] + 1
end

puts (1...1000).reduce { |ans, x| recurring_cycle_length(x) > recurring_cycle_length(ans) ? x : ans }
