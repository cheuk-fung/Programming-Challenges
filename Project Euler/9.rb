puts (1..1000).reduce(nil) { |prod, a| prod || (1..(1000 - a - 1)).reduce(prod) { |prod, b| prod || (a ** 2 + b ** 2 == (1000 - a - b) ** 2 ? a * b * (1000 - a - b) : nil) } }
