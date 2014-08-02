load "helper.rb"

parser = LogParser.new(ARGV[0])
File.open(ARGV[1], "w") { |file| file.write(Marshal.dump(parser)) }
