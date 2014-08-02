load "helper.rb"

MAX_GAP = 100

slow_request = []

parser = Marshal.load(File.read(ARGV[0]))
is_slow = lambda { |request| request.responsed_time - request.created_time >= 10 }
slow_request = parser.requests.select { |request| is_slow[request] }.sort_by { |request| request.created_time }

time_span = [[slow_request[0].created_time, slow_request[0].responsed_time]]
slow_request.each do |request|
  if request.created_time > time_span.last[1] + MAX_GAP
    time_span << [request.created_time, request.responsed_time]
  else
    time_span.last[1] = [time_span.last[1], request.responsed_time].max
  end
end

max_time_span = time_span.sort_by { |l, r| r - l }.last
puts [Time.at(max_time_span[0]).strftime("%H:%M:%S"), Time.at(max_time_span[1]).strftime("%H:%M:%S")].join(",")
