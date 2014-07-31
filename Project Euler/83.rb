mat = []
File.open('matrix.txt', 'r').each_line { |line| mat << line.split(',').map(&:to_i) }

N = mat.length
DIR = [[0, -1], [1, 0], [0, 1], [-1, 0]]

distance = Array.new(N) { Array.new(N, Float::INFINITY) }
queue = []
in_queue = Array.new(N) { Array.new(N, false) }

distance[0][0] = mat[0][0]
queue << [0, 0]
in_queue[0][0] = true

queue.each do |x, y|
  in_queue[x][y] = false
  DIR.each do |dx, dy|
    nx, ny = x + dx, y + dy
    next if nx < 0 || ny < 0 || nx >= N || ny >= N
    if mat[nx][ny] + distance[x][y] < distance[nx][ny]
      distance[nx][ny] = mat[nx][ny] + distance[x][y]
      if !in_queue[nx][ny]
        queue << [nx, ny]
        in_queue[nx][ny] = true
      end
    end
  end
end

puts distance[N - 1][N - 1]
