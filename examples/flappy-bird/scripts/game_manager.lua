FlappyBirdGame = LE3ScriptObject:new()

function FlappyBirdGame:init()
    local cameraName = "camera"
    self.camera = LE3FreeCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName
    })
    LE3Scene.reparent(self.scene, cameraName, self.name)

    self.isSpaceDown = false
end

function FlappyBirdGame:update(deltaTime)
    self:handleInput()
end

function FlappyBirdGame:handleInput()
    if LE3Input.get_key("KEY_ESCAPE") then
        LE3EngineState.notify_wants_quit()
    end

    if LE3Input.get_key("KEY_SPACE") then
        if not self.isSpaceDown then
            LE3EventManager.notify("EVT_JUMP")
        end
        self.isSpaceDown = true
    else
        self.isSpaceDown = false
    end
end

function FlappyBirdGame:draw()
end