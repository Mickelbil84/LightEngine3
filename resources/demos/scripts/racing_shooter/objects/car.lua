print("Hello world!")

Car = LE3ScriptObject:new()
function Car:init() 
    print("Initializing car...")
    print(self.object)
    LE3Transform.set_scale(self.transform, 2.5, 2.5, 2.5)
    print(LE3Transform.get_scale(self.transform))

    self.total_time = 0
end

function Car:update(deltaTime)
    self.total_time = self.total_time + deltaTime
    print("Car (#id = " .. self._ref .. "); total time: " .. self.total_time .. "[sec]")
end