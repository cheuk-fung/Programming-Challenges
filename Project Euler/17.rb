num2word = {
  0 => '',
  1 => 'one',
  2 => 'two',
  3 => 'three',
  4 => 'four',
  5 => 'five',
  6 => 'six',
  7 => 'seven',
  8 => 'eight',
  9 => 'nine',
  10 => 'ten',
  11 => 'eleven',
  12 => 'twelve',
  13 => 'thirteen',
  14 => 'fourteen',
  15 => 'fifteen',
  16 => 'sixteen',
  17 => 'seventeen',
  18 => 'eighteen',
  19 => 'nineteen',
  20 => 'twenty',
  30 => 'thirty',
  40 => 'forty',
  50 => 'fifty',
  60 => 'sixty',
  70 => 'seventy',
  80 => 'eighty',
  90 => 'ninety'
}

translate = ->(x) { (x >= 1000 ? num2word[x / 1000] + "thousand" : '') \
            + (x % 1000 >= 100 ? num2word[x % 1000 / 100] + "hundred" + (x % 100 > 0 ? "and" : '') : '') \
            + (x % 100 >= 20 ? num2word[x % 100 / 10 * 10] + num2word[x % 10] : num2word[x % 100])
}

puts (1..1000).map(&translate).map(&:length).reduce(:+)
