Scene = {}
Scene.Shaders = {
    {
        Name = "S_default",
        VertexSource = "/engine/shaders/blinn_phong/blinn_phong.vs",
        FragmentSource = "/engine/shaders/blinn_phong/blinn_phong.fs"
    }
}
Scene.Textures = {
    {
        Name = "T_carBody_DIFF",
        Path = "/demos/textures/cars/T_CarBody_DIFF.png"
    },
    {
        Name = "T_carWheel_DIFF",
        Path = "/demos/textures/cars/CarWheel_DIFF.png"
    },
    {
        Name = "T_carWheel_REFL",
        Path = "/demos/textures/cars/CarWheel_REFL.png"
    },
    {
        Name = "T_basilica",
        Path = "/demos/textures/cubemaps/basilica.png"
    },
    {
        Name = "T_DIF_soldier",
        Path = "/demos/textures/animations/soldier/T_DIF_soldier.png"
    },
    {
        Name = "T_NRM_soldier",
        Path = "/demos/textures/animations/soldier/T_NRM_soldier.png"
    },
    {
        Name = "T_SPC_soldier",
        Path = "/demos/textures/animations/soldier/T_SPC_soldier.png"
    },
    {
        Name = "T_cylinder",
        Path = "/demos/textures/cylinder.png"
    },
}
Scene.Materials = {
    {
        Name = "M_default",
        ShaderName = "S_default",
        DiffuseColor = {0.8, 0.8, 0.8, 1.0},
        SpecularIntensity = 0.0
    },
    {
        Name = "M_wheel",
        ShaderName = "S_default",
        DiffuseTexture = "T_carWheel_DIFF",
        SpecularTexture = "T_carWheel_REFL",
        Shininess = 128,
        Cubemap = "T_basilica",
        ReflectionIntensity = 0.5
    },
    {
        Name = "M_carBody",
        ShaderName = "S_default",
        DiffuseTexture = "T_carBody_DIFF",
        Shininess = 128,
        Cubemap = "T_basilica",
        ReflectionIntensity = 0.2
    },
    {
        Name = "M_soldier",
        ShaderName = "S_default",
        DiffuseTexture = "T_DIF_soldier",
        NormalTexture = "T_NRM_soldier",
        SpecularTexture = "T_SPC_soldier",
        SpecularIntensity = 2.0,
        Shininess = 128,
    },
    {
        Name = "M_cylinder",
        ShaderName = "S_default",
        DiffuseTexture = "T_cylinder",
        SpecularIntensity = 2.0,
        Shininess = 32,
        Cubemap = "T_basilica",
        ReflectionIntensity = 0.02
    }
}
Scene.StaticMeshes = {
    {
        Name = "SM_carBody",
        Path = "/demos/models/cars/Car Body.fbx"
    },
    {
        Name = "SM_carWheel",
        Path = "/demos/models/cars/Car Wheel.fbx"
    }
}
Scene.SkeletalMeshes = {
    {
        Name = "SK_soldier",
        Path = "/demos/models/animations/soldier/SK_soldier.fbx",
        Animations = {
            {
                Name = "ANIM_fire",
                Path = "/demos/models/animations/soldier/ANIM_soldier_rifle_fire.fbx"
            },
            {
                Name = "ANIM_idle",
                Path = "/demos/models/animations/soldier/ANIM_soldier_rifle_idle.fbx"
            },
            {
                Name = "ANIM_walk",
                Path = "/demos/models/animations/soldier/ANIM_soldier_rifle_walk.fbx"
            }
        }
    }
}

Scene.Objects = {
    {
        Type = "AmbientLight",
        Name = "ambientLight",
        Intensity = 0.3,
        Color = {1, 0.9, 0.9}
    },
    {
        Type = "DirectionalLight",
        Name = "sunLight",
        Intensity = 0.5,
        Rotation = {-0.9961947, 0, -0.08715574, 0},
        HasShadowMap = true,
    },
    {
        Type = "PointLight",
        Name = "pointLight01",
        -- Position = {-2, 1.1, 0},
        Position = {-1, 1.1, 0},
        Color = {0, 0.9, 0.3},
        Intensity = 0.3,
    },
    {
        Type = "SpotLight",
        Name = "spotLight01",
        Position = {-2.3, 1.1, 0},
        Color = {0.9, 0.9, 0.9},
        -- Rotation = {-0.9961947, 0, 0.08715574, 0},
        -- Rotation = {0, 0, 0, 1},
        Intensity = 0.8,
        HasShadowMap = true,
    },
    {
        Type = "Empty",
        Name = "player",
        Position = {0.0, 0.0, 0.0}
    },
    {
        Type = "Box",
        Name = "floor",
        MaterialName = "M_default",
        BoxPosition = {0, -0.05, 0},
        BoxExtent = {50, 0.1, 50},
        CastShadow = false
    },
    {
        Type = "FreeCamera",
        Name = "cameraFree",
        Position = {0.0, 0.5, 3.0}
    },
    {
        Type = "OrbitCamera",
        Name = "cameraOrbit",
        Offset = 3.0
    },
    {
        Type = "OrbitCamera",
        Name = "inspector",
        Offset = 5.0
    },
    {
        Type = "ScriptObject",
        Classname = "Car",
        Name = "car",
        Scale = {2.5 * 0.75, 2.5 * 0.75, 2.75 * 0.5},
        Position = {0.3, 0.0, -1}
    },
    -- {
    --     Type = "ScriptObject",
    --     Classname = "Car",
    --     Name = "car2",
    --     Scale = {2.5 * 0.75, 2.5 * 0.75, 2.75 * 0.5},
    --     Position = {-2, 0.05, 2}
    -- },
    {
        Type = "SkeletalModel",
        Name = "soldier",
        MeshName = "SK_soldier",
        MaterialName = "M_soldier",
        Position = {0.8, 0, 0},
        Scale = {0.005, 0.005, 0.005}
    },
    {
        Type = "ScriptObject",
        Classname = "PointCloudDemo",
        Name = "_pcdemo",
    },
    {
        Type = "Cylinder",
        Name = "cyl1",
        MaterialName = "M_cylinder",
        Position = {1,1,1},
        Radius = 0.25,
        Height = 1.0,
        Resolution = 32,
        WithCaps = true
    },

    {
        Type = "Cone",
        Name = "con1",
        MaterialName = "M_cylinder",
        Position = {1.6,1,1},
        Radius = 0.25,
        Height = 1.0,
        Resolution = 32,
        WithCaps = true
    },
}

Scene.ObjectRelations = {
    {"cameraFree", "player"},
    {"cameraOrbit", "car"},
    {"pointLight01", "car"},
}

-- Scene settings
Scene.Settings = {
    BackgroundColor = {100/255, 149/255, 253/255}
}