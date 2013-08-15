class Array
  def >(other_ary)
    index = (size - 1).downto(0).detect { |i| self[i] != other_ary[i] }
    !!(index && self[index] > other_ary[index])
  end
end

class Poker
  VALUE = [*2..14]
  TYPE = [:straight_flush?,
          :four_of_a_kind?,
          :full_house?,
          :flush?,
          :straight?,
          :three_of_a_kind?,
          :two_pair?,
          :one_pair?,
          :high_card?
  ]

  attr_reader :hand

  def initialize(hand)
    @to_num = Hash.new do |h, k|
    end

    @hand = hand.map { |h| [value_to_num(h[0]), h[1]] }.sort_by { |h| h[0] }
  end

  def >(other_poker)
    rank != other_poker.rank ? (rank < other_poker.rank) : (send(TYPE[rank]) > other_poker.send(TYPE[rank]))
  end

  def rank
    TYPE.each_with_index { |m, i| return i if method(m).call }
  end

  private

  def value_to_num(v)
    case v
    when ('2'..'9') then v.to_i
    when 'T' then 10
    when 'J' then 11
    when 'Q' then 12
    when 'K' then 13
    when 'A' then 14
    end
  end

  def values
    hand.map { |h| h[0] }
  end

  def count_value(v)
    hand.count { |h| h[0] == v }
  end

  def high_card?
    values
  end

  def one_pair?
    pair = VALUE.detect { |v| count_value(v) == 2 }
    values.reject(&pair.method(:==)) << pair if pair
  end

  def two_pair?
    p1 = VALUE.detect { |v| count_value(v) == 2 }
    p2 = VALUE.detect { |v| v != p1 && count_value(v) == 2 }
    values.reject { |v| v == p1 || v == p2 } << p1 << p2 if p1 && p2
  end

  def three_of_a_kind?
    triple = VALUE.detect { |v| count_value(v) == 3 }
    values.reject(&triple.method(:==)) << triple if triple
  end

  def straight?
    values if (1...hand.size).all? { |i| hand[i][0] == hand[i - 1][0] + 1 }
  end

  def flush?
    values if hand.uniq { |h| h[1] }.size == 1
  end

  def full_house?
    triple = VALUE.detect { |v| count_value(v) == 3 }
    pair = VALUE.detect { |v| v != triple && count_value(v) == 2 }
    [pair, triple] if triple && pair
  end

  def four_of_a_kind?
    quad = VALUE.detect { |v| count_value(v) == 4 }
    values.reject(&quad.method(:==)) << quad if quad
  end

  def straight_flush?
    values if straight? && flush?
  end
end

puts File.open('poker.txt', 'r').readlines.map(&:split).reduce(0) { |sum, line| sum + (Poker.new(line[0...5]) > Poker.new(line[5..-1]) ? 1 : 0) }
