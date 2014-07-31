max_string = ''
[*1..10].permutation do |p|
  next if p[0..4].include?(10)

  sum = [[p[9], p[4], p[3]],
         [p[8], p[3], p[2]],
         [p[7], p[2], p[1]],
         [p[6], p[1], p[0]],
         [p[5], p[0], p[4]]
  ]
  if sum.map { |line| line.reduce(:+) }.all?(&sum[0].reduce(:+).method(:==))
    index = sum.each.with_index.with_object([0]) { |(line, i), min_first| min_first[0] = i if line[0] < sum[min_first[0]][0] }[0]
    now = (index..(index + 4)).reduce('') { |s, i| s += sum[i % 5].join }
    max_string = [max_string, now].max if now.length == 16
  end
end

puts max_string
