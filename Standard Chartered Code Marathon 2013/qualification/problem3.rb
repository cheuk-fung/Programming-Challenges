load "code_marathon.rb"

subway_stations, edges = CodeMarathon.parse_subway
distance, route = CodeMarathon.spfa_all(subway_stations, edges)

passengers = Hash.new
must = []
File.open('sample.log', 'rb:UTF-16LE').each_line do |line|
  line = line.encode('UTF-8')
  r = /station (?<sid>\d+) with card number (?<cid>\d+)/.match(line)
  if r
    if line.include?("entered")
      passengers[r[:cid]] = r[:sid].to_i
    else
      next if passengers[r[:cid]].nil?
      first, last = passengers[r[:cid]], r[:sid].to_i
      must << [first, last] if first != CodeMarathon::XIZHIMEN && last != CodeMarathon::XIZHIMEN && route[first][last].count(CodeMarathon::XIZHIMEN) == 2
    end
  end
end

min_count = must.size
min_stations = nil
[*0...subway_stations.size].each do |x|
  next if subway_stations[x].nil? || x == CodeMarathon::XIZHIMEN
  [*(x + 1)...subway_stations.size].each do |y|
    next if subway_stations[y].nil? || y == CodeMarathon::XIZHIMEN

    count = must.size
    must.each do |first, last|
      i, j = x, y
      new_distance = distance[first][i] + CodeMarathon::NEXT_STATION_TIME + distance[j][last]
      new_distance += CodeMarathon::CHANGE_LINE_TIME if i != first
      new_distance += CodeMarathon::CHANGE_LINE_TIME if j != last
      check_inc = new_distance <= distance[first][last] && (route[first][i] + route[j][last]).count(CodeMarathon::XIZHIMEN) < 2

      i, j = y, x
      new_distance = distance[first][i] + CodeMarathon::NEXT_STATION_TIME + distance[j][last]
      new_distance += CodeMarathon::CHANGE_LINE_TIME if i != first
      new_distance += CodeMarathon::CHANGE_LINE_TIME if j != last
      check_dec = new_distance <= distance[first][last] && (route[first][i] + route[j][last]).count(CodeMarathon::XIZHIMEN) < 2

      count -= 1 if check_inc || check_dec
    end

    min_count, min_stations = [count, [x, y]] if count < min_count
  end
end

File.open('SampleResult/output3.txt', 'w') do |file|
  file.puts min_count
  file.puts min_stations.join(" ")
end
