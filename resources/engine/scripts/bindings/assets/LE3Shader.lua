LE3Shader.load = function (scene, shader_table)
    LE3Scene.add_shader(scene, shader_table.Name, shader_table.VertexSource, shader_table.FragmentSource)
end