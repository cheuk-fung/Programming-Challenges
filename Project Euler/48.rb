puts (1..1000).reduce { |sum, x| (sum + x**x) % (10**10) }
