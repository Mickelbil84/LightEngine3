PointCloudDemo = LE3ScriptObject:new()
function PointCloudDemo:init()
    LE3Scene.add_point_cloud(self.scene, "pointcloud", "M_default")
    self.pc = LE3Scene.get_object(self.scene, "pointcloud")
    LE3PointCloud.set_point_size(self.pc, 10.0)
    LE3DrawableObject.set_cast_shadow(self.pc, false)
    LE3Transform.set_position(LE3Object.get_transform(self.pc), 6, 1.2, 0)

    for i=1,100000 do 
        x = math.random() * 2 - 1; y = math.random() * 2 - 1; z = math.random() * 2 - 1
        norm = math.sqrt(x * x + y * y + z * z)
        x = x / norm; y = y / norm; z = z / norm
        LE3PointCloud.add_point(self.pc, x, y, z, x, y, z)
    end
    LE3PointCloud.create(self.pc)
end