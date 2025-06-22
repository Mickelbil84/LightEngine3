FreeCamPlayer = LE3ScriptObject:new()
function FreeCamPlayer:init()
    local cameraName = self.name .. "__freecamera"
    print(cameraName)
    self.camera = LE3FreeCamera.load(self.scene, {
        FOV = 45 * 3.14159265 / 180,
        Name = cameraName,
    })
    LE3Scene.reparent(self.scene, cameraName, self.name)
end

function FreeCamPlayer:update(deltaTime)
end

function FreeCamPlayer:draw()
end