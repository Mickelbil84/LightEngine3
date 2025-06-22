-- Template code for a third-person camera player
TPSCamPlayer = LE3ScriptObject:new()
function TPSCamPlayer:init()
    local cameraName = self.name .. "__tpscamera"
    self.camera = LE3OrbitCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName,
        Offset = 3,
        -- Origin = {10, 0, 0}
    })
    self.offset = LE3Object.load(self.scene, {
        Name = cameraName .. "__offset",
        Position = {0, 150, 0},
        Rotation = {0, 0, 180},
        Scale = {1, 1, 1}
    })
    LE3Scene.reparent(self.scene, self.offset.name, "SK_mannequin_1")
    LE3Scene.reparent(self.scene, cameraName, self.offset.name)

    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}
    self.walkSpeed = 2.2
    self.sensitivity = 0.005

    LE3EngineState.notify_wants_relative_mouse(true)
end

function TPSCamPlayer:update(deltaTime)
    self:handleInput()

    LE3Camera.add_pitch_yaw(self.camera.ptr, self.cameraRotation[2] * self.sensitivity, -self.cameraRotation[1] * self.sensitivity)
    -- LE3Camera.move_forward(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[2])
    -- LE3Camera.move_right(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[1])
    -- LE3Camera.move_up(self.camera.ptr, deltaTime * self.walkSpeed * self.cameraVelocity[3])
end

function TPSCamPlayer:handleInput()
    -- Use escape to quit the game
    if LE3Input.get_key("KEY_ESCAPE") then
        LE3EngineState.notify_wants_quit()
    end

    -- Toggle relative mouse mode (in the free camera player, useful especially for editor)
    if LE3Input.is_key_down_event("KEY_F") then
        local isRelative = LE3EngineState.is_relative_mouse()
        LE3EngineState.notify_wants_relative_mouse(not isRelative)
    end

    -- Adjsut camera speed
    if LE3Input.get_key("KEY_P") then
        self.walkSpeed = self.walkSpeed * 1.1
    end
    if LE3Input.get_key("KEY_O") then
        self.walkSpeed = self.walkSpeed / 1.1
    end

    -- Camera movement
    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}

    if not LE3EngineState.is_relative_mouse() then return end

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

function TPSCamPlayer:draw()
end