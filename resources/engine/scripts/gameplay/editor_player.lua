-- Editor camera player: like FreeCamPlayer, but the camera only looks/moves while the right mouse button is held
EditorPlayer = LE3ScriptObject:new()
function EditorPlayer:init()
    local cameraName = self.name .. "__editorcamera"
    self.camera = LE3FreeCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName,
    })
    LE3Scene.reparent(self.scene, cameraName, self.name)

    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}
    self.walkSpeed = 2.2
    self.sensitivity = 0.005

    -- The cursor stays free until the right mouse button is held
    LE3EngineState.notify_wants_relative_mouse(false)
end

function EditorPlayer:update(deltaTime)
    self:handleInput()

    LE3Camera.add_pitch_yaw(self.camera.ptr, self.cameraRotation[2] * self.sensitivity, -self.cameraRotation[1] * self.sensitivity)
    LE3Camera.move_forward(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[2])
    LE3Camera.move_right(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[1])
    LE3Camera.move_up(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[3])
end

function EditorPlayer:handleInput()
    -- Use escape to quit the game
    if LE3Input.get_key("KEY_ESCAPE") then
        LE3EngineState.notify_wants_quit()
    end

    -- Adjust camera speed
    if LE3Input.get_key("KEY_P") then
        self.walkSpeed = self.walkSpeed * 1.1
    end
    if LE3Input.get_key("KEY_O") then
        self.walkSpeed = self.walkSpeed / 1.1
    end

    -- Camera movement: only while holding right click (the mouse is captured while looking)
    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}

    local isLooking = LE3Input.is_right_mouse_down()
    LE3EngineState.notify_wants_relative_mouse(isLooking)
    if not isLooking then return end

    if LE3Input.get_key("KEY_W") then self.cameraVelocity[2] = 1.0
    elseif LE3Input.get_key("KEY_S") then self.cameraVelocity[2] = -1.0
    else self.cameraVelocity[2] = 0.0
    end

    if LE3Input.get_key("KEY_D") then self.cameraVelocity[1] = 1.0
    elseif LE3Input.get_key("KEY_A") then self.cameraVelocity[1] = -1.0
    else self.cameraVelocity[1] = 0.0
    end

    if LE3Input.get_key("KEY_E") then self.cameraVelocity[3] = 1.0
    elseif LE3Input.get_key("KEY_Q") then self.cameraVelocity[3] = -1.0
    else self.cameraVelocity[3] = 0.0
    end

    self.cameraRotation[1] = LE3Input.get_xrel()
    self.cameraRotation[2] = -LE3Input.get_yrel()
end

function EditorPlayer:draw()
end
