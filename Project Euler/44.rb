p = ->(n) { n * (3 * n - 1) / 2 }
check_p = ->(k) { p[x = (1 + Math.sqrt(1 + 24 * k).floor) / 6] == k ? x : nil }
(1..Float::INFINITY).each do |k|
  (1...k).each do |j|
    if check_p[p[k] - p[j]] && check_p[p[j] + p[k]]
      puts p[check_p[p[k] - p[j]]]
      exit
    end
  end
end
