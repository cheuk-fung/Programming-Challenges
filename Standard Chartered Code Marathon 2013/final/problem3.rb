load "helper.rb"

total_count = Hash.new(0)
total_price = Hash.new(0)

parser = Marshal.load(File.read(ARGV[0]))
parser.orders.each do |order|
  if order.executed_time
    request = order.created_request
    user = request.user
    total_count[user] += 1
    total_price[user] += (request.price * request.quantity).abs
  end
end

File.open("problem3.tmp", "w") do |file|
  total_count.each { |user, count| file.puts user + " " + count.to_s + " " + total_price[user].to_s }
end

`Rscript problem3.R`

result = Hash.new { |h, k| h[k] = [] }
File.open("problem3.tmp.out") do |file|
  file.gets
  while str = file.gets
    id, center = str.strip.split(" ")
    result[center] << id[1..-2]
  end
end

result.each do |center, ids|
  file_name = "Q3_" + center + ".csv"
  File.open(file_name, "w") { |file| file.puts ids.sort.join("\n") }
end
