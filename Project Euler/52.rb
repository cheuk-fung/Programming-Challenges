require "set"
(2..Float::INFINITY).each do |l|
  (0..6).each do |second|
    (0...(10**(l - 2))).each do |tail|
      num = 10**(l - 1) + second * 10**(l - 2) + tail
      digits = num.to_s.chars.to_set
      if (2..6).map { |k| (k * num).to_s.length == l && (k * num).to_s.chars.to_set == digits }.all?
        puts num
        exit
      end
    end
  end
end
