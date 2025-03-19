Scene = {}
Scene.Shaders = {
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
        Name = "T_DIF_mannequin",
        Path = "/demos/textures/animations/mannequin/T_DIF_mannequin.png"
    },
    {
        Name = "T_NRM_mannequin",
        Path = "/demos/textures/animations/mannequin/T_NRM_mannequin.png"
    },
    {
        Name = "T_SPC_mannequin",
        Path = "/demos/textures/animations/mannequin/T_SPC_mannequin.png"
    },
    {
        Name = "T_cylinder",
        Path = "/demos/textures/cylinder.png"
    },
}
Scene.Materials = {
    {
        Name = "M_wheel",
        ShaderName = "__ENGINE__S_default",
        DiffuseTexture = "T_carWheel_DIFF",
        SpecularTexture = "T_carWheel_REFL",
        Shininess = 128,
        Cubemap = "T_basilica",
        ReflectionIntensity = 0.5
    },
    {
        Name = "M_carBody",
        ShaderName = "__ENGINE__S_default",
        DiffuseTexture = "T_carBody_DIFF",
        Shininess = 128,
        Cubemap = "T_basilica",
        ReflectionIntensity = 0.2
    },
    {
        Name = "M_soldier",
        ShaderName = "__ENGINE__S_default",
        DiffuseTexture = "T_DIF_soldier",
        NormalTexture = "T_NRM_soldier",
        SpecularTexture = "T_SPC_soldier",
        SpecularIntensity = 2.0,
        Shininess = 128,
    },
    {
        Name = "M_mannequin",
        ShaderName = "__ENGINE__S_default",
        DiffuseTexture = "T_DIF_mannequin",
        NormalTexture = "T_NRM_mannequin",
        SpecularTexture = "T_SPC_mannequin",
        SpecularIntensity = 0.5,
        Shininess = 32,
    },
    {
        Name = "M_cylinder",
        ShaderName = "__ENGINE__S_default",
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
    },
    {
        Name = "SK_mannequin",
        Path = "/demos/models/animations/mannequin/SK_mannequin.fbx",
        Animations = {
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
        HasShadowMap = true,
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
        Name = "inspector",
        Offset = 5.0
    }
}

Scene.ObjectRelations = {
}

-- Scene settings
Scene.Settings = {
    BackgroundColor = {100/255, 149/255, 253/255}
}