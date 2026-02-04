FlappyBird = LE3ScriptObject:new()

function FlappyBird:init()
    EventManager:subscribe("EVT_JUMP", self.name, function(data)
        self:jump()
    end)
    self.shouldInit = true
end

function FlappyBird:initAfterLoad()
    self.bird = LE3Scene.get_object_global("SM_bird")
    self.birdPhysics = LE3Object.get_physics_component(self.bird)
end

function FlappyBird:update(deltaTime)
    if self.shouldInit then 
        self:initAfterLoad()
        self.shouldInit = false
    end
end

function FlappyBird:draw()
end

function FlappyBird:jump()
    LE3PhysicsComponent.apply_impulse(self.birdPhysics, 0, 3, 0)
end
