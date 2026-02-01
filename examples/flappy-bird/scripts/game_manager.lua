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

    self.bird = LE3Scene.get_object(self.scene, "bird")
    self.isSpaceDown = false
end

function FlappyBirdGame:update(deltaTime)
    self:handleInput()
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
end