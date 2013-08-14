require "prime"
Prime.each(Float::INFINITY).each do |p|
  ps = p.to_s
  (1..(ps.length - 1)).each do |l|
    [*0...(ps.length - 1)].combination(l).select { |comb| ps[comb[0]] <= "4" && comb.map { |c| ps[c] == ps[comb[0]] }.all? }.each do |comb|
      q = p
      eps = comb.reduce(0) { |sum, i| sum += 10**(ps.length - i - 1) }
      if ((ps[comb[0]].to_i + 1)..9).map { |_| (q += eps).to_i.prime? ? 1 : 0 }.reduce(:+) == 7
        puts p
        exit
      end
    end
  end
end
