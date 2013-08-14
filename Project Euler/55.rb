class Integer
  def palindrome?
    self == reverse
  end

  def reverse
    to_s.reverse.to_i
  end
end

puts (1...10000).count { |x| !(1...50).any? { |_| (x += x.reverse).palindrome? } }
