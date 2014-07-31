coins = [1, 2, 5, 10, 20, 50, 100, 200]
f = [1] + [0] * 200
coins.each { |coin| (coin..200).each { |i| f[i] += f[i - coin] } }
puts f[200]
