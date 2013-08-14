def recurring_cycle_length(x)
  residue = 1
  h = {}
  tail = (1..Float::INFINITY).detect { |i| h[residue = residue * 10 % x] ? true : !(h[residue] = i) }
  residue == 0 ? 0 : tail - h[residue]
end

puts (1...1000).reduce { |ans, x| recurring_cycle_length(x) > recurring_cycle_length(ans) ? x : ans }
