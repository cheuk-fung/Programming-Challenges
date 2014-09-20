n = gets.to_i

if n < 4
  puts "NO"
elsif n.even?
  puts "YES"
  puts "1 * 2 = 2"
  puts "2 * 3 = 6"
  puts "6 * 4 = 24"
  5.upto(n).each_slice(2) do |a, b|
    puts "#{b} - #{a} = 1"
    puts "24 * 1 = 24"
  end
else
  puts "YES"
  puts "2 - 1 = 1"
  puts "1 + 3 = 4"
  puts "4 * 5 = 20"
  puts "20 + 4 = 24"
  6.upto(n).each_slice(2) do |a, b|
    puts "#{b} - #{a} = 1"
    puts "24 * 1 = 24"
  end
end
