require "prime"
puts Prime.each(10000).each_with_object([]) { |p, res| p > 1000 && (seq = p.to_s.chars.permutation.map(&:join).map(&:to_i).select { |per| per > 1000 && per.prime? }.uniq.sort).size >= 3 && seq[0] == p && seq.combination(3).map { |s| s[1] * 2 == s[0] + s[2] ? res << s.join : nil }.any? }.last
