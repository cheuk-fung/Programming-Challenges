#!/usr/bin/env ruby
#
def check(k, r, t)
  k + 2 * (k * r + (k - 1) * k) <= t;
end

tasks = gets.to_i
tasks.times do |task|
  radius, t = gets.split(" ").map(&:to_i)

  l = 0;
  r = 0x3f3f3f3f;
  while (l < r)
    mid = (l + r + 1) >> 1;
    if check(mid, radius, t)
      l = mid;
    else
      r = mid - 1;
    end
  end

  puts "Case ##{task + 1}: #{l}"
end
