-- Simple Flappy Bird clone using LE3 Lua bindings

math.randomseed(os.time())

local scene = _scene

-- Game state
local player
local velocity = 0.0
local pipes = {}
local spawn_timer = 0.0
local game_over = false
local restart_timer = 0.0

local function aabb(ax, ay, aw, ah, bx, by, bw, bh)
    return math.abs(ax - bx) < (aw + bw) and math.abs(ay - by) < (ah + bh)
end

local function clear_objects()
    if player then
        LE3Scene.delete_object(scene, "bird")
        player = nil
    end
    for _, pair in ipairs(pipes) do
        LE3Scene.delete_object(scene, LE3Object.get_name(pair.top))
        LE3Scene.delete_object(scene, LE3Object.get_name(pair.bottom))
    end
    pipes = {}
end

local function reset_game()
    clear_objects()
    velocity = 0.0
    spawn_timer = 0.0
    LE3Scene.add_box(scene, "bird", "M_Flappy", -1.0, 0.0, 0.0, 0.5, 0.5, 0.5)
    player = LE3Scene.get_object(scene, "bird")
    game_over = false
end

function init_flappy()
    -- Camera
    LE3Scene.add_free_camera(scene, "camera")
    LE3Scene.set_main_camera(scene, "camera")
    local cam = LE3Scene.get_object(scene, "camera")
    LE3Transform.set_position(LE3Object.get_transform(cam), 0.0, 0.0, 5.0)
    LE3Scene.set_background_color(scene, 0.5, 0.8, 1.0)

    -- Lighting
    LE3Scene.add_ambient_light(scene, "ambient")
    local amb = LE3Scene.get_object(scene, "ambient")
    LE3Light.set_intensity(amb, 0.4)
    LE3Light.set_color(amb, 1.0, 1.0, 1.0)

    LE3Scene.add_directional_light(scene, "sun")
    local sun = LE3Scene.get_object(scene, "sun")
    LE3Light.set_intensity(sun, 0.8)
    LE3Light.set_color(sun, 1.0, 1.0, 1.0)
    LE3Transform.set_rotation(
        LE3Object.get_transform(sun),
        math.cos(-0.25), 0.0, 0.0, math.sin(-0.25))

    reset_game()
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
    if game_over then
        restart_timer = restart_timer - dt
        if restart_timer <= 0.0 then
            reset_game()
        end
        return
    end

    -- Jump
    if LE3Input.is_key_down_event(LE3Input.KEY_SPACE) then
        velocity = 5.0
    end

    -- Apply gravity and update player position
    velocity = velocity - 9.8 * dt
    local t = LE3Object.get_transform(player)
    local px, py, pz = LE3Transform.get_position(t)
    py = py + velocity * dt
    LE3Transform.set_position(t, px, py, pz)

    -- Spawn pipes periodically
    spawn_timer = spawn_timer + dt
    if spawn_timer > 2.0 then
        spawn_timer = 0.0
        spawn_pipe((math.random() - 0.5) * 3.0)
    end

    -- Move pipes and check collisions
    local psx, psy, _ = LE3Transform.get_scale(t)
    local hit = false
    for i = #pipes, 1, -1 do
        local pair = pipes[i]
        for _, obj in pairs(pair) do
            local tr = LE3Object.get_transform(obj)
            local x, y, z = LE3Transform.get_position(tr)
            x = x - 2.0 * dt
            LE3Transform.set_position(tr, x, y, z)
            local sx, sy, _ = LE3Transform.get_scale(tr)
            if aabb(px, py, psx, psy, x, y, sx, sy) then
                hit = true
            end
        end
        local top_tr = LE3Object.get_transform(pair.top)
        local x, _, _ = LE3Transform.get_position(top_tr)
        if x < -10.0 then
            LE3Scene.delete_object(scene, LE3Object.get_name(pair.top))
            LE3Scene.delete_object(scene, LE3Object.get_name(pair.bottom))
            table.remove(pipes, i)
        end
    end

    -- Scene bounds collision
    if py > 3.0 or py < -3.0 then
        hit = true
    end

    if hit then
        clear_objects()
        game_over = true
        restart_timer = 2.0
    end
end
