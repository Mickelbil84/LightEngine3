LE3Shader.load = function (shader_table)
    LE3AssetManager.add_shader(shader_table.Name, shader_table.VertexSource, shader_table.FragmentSource)
end
LE3Shader.rebuild = function (shader, tbl)
    LE3Shader.set_name(shader, tbl.Name)
end
LE3Shader.save = function (shader)
    local name = shader
    local vertex_source, fragment_source = LE3AssetManager.get_shader_paths(shader)

    return {
        Name = name,
        VertexSource = vertex_source,
        FragmentSource = fragment_source
    }
end
LE3Shader.title = "LE3Shader"
LE3Shader.properties = {
    {name = "Name", type = "string"},
    {name = "VertexSource", type = "string"},
    {name = "FragmentSource", type = "string"}
}