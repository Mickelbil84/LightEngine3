-- Simple Flappy Bird clone using LE3 Lua bindings and Bullet physics

math.randomseed(os.time())

local scene = _scene

-- Game state
local player
local player_rb
local pipes = {}
local next_pipe_x = 5.0
local game_over = false
local restart_timer = 0.0

local function spawn_pipe(x)
    local gap = 2.5
    local offset = (math.random() - 0.5) * 3.0
    local idx = #pipes + 1

    local top_name = "pipe_top_" .. idx
    LE3Scene.add_box(scene, top_name, "M_FlappyPipe", x, offset + gap, 0.0, 1.0, 3.0, 1.0)
    local top_obj = LE3Scene.get_object(scene, top_name)
    local top_rb = LE3Object.get_physics_component(top_obj)
    LE3PhysicsComponent.set_mass(top_rb, 0.0)

    local bottom_name = "pipe_bottom_" .. idx
    LE3Scene.add_box(scene, bottom_name, "M_FlappyPipe", x, offset - gap, 0.0, 1.0, 3.0, 1.0)
    local bottom_obj = LE3Scene.get_object(scene, bottom_name)
    local bottom_rb = LE3Object.get_physics_component(bottom_obj)
    LE3PhysicsComponent.set_mass(bottom_rb, 0.0)

    table.insert(pipes, {top = top_obj, bottom = bottom_obj})
end

local function hide_all(hidden)
    if player then LE3DrawableObject.set_hidden(player, hidden) end
    for _, pair in ipairs(pipes) do
        LE3DrawableObject.set_hidden(pair.top, hidden)
        LE3DrawableObject.set_hidden(pair.bottom, hidden)
    end
end

local function reset_game()
    if player then LE3Scene.delete_object(scene, "bird") end
    LE3Scene.add_box(scene, "bird", "M_Flappy", -1.0, 0.0, 0.0, 0.5, 0.5, 0.5)
    player = LE3Scene.get_object(scene, "bird")
    player_rb = LE3Object.get_physics_component(player)
    LE3PhysicsComponent.set_mass(player_rb, 1.0)
    LE3PhysicsComponent.set_linear_velocity(player_rb, 1.5, 0.0, 0.0)

    next_pipe_x = 5.0
    pipes = {}
    game_over = false
    restart_timer = 0.0
end

function init_flappy()
    -- Camera
    LE3Scene.add_free_camera(scene, "camera")
    LE3Scene.set_main_camera(scene, "camera")
    local cam = LE3Scene.get_object(scene, "camera")
    LE3Transform.set_position(LE3Object.get_transform(cam), 0.0, 0.0, 7.0)
    LE3Scene.set_background_color(scene, 0.5, 0.8, 1.0)

    -- Lighting
    LE3Scene.add_ambient_light(scene, "ambient")
    local amb = LE3Scene.get_object(scene, "ambient")
    LE3Light.set_intensity(amb, 0.1)
    LE3Light.set_color(amb, 1.0, 1.0, 1.0)

    LE3Scene.add_directional_light(scene, "sun")
    local sun = LE3Scene.get_object(scene, "sun")
    LE3Light.set_intensity(sun, 0.8)
    LE3Light.set_color(sun, 1.0, 1.0, 1.0)
    LE3Transform.set_rotation(
        LE3Object.get_transform(sun),
        math.cos(-0.25), 0.0, 0.0, math.sin(-0.25))

    -- Scene bounds
    LE3Scene.add_box(scene, "bound_top", "M_FlappyPipe", 0.0, 4.0, 0.0, 50.0, 1.0, 1.0)
    local bt = LE3Scene.get_object(scene, "bound_top")
    LE3PhysicsComponent.set_mass(LE3Object.get_physics_component(bt), 0.0)
    LE3DrawableObject.set_hidden(bt, true)
    LE3Scene.add_box(scene, "bound_bottom", "M_FlappyPipe", 0.0, -4.0, 0.0, 50.0, 1.0, 1.0)
    local bb = LE3Scene.get_object(scene, "bound_bottom")
    LE3PhysicsComponent.set_mass(LE3Object.get_physics_component(bb), 0.0)
    LE3DrawableObject.set_hidden(bb, true)

    reset_game()
end

local function check_collision()
    if not player_rb then return false end
    local probes = {
        {0, 0, 0}, {0.3, 0, 0}, {-0.3, 0, 0},
        {0, 0.3, 0}, {0, -0.3, 0}
    }
    for _, p in ipairs(probes) do
        if LE3PhysicsComponent.probe_collision(player_rb, p[1], p[2], p[3]) then
            return true
        end
    end
    return false
end

function update_flappy(dt)
    if game_over then
        restart_timer = restart_timer - dt
        if restart_timer <= 0.0 then
            hide_all(false)
            reset_game()
        end
        return
    end

    if LE3Input.is_key_down_event(LE3Input.KEY_SPACE) then
        LE3PhysicsComponent.apply_impulse(player_rb, 0.0, 5.0, 0.0)
    end

    -- Keep forward speed
    local vx, vy, vz = LE3PhysicsComponent.get_linear_velocity(player_rb)
    LE3PhysicsComponent.set_linear_velocity(player_rb, 1.5, vy, 0.0)

    -- Camera follows player
    local px, py, pz = LE3Transform.get_position(LE3Object.get_transform(player))
    local cam = LE3Scene.get_object(scene, "camera")
    LE3Transform.set_position(LE3Object.get_transform(cam), px, 0.0, 7.0)

    -- Spawn pipes ahead
    if px + 10.0 > next_pipe_x then
        spawn_pipe(next_pipe_x)
        next_pipe_x = next_pipe_x + 5.0
    end

    if check_collision() then
        game_over = true
        restart_timer = 2.0
        hide_all(true)
    end
end
