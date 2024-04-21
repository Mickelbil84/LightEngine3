Car = LE3ScriptObject:new()
function Car:init()
    print("Initializing car...")

    self.car_body = LE3StaticModel.load(self.scene, {
        Type = "StaticModel",
        Name = self.name .. "_carBody",
        MeshName = "SM_carBody",
        MaterialName = "M_carBody",
        Rotation = {0.5, -0.5, -0.5, -0.5},
        Scale = {0.3, 0.3, 0.3},
        Position = {-2.06 * 0.3, 0, 0}
    })
    LE3Scene.reparent(self.scene, self.car_body.name, self.name)

    self.wheels_front = LE3Object.load(self.scene, {
        Type = "Empty",
        Name = self.name .. "_wheelsFront",
        Position = {.285 -2.06 * 0.3, 0.095, 0.}
    })
    LE3Scene.reparent(self.scene, self.wheels_front.name, self.name)

    self.wheels_back = LE3Object.load(self.scene, {
        Type = "Empty",
        Name = self.name .. "_wheelsBack",
        Position = {1.035 -2.06 * 0.3, 0.095, 0.}
    })
    LE3Scene.reparent(self.scene, self.wheels_back.name, self.name)

    local pos_odd = {0, 0, -0.3}
    local pos_even = {0, 0, 0.3}
    local rot_odd = {0.5, 0.5, 0.5, -0.5}
    local rot_even = {0.5, -0.5, -0.5, -0.5}

    self.wheels = {}
    for i=1,4 do
        local pos = pos_odd
        local rot = rot_odd
        if i % 2 == 0 then pos = pos_even; rot = rot_even; end
        local tmp = self.wheels_front
        if i >= 3 then tmp = self.wheels_back end

        self.wheels[i] = LE3StaticModel.load(self.scene, {
            Type = "StaticModel",
            Name = self.name .. "_wheel" .. i,
            MeshName = "SM_carWheel",
            MaterialName = "M_wheel",
            Position = pos,
            Scale = {0.33, 0.33, 0.33},
            Rotation = rot
        })
        LE3Scene.reparent(self.scene, self.wheels[i].name, tmp.name)
    end
end

function Car:update(deltaTime)
end

function Car:draw()
    local x, y, z = LE3Transform.get_position(self.transform)
    LE3VisualDebug.draw_debug_box(
        x, y + 0.35, z,
        1, 0, 0, 0,
        3, 0.8, 1.5,
        0, 1, 0
    )
end