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
    }
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

Scene.Objects = {
    {
        Type = "Empty",
        Name = "player",
        Position = {0.0, 0.0, 0.0}
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
        Type = "Cube",
        Name = "cube",
        MaterialName = "M_default",
        Position = {0.0, -0.1, 0.0},
        Scale = {50.0, 0.1, 50.0}
    },
    {
        Type = "Empty",
        Name = "car",
        Scale = {2.5, 2.5, 2.5}
    },
    {
        Type = "StaticModel",
        MeshName = "SM_carBody",
        MaterialName = "M_carBody",
        
    }
}

Scene.ObjectRelations = {
    {"cameraFree", "player"},
    {"cameraOrbit", "car"},
    {"carBody", "car"},
    {"wheelsFront", "car"},
    {"wheelsBack", "car"},
    {"wheel1", "wheelsFront"},
    {"wheel2", "wheelsFront"},
    {"wheel3", "wheelsBack"},
    {"wheel4", "wheelsBack"},
}