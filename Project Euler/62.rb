cube = (1..10000).map { |x| x**3 }
cube_rep = ->(x) { x.to_s.chars.sort.reverse.join.to_i }
rep_min = Hash.new(Float::INFINITY)
count = Hash.new(0)
puts rep_min[cube_rep[cube.detect { |x| (count[rep_min[cube_rep[x]] = [rep_min[cube_rep[x]], x].min] += 1) == 5 }]]
