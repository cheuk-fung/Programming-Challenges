triangle = (1..200).map { |n| n * (n + 1) / 2 }.select { |x| x.between?(1000, 9999) }
square = (1..100).map { |n| n**2 }.select { |x| x.between?(1000, 9999) }
pentagonal = (1..100).map { |n| n * (3 * n - 1) / 2 }.select { |x| x.between?(1000, 9999) }
hexagonal = (1..100).map { |n| n * (2 * n - 1) }.select { |x| x.between?(1000, 9999) }
heptagonal = (1..100).map { |n| n * (5 * n - 3) / 2 }.select { |x| x.between?(1000, 9999) }
octagonal = (1..100).map { |n| n * (3 * n - 2) }.select { |x| x.between?(1000, 9999) }

@numbers = [octagonal, heptagonal, hexagonal, pentagonal, square, triangle]

def dfs(selected_number, used_category, depth)
  if depth == 6
    if selected_number.last.to_s[-2..-1] == selected_number[0].to_s[0..1]
      puts selected_number.inspect
      puts selected_number.reduce(:+)
      exit
    end
    return
  end

  (0...6).select { |i| (used_category & (1 << i)) == 0 }.each { |i| @numbers[i].each { |x| dfs(selected_number + [x], used_category | (1 << i), depth + 1) if selected_number.empty? || selected_number.last.to_s[-2..-1] == x.to_s[0..1] } }
end

dfs([], 0, 0)
