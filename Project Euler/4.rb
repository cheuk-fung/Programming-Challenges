puts (100..999).reduce(101) { |s, x| (100..999).reduce(s) { |t, y| (p = x * y) > t && p.to_s == p.to_s.reverse ? p : t } }
