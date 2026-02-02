print("TODO: Refactor this game so that it would be a more coherent piece of software!!")

FlappyBirdGame = LE3ScriptObject:new()
function FlappyBirdGame:init()
    print("Hello World! <<from FlappyBirdGame:init()>>")

    local cameraName = "camera"
    self.camera = LE3FreeCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName
    })
    LE3Scene.reparent(self.scene, cameraName, self.name)

    self.wasInit = false
end

function FlappyBirdGame:onInitDone()
    self.bird = LE3Scene.get_object_global("bird")
    self.birdPhysics = LE3Object.get_physics_component(self.bird)
    print(LE3Object.get_name(self.bird))
    self.isSpaceDown = false
end

function FlappyBirdGame:update(deltaTime)
    if not self.wasInit then
        self:onInitDone()
        self.wasInit = true
    end

    self:handleInput()

    local transform = LE3Object.get_transform(self.bird)
    print(LE3Transform.get_position(transform))
end

function FlappyBirdGame:handleInput()
    -- Use escape to quit the game
    if LE3Input.get_key("KEY_ESCAPE") then
        LE3EngineState.notify_wants_quit()
    end

    if LE3Input.get_key("KEY_SPACE") then
        if not self.isSpaceDown then self:onSpace() end
        self.isSpaceDown = true
    else 
        self.isSpaceDown = false
    end

end

function FlappyBirdGame:draw()
end

function FlappyBirdGame:onSpace()
    print("onSpace")
    LE3PhysicsComponent.apply_impulse(self.birdPhysics, 0, 3, 0)
end