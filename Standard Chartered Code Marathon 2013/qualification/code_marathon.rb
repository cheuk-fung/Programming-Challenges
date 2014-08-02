module CodeMarathon
  NEXT_STATION_TIME = 150
  CHANGE_LINE_TIME = 191
  XIZHIMEN = 35

  class << self
    def parse_subway
      subway_lines = []
      subway_stations = []
      edges = Hash.new { |h, k| h[k] = [] }
      File.open('subway.txt', 'rb:cp936').each_line do |line|
        line = line.encode('UTF-8').split
        if line.size == 0		# empty line
          next
        elsif line.size == 1		# subway line begin
          subway_lines << []
        else				# subway station
          lid = subway_lines.size - 1	# line id
          sid = line[0]
          sid = sid.to_i		# station id

          if !subway_lines[lid].empty?
            eps = sid == XIZHIMEN || subway_lines[lid].last == XIZHIMEN ? 1 : 0
            edges[CodeMarathon.pid_encode(lid, sid)] << [CodeMarathon.pid_encode(lid, subway_lines[lid].last), NEXT_STATION_TIME + eps]
            edges[CodeMarathon.pid_encode(lid, subway_lines[lid].last)] << [CodeMarathon.pid_encode(lid, sid), NEXT_STATION_TIME + eps]
          end
          subway_lines.last << sid

          subway_stations[sid] = [] if subway_stations[sid].nil?
          subway_stations[sid].each do |previous_lid|
            eps = sid == XIZHIMEN ? 1 : 0
            edges[CodeMarathon.pid_encode(lid, sid)] << [CodeMarathon.pid_encode(previous_lid, sid), CHANGE_LINE_TIME + eps]
            edges[CodeMarathon.pid_encode(previous_lid, sid)] << [CodeMarathon.pid_encode(lid, sid), CHANGE_LINE_TIME + eps]
          end
          subway_stations[sid] << lid
        end
      end

      [subway_stations, edges]
    end

    def pid_encode(line, station)
      (line << 10) | station
    end

    def pid_decode(pid)
      [pid >> 10, pid & ((1 << 10) - 1)]
    end

    def spfa(first, subway_stations, edges)
      distance = Hash.new(Float::INFINITY)
      previous = Hash.new
      queue = []
      in_queue = Hash.new(false)

      subway_stations[first].each do |line|
        pid = pid_encode(line, first)
        distance[pid] = 0
        queue << pid
        in_queue[pid] = true
      end

      queue.each do |pid|
        in_queue[pid] = false
        current_distance = distance[pid]

        edges[pid].each do |next_pid, next_distance|
          if current_distance + next_distance < distance[next_pid]
            distance[next_pid] = current_distance + next_distance
            previous[next_pid] = pid
            if !in_queue[next_pid]
              queue << next_pid
              in_queue[next_pid] = true
            end
          end
        end
      end

      result_distance = Hash.new
      route = Hash.new
      (0...subway_stations.size).each do |last|
        next if subway_stations[last].nil?
        result_distance[last], min_line = subway_stations[last].reduce([Float::INFINITY, -1]) { |(r_distance, r_line), line| distance[pid_encode(line, last)] < r_distance ? [distance[pid_encode(line, last)], line] : [r_distance, r_line] }
        route[last] = [last]
        prev_pid = pid_encode(min_line, last)
        while pid_decode(prev_pid)[1] != first
          prev_pid = previous[prev_pid]
          route[last] << pid_decode(prev_pid)[1]
        end

        route[last].reverse!
      end

      [result_distance, route]
    end

    def spfa_all(subway_stations, edges)
      distance = Hash.new
      route = Hash.new
      (0...subway_stations.size).each do |first|
        next if subway_stations[first].nil?

        distance[first], route[first] = spfa(first, subway_stations, edges)
      end

      [distance, route]
    end
  end
end
