FlappyBird = LE3ScriptObject:new()

function FlappyBird:init()
    LE3EventManager.subscribe("EVT_JUMP", self.name, function(data)
        self:jump()
    end)
    LE3EventManager.subscribe("EVT_ON_COLLISION__SM_bird", self.name, function(data)
        self:onCollision(data)
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

function FlappyBird:onCollision(data)
    -- print("Collision: " .. data.objectA .. " <-> " .. data.objectB)
end
