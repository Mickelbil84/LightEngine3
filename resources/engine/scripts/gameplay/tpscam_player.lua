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
    self.playerMesh = LE3Scene.get_object(self.scene, "SK_soldier_1")
    self.playerMeshPhysics = LE3Object.get_physics_component(self.playerMesh)
    LE3SkeletalModel.set_animation_playing(self.playerMesh, true)

    self.offset = LE3Object.load(self.scene, {
        Name = cameraName .. "__offset",
        Position = {0, 150, 0},
        Rotation = {0, 0, 0},
        Scale = {1, 1, 1}
    })
    LE3Scene.reparent(self.scene, self.offset.name, "SK_soldier_1")
    LE3Scene.reparent(self.scene, cameraName, self.offset.name)

    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}
    self.walkSpeed = 2.2
    self.sensitivity = 0.005

    LE3EngineState.notify_wants_relative_mouse(true)


    -- Animation state
    self.animType = 0 -- 0 idle 1 walk
end

function TPSCamPlayer:update(deltaTime)
    self:handleInput()

    LE3Camera.add_pitch_yaw(self.camera.ptr, self.cameraRotation[2] * self.sensitivity, -self.cameraRotation[1] * self.sensitivity)
    local forward = table.pack(LE3Camera.get_forward(self.camera.ptr))
    local right = table.pack(LE3Camera.get_right(self.camera.ptr))
    _, vy, _ = LE3PhysicsComponent.get_linear_velocity(self.playerMeshPhysics)
    local v = {
        self.walkSpeed * (self.cameraVelocity[2] * forward[1] + self.cameraVelocity[1] * right[1]),
        vy,
        self.walkSpeed * (self.cameraVelocity[2] * forward[3] + self.cameraVelocity[1] * right[3])
    }
    LE3PhysicsComponent.set_linear_velocity(self.playerMeshPhysics, table.unpack(v))
    LE3PhysicsComponent.set_angular_factor(self.playerMeshPhysics, 0, 0, 0) -- Disable rotation
    LE3PhysicsComponent.set_angular_velocity(self.playerMeshPhysics, 0, 0, 0)
    if self:isMoving(v) then
        LE3PhysicsComponent.set_rotation(self.playerMeshPhysics, LE3Camera.get_xz_rotation(self.camera.ptr))
    end

    self:decideAnimation(v)
end

function TPSCamPlayer:isMoving(v)
    if math.abs(v[1]) > 0 or math.abs(v[3]) > 0 then return true end
    return false
end

function TPSCamPlayer:decideAnimation(v)
    local isMoving = self:isMoving(v)

    if isMoving and self.animType == 0 then
        LE3SkeletalModel.set_current_animation(self.playerMesh, "ANIM_soldier_rifle_walk")
        self.animType = 1
    end
    if not isMoving and self.animType == 1 then
        LE3SkeletalModel.set_current_animation(self.playerMesh, "ANIM_soldier_rifle_idle")
        self.animType = 0
    end
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