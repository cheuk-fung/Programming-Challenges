require "time"

class Request
  attr_accessor :rid
  attr_accessor :created_time, :responsed_time
  attr_accessor :reqtype, :user, :order, :type, :code, :quantity, :price
end

class Order
  attr_accessor :oid
  attr_accessor :created_time, :executed_time, :cancelled_time
  attr_accessor :created_request, :cancelled_request, :cancelled_status
end

class LogItem
  attr_accessor :operation, :time, :user, :io, :request, :order, :type, :code, :quantity, :price

  def initialize(line)
    r = /\[(\d+-\d+-\d+ \d+:\d+:\d+)\.(\d+)\]/.match(line)
    @time = Time.parse(r[1]).to_i
    @time = @time * 1000 + r[2].to_i

    r = /User \[(.*)\] logged (.*)/.match(line)
    if r
      @operation = :user_io
      @user = r[1]
      @io = r[2] == "in"
      return
    end

    r = /User \[(.*)\] view product\[type:(.*),code:(.*)\]/.match(line)
    if r
      @operation = :user_view
      @user = r[1]
      @type = r[2]
      @code = r[3]
      return
    end

    r = /New Order Request \[(.*)\] is sent by User \[(.*)\] to (.*) product\[type:(.*),code:(.*),quantity:(.*),price:(.*)\]/.match(line)
    if r
      @operation = :new_order_request
      @request = r[1]
      @user = r[2]
      @type = r[4]
      @code = r[5]
      @quantity = (r[3] == "buy" ? 1 : -1) * r[6].to_i
      @price = r[7].to_f
      return
    end

    r = /New Order \[(.*)\] is created by request \[(.*)\]/.match(line)
    if r
      @operation = :new_order
      @order = r[1]
      @request = r[2]
      return
    end

    r = /Order \[(.*)\] is executed/.match(line)
    if r
      @operation = :execute_order
      @order = r[1]
      return
    end

    r = /Cancel Order Request \[(.*)\] is sent by User \[(.*)\] to cancel Order \[(.*)\]/.match(line)
    if r
      @operation = :cancel_order_request
      @request = r[1]
      @user = r[2]
      @order = r[3]
      return
    end

    r = /Order \[(.*)\] is cancelled by request \[(.*)\]/.match(line)
    if r
      @operation = :cancel_success
      @order = r[1]
      @request = r[2]
      return
    end

    r = /Cancel Order Request \[(.*)\] is rejected/.match(line)
    if r
      @operation = :cancel_fail
      @request = r[1]
    end
  end
end

class LogParser
  attr_accessor :requests, :orders

  def initialize(path)
    @requests = {}
    @orders = {}

    File.open(path).each_line do |line|
      log = LogItem.new(line)

      case log.operation
      when :user_io
        next #TODO
      when :user_view
        next #TODO
      when :new_order_request
        # puts "3: R:" + log.request + " U:" + log.user
        request = Request.new
        request.created_time = log.time
        request.rid = log.request
        request.reqtype = :new_order
        request.user = log.user
        request.type = log.type
        request.code = log.code
        request.quantity = log.quantity
        request.price = log.price
        @requests[log.request] = request
      when :new_order
        # puts "4: O:" + log.order + " R:" + log.request
        order = Order.new
        order.created_time = log.time
        order.oid = log.order
        order.created_request = @requests[log.request]
        order.created_request.order = order
        order.created_request.responsed_time = log.time
        @orders[log.order] = order
      when :execute_order
        # puts "5: O:" + log.order
        @orders[log.order].executed_time = log.time
      when :cancel_order_request
        # puts "6: R:" + log.request
        request = Request.new
        request.created_time = log.time
        request.rid = log.request
        request.reqtype = :cancel_order
        request.user = log.user
        request.order = @orders[log.order]
        @requests[log.request] = request
        @orders[log.order].cancelled_request = request
      when :cancel_success
        # puts "7: O:" + log.order
        order = @orders[log.order]
        order.cancelled_time = log.time
        order.cancelled_status = true
        order.cancelled_request.responsed_time = log.time
      when :cancel_fail
        # puts "8: R:" + log.request
        order = @requests[log.request].order
        order.cancelled_time = log.time
        order.cancelled_status = false
        order.cancelled_request.responsed_time = log.time
      end
    end

    @requests = @requests.values
    @orders = @orders.values
  end
end
