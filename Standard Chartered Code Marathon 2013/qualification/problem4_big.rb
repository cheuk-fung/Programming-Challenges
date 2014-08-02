require "time"

fuxingmen_id = 12
log = []
File.open('subway.log').each_line do |line|
  r = /(?<time>.*): user entered station (?<sid>\d+)/.match(line)
  log << Time.parse(r[:time]).to_i if r && r[:sid].to_i == fuxingmen_id
end

window = []
max_count = 0
max_time = nil
log.sort.each do |now|
  window << now
  window.shift while now - window.first >= 60
  max_count, max_time = window.size, window.first if window.size > max_count
end

File.open('Result/output4.txt', 'w') do |file|
  file.puts max_count
  file.puts [max_time, max_time + 59].map { |now| Time.at(now).strftime("%H:%M:%S") }.join(' ')
end
