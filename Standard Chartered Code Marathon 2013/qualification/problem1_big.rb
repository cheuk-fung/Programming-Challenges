count = Hash.new(0)
File.open('subway.log').each_line do |line|
  r = /entered station (?<id>\d+)/.match(line)
  count[r[:id]] += 1 if r
end

count = count.sort_by { |k, v| v }.reverse
count = count.take_while { |k, v| v == count[0][1] }

File.open('Result/output1.txt', 'w') do |file|
  file.puts count[0][1]
  file.puts count.map { |k, v| k }.join(" ")
end
