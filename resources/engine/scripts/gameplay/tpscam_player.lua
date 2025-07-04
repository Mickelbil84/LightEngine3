-- Template code for a third-person camera player
TPSCamPlayer = LE3ScriptObject:new()
function TPSCamPlayer:init()
    local cameraName = self.name .. "__tpscamera"
    self.camera = LE3OrbitCamera.load(self.scene, {
        FOV = 50 * 3.14159265 / 180,
        Name = cameraName,
        Offset = 1.5,
        -- Origin = {10, 0, 0}
    })
    self.playerMesh = LE3Scene.get_object(self.scene, "SK_ybot_1")
    self.playerMeshPhysics = LE3Object.get_physics_component(self.playerMesh)
    LE3SkeletalModel.set_animation_playing(self.playerMesh, true)
    LE3SkeletalModel.set_current_animation(self.playerMesh, "ANIM_ybot_idle", 0)

    self.offset = LE3Object.load(self.scene, {
        Name = cameraName .. "__offset",
        Position = {0, 150, 0},
        Rotation = {0, 0, 0},
        Scale = {1, 1, 1}
    })
    LE3Scene.reparent(self.scene, self.offset.name, "SK_ybot_1")
    LE3Scene.reparent(self.scene, cameraName, self.offset.name)

    self.cameraVelocity = {0, 0, 0}
    self.cameraRotation = {0, 0}
    self.walkSpeed = 2.2
    self.runSpeed = 4.0
    self.isRunning = false
    self.sensitivity = 0.005
    
    self.inAir = false

    LE3EngineState.notify_wants_relative_mouse(true)

    -- Animation state
    self.animType = 0 -- 0 idle 1 walk 2 jump 3 fall
    self.animBlendTime = 0.1
    self.currentAnimation = "ANIM_ybot_idle"
end

function TPSCamPlayer:update(deltaTime)
    self:handleInput()

    LE3Camera.add_pitch_yaw(self.camera.ptr, self.cameraRotation[2] * self.sensitivity, -self.cameraRotation[1] * self.sensitivity)
    local forward = table.pack(LE3Camera.get_forward(self.camera.ptr))
    local right = table.pack(LE3Camera.get_right(self.camera.ptr))
    _, vy, _ = LE3PhysicsComponent.get_linear_velocity(self.playerMeshPhysics)
    local speed = self.walkSpeed
    if self.isRunning then speed = self.runSpeed end
    local v = {
        speed * (self.cameraVelocity[2] * forward[1] + self.cameraVelocity[1] * right[1]),
        vy,
        speed * (self.cameraVelocity[2] * forward[3] + self.cameraVelocity[1] * right[3])
    }
    LE3PhysicsComponent.set_linear_velocity(self.playerMeshPhysics, table.unpack(v))
    LE3PhysicsComponent.set_angular_factor(self.playerMeshPhysics, 0, 0, 0) -- Disable rotation
    LE3PhysicsComponent.set_angular_velocity(self.playerMeshPhysics, 0, 0, 0)
    if self:isMoving(v) then
        LE3PhysicsComponent.set_rotation(self.playerMeshPhysics, LE3Camera.get_xz_rotation(self.camera.ptr))
    end

    self.inAir = self:isInAir()

    self:decideAnimation(v)
end

function TPSCamPlayer:isMoving(v)
    if math.abs(v[1]) > 0 or math.abs(v[3]) > 0 then return true end
    return false
end

function TPSCamPlayer:isInAir()
    local probe = {0, -0.9 - 0.2, 0}
    return not LE3PhysicsComponent.probe_collision(self.playerMeshPhysics, table.unpack(probe))
end

function TPSCamPlayer:decideAnimation(v)
    local isMoving = self:isMoving(v)
    
    local isFalling = self.inAir
    
    if isFalling and self.animType ~= 3 then
        LE3SkeletalModel.set_current_animation(self.playerMesh, "ANIM_ybot_fall", self.animBlendTime * 2)
        self.animType = 3
        self.currentAnimation = "ANIM_ybot_fall"
        return
    end
    if isFalling and self.animType == 3 then return end

    local blendTime = self.animBlendTime
    if self.animType == 3 then blendTime = 0.1 end
    if isMoving and (
        self.animType ~= 1 or
        (self.isRunning and self.currentAnimation ~= "ANIM_ybot_run") or
        (not self.isRunning and self.currentAnimation ~= "ANIM_ybot_walk"))  then
        local anim = "ANIM_ybot_walk"
        if self.isRunning then anim = "ANIM_ybot_run" end
        LE3SkeletalModel.set_current_animation(self.playerMesh, anim, blendTime)
        self.animType = 1
        self.currentAnimation = anim
        return
    end
    if not isMoving and self.animType ~= 0 then
        LE3SkeletalModel.set_current_animation(self.playerMesh, "ANIM_ybot_idle", blendTime)
        self.animType = 0
        return
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

    if LE3Input.is_key_down_event("KEY_SPACE") then
        LE3PhysicsComponent.apply_impulse(self.playerMeshPhysics, 0, 70, 0)
    end

    -- Adjsut camera speed
    if LE3Input.get_key("KEY_P") then
        self.walkSpeed = self.walkSpeed * 1.1
    end
    if LE3Input.get_key("KEY_O") then
        self.walkSpeed = self.walkSpeed / 1.1
    end

    self.isRunning = LE3Input.get_key("KEY_LSHIFT") or LE3Input.get_key("KEY_RSHIFT")

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