EventSubscription = {}
function EventSubscription:new(event, subscriber, callback)
    o = {event = event, subscriber = subscriber, callback = callback}
    setmetatable(o, self)
    self.__index = self
    return o
end


EventManager = {}
EventManager.__index = EventManager

EventManager.subscriptions = {}

function EventManager:subscribe(event, subscriber, callback)
    if self.subscriptions[event] == nil then self.subscriptions[event] = {} end
    local eventSubs = self.subscriptions[event]
    eventSubs[#eventSubs+1] = EventSubscription:new(event, subscriber, callback)
end

function EventManager:notify(event, data)
    if self.subscriptions[event] == nil then return end
    for i, subscription in ipairs(self.subscriptions[event]) do
        -- TODO: make nil, defragment list
        if not LE3Scene.has_object_global(subscription.subscriber) then
            goto continue
        end
        ::continue::

        subscription.callback(data)
    end
end