print("RUNNING SCRIPT! -- TESTING THAT BUILD ACTUALLY DOES SOMETHING")

FlappyBirdGame = LE3ScriptObject:new()
function FlappyBirdGame:init()
    print("Hello World! <<from FlappyBirdGame:init()>>")

    local cameraName = "camera"
    self.camera = LE3FreeCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName
    })
    LE3Scene.reparent(self.scene, cameraName, self.name)
end

function FlappyBirdGame:update(deltaTime)
    self:handleInput()
end

function FlappyBirdGame:handleInput()
    -- Use escape to quit the game
    if LE3Input.get_key("KEY_ESCAPE") then
        LE3EngineState.notify_wants_quit()
    end
end

function FlappyBirdGame:draw()
end