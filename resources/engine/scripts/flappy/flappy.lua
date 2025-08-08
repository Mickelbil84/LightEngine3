-- Simple Flappy Bird clone using LE3 Lua bindings

math.randomseed(os.time())

local scene = _scene

-- Load default shader and material
LE3Shader.load{
    Name = "S_Flappy",
    VertexSource = "/engine/shaders/blinn_phong/blinn_phong.vs",
    FragmentSource = "/engine/shaders/blinn_phong/blinn_phong.fs"
}
LE3Material.load{
    Name = "M_Flappy",
    ShaderName = "S_Flappy",
    DiffuseColor = {1.0, 1.0, 1.0, 1.0}
}

-- Game objects
local player
local velocity = 0.0
local pipes = {}
local spawn_timer = 0.0

function init_flappy()
    -- Camera
    LE3Scene.add_free_camera(scene, "camera")
    LE3Scene.set_main_camera(scene, "camera")
    local cam = LE3Scene.get_object(scene, "camera")
    LE3Transform.set_position(LE3Object.get_transform(cam), 0.0, 0.0, 5.0)
    LE3Scene.set_background_color(scene, 0.5, 0.8, 1.0)

    -- Player box
    LE3Scene.add_box(scene, "bird", "M_Flappy", -1.0, 0.0, 0.0, 0.5, 0.5, 0.5)
    player = LE3Scene.get_object(scene, "bird")
end

function spawn_pipe(offset)
    local gap = 1.5
    local idx = #pipes + 1
    local y = offset or 0.0

    local top_name = "pipe_top_" .. idx
    LE3Scene.add_box(scene, top_name, "M_Flappy", 5.0, y + gap, 0.0, 1.0, 5.0, 1.0)
    local top_obj = LE3Scene.get_object(scene, top_name)

    local bottom_name = "pipe_bottom_" .. idx
    LE3Scene.add_box(scene, bottom_name, "M_Flappy", 5.0, y - gap, 0.0, 1.0, 5.0, 1.0)
    local bottom_obj = LE3Scene.get_object(scene, bottom_name)

    table.insert(pipes, {top = top_obj, bottom = bottom_obj})
end

function update_flappy(dt)
    -- Jump
    if LE3Input.is_key_down_event(LE3Input.KEY_SPACE) then
        velocity = 5.0
    end

    -- Apply gravity and update player position
    velocity = velocity - 9.8 * dt
    local t = LE3Object.get_transform(player)
    local x, y, z = LE3Transform.get_position(t)
    y = y + velocity * dt
    LE3Transform.set_position(t, x, y, z)

    -- Spawn pipes periodically
    spawn_timer = spawn_timer + dt
    if spawn_timer > 2.0 then
        spawn_timer = 0.0
        spawn_pipe((math.random() - 0.5) * 3.0)
    end

    -- Move pipes
    for _, pair in ipairs(pipes) do
        for _, obj in pairs(pair) do
            local tr = LE3Object.get_transform(obj)
            local px, py, pz = LE3Transform.get_position(tr)
            px = px - 2.0 * dt
            LE3Transform.set_position(tr, px, py, pz)
        end
    end
end


