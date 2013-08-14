cipher_msg = File.open('cipher1.txt', 'r').read.split(',').map(&:to_i)
[*'aaa'..'zzz'].each do |key|
  key = key.chars.map(&:ord)
  test_msg = cipher_msg.each_slice(3).map { |text| text.map.with_index { |c, i| (c ^ key[i]).chr }.join }.join
  if test_msg[/ (T|t)he /] # only one match in this cipher message
    puts test_msg.chars.map(&:ord).reduce(:+)
    break
  end
end
