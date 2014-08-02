load "code_marathon.rb"

subway_stations, edges = CodeMarathon.parse_subway
distance, route = CodeMarathon.spfa_all(subway_stations, edges)

passengers = Hash.new
count = 0
File.open('sample.log', 'rb:UTF-16LE').each_line do |line|
  line = line.encode('UTF-8')
  r = /station (?<sid>\d+) with card number (?<cid>\d+)/.match(line)
  if r
    if line.include?("entered")
      passengers[r[:cid]] = r[:sid].to_i
    else
      next if passengers[r[:cid]].nil?
      first, last = passengers[r[:cid]], r[:sid].to_i
      count += 1 if first != CodeMarathon::XIZHIMEN && last != CodeMarathon::XIZHIMEN && route[first][last].count(CodeMarathon::XIZHIMEN) == 2
    end
  end
end

File.open('SampleResult/output2.txt', 'w') { |file| file.puts count }
