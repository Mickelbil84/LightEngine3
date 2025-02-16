-- Playground of Lua code, for tests while developing features.
-- None of this is actually required for neither the game nor the editor.

print("Hi! The playground is on")

print("Test shader bindings...")
a, b, c = LE3AssetManager.get_shaders()
print(a, b, c)
for i, _ in ipairs(a) do
    print(a[i], b[i], c[i])
end