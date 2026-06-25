FlappyPipes = LE3ScriptObject:new()

function FlappyPipes:init()
    self.shouldInit = true
    self.speed = 1.0
    self.numPipes = 5
    self.xMin = -5
    self.xMax = 5
    self.yMin = 0.2
    self.yMax = 1.2
    self.zPos = 1.5
    self.spacing = (self.xMax - self.xMin) / self.numPipes
end

function FlappyPipes:initAfterLoad()
    self.pipes = {}
    for i = 1, self.numPipes do
        local up = LE3Scene.get_object_global("SM_pipe" .. i .. "_up")
        local down = LE3Scene.get_object_global("SM_pipe" .. i .. "_down")

        -- Store the base Y of each pipe so we preserve the gap between up/down
        local tUp = LE3Object.get_transform(up)
        local tDown = LE3Object.get_transform(down)
        local _, yUpBase, _ = LE3Transform.get_position(tUp)
        local _, yDownBase, _ = LE3Transform.get_position(tDown)

        local physUp = LE3Object.get_physics_component(up)
        local physDown = LE3Object.get_physics_component(down)
        LE3PhysicsComponent.set_kinematic(physUp, true)
        LE3PhysicsComponent.set_kinematic(physDown, true)

        local x = self.xMax + (i - 1) * self.spacing
        local y = self.yMin + math.random() * (self.yMax - self.yMin)

        self.pipes[i] = {
            up = up, down = down,
            physUp = physUp, physDown = physDown,
            x = x, y = y,
            yUpBase = yUpBase, yDownBase = yDownBase
        }
        self:applyPipePosition(i)
    end
end

function FlappyPipes:applyPipePosition(i)
    local pipe = self.pipes[i]
    -- warp(physics_component, x, y, z, qw, qx, qy, qz)
    LE3PhysicsComponent.warp(pipe.physUp, pipe.x, pipe.yUpBase + pipe.y, self.zPos, 1, 0, 0, 0)
    LE3PhysicsComponent.warp(pipe.physDown, pipe.x, pipe.yDownBase + pipe.y, self.zPos, 1, 0, 0, 0)
end

function FlappyPipes:update(deltaTime)
    if self.shouldInit then
        self:initAfterLoad()
        self.shouldInit = false
    end

    for i = 1, self.numPipes do
        local pipe = self.pipes[i]
        pipe.x = pipe.x - self.speed * deltaTime
        if pipe.x < self.xMin then
            pipe.x = self.xMax
            pipe.y = self.yMin + math.random() * (self.yMax - self.yMin)
        end
        self:applyPipePosition(i)
    end
end

function FlappyPipes:draw()
end
