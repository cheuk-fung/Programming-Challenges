load "helper.rb"

code = Hash.new(0)

parser = Marshal.load(File.read(ARGV[0]))
parser.requests.each { |request| code[request.code] += request.quantity.abs if request.reqtype == :new_order }

puts code.sort_by { |key, value| value }.reverse.first(10).map { |key, value| key }.join(",")
