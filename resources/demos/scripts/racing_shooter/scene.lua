Scene = {}
Scene.Shaders = {
    {
        Name = "blinn_phong",
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