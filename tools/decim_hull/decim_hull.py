"""
Python script for quickly testing the mesh decimation + convex hull shape
(Which will then be implemented in C++ for convex hull shape for collision detection)
"""
import tqdm
import trimesh
import numpy as np


def get_aabb(mesh: trimesh.Trimesh):
    return np.min(mesh.vertices, axis=0), np.max(mesh.vertices, axis=0)

def get_bucket(v: np.array, n: int, bl: np.array, tr: np.array):
    tmp = n * (v - bl) / (tr - bl)
    tmp = tmp.astype(np.int64)
    i, j, k = tmp
    return i, j, k
    
def decimate_mesh(mesh: trimesh.Trimesh, n: int):
    bl, tr = get_aabb(mesh)
    buckets = [[[[] for _ in range(n+1)] for _ in range(n+1)] for _ in range(n+1)]
    bucket_faces = []
    for idx in tqdm.tqdm(range(mesh.faces.shape[0])):
        f = mesh.faces[idx]
        v1, v2, v3 = mesh.vertices[f[0]], mesh.vertices[f[1]], mesh.vertices[f[2]]
        i1, j1, k1 = get_bucket(v1, n, bl, tr)
        i2, j2, k2 = get_bucket(v2, n, bl, tr)
        i3, j3, k3 = get_bucket(v3, n, bl, tr)
        buckets[i1][j1][k1].append(v1)
        buckets[i2][j2][k2].append(v2)
        buckets[i3][j3][k3].append(v3)
        bucket_faces.append((
            (int(i1), int(j1), int(k1)), 
            (int(i2), int(j2), int(k2)),
            (int(i3), int(j3), int(k3))))
    
    vertices = []
    vertices_names = {}
    faces = []

    for i in tqdm.tqdm(range(n+1)):
        for j in range(n+1):
            for k in range(n+1):
                bucket = buckets[i][j][k]
                if len(bucket) == 0:
                    continue
                v = np.zeros((3,))
                for v_ in bucket:
                    v += v_
                v *= 1.0 / len(bucket)
                vertices.append(v)
                vertices_names[(i,j,k)] = len(vertices) - 1
    for idx1, idx2, idx3 in bucket_faces:
        faces.append((vertices_names[idx1], vertices_names[idx2], vertices_names[idx3]))
    
    return trimesh.Trimesh(vertices=np.array(vertices), faces=np.array(faces, dtype=np.int64))

def convex_hull(mesh: trimesh.Trimesh):
    vertices = [mesh.vertices[0], mesh.vertices[1], mesh.vertices[2]]
    faces = [(0,1,2)]

    for idx in range(3, len(mesh.vertices)):



if __name__ == "__main__":
    # filename = "resources/demos/models/animations/mannequin/SM_mannequin.obj"
    filename = "resources/demos/models/cars/Car Wheel.obj"
    out_filename = filename.replace(".obj", "_decim.obj")
    mesh = trimesh.load_mesh(filename)
    mesh_ = decimate_mesh(mesh, 15)
    mesh_.export(out_filename)