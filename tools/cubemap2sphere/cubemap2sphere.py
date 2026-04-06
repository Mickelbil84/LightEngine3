import cv2
import numpy as np

def proj2sphere(x, y):
    """
    Take "projected" pixel (in continous space) and return its corresponding 3d point on the sphere
    x: longitude (-pi,pi)
    y: latitude (-pi/2, pi/2)
    """
    return (
        np.cos(y) * np.cos(x),
        np.cos(y) * np.sin(x),
        np.sin(y)
    )

def cast_ray_to_cube(ray):
    """
    Assume we have a cube defined by the intersection of the hyperplanes x=+-1, y=+-1, z=+-1
    Cast a ray from origin towards a 3D point (on the sphere).
    Return the plane index, in the following correspondance:
        [x=-1  x=1   y=-1  y=1  z=-1  z=1]
        [0     1     2     3    4     5  ]
    Also return the x,y inside the plane
    Note that the line equation is l(t) = t * v (and t>=0)
    So if l(t) intersects with say x=-1, then we solve for t * (vx, vy, vz) = (-1, t*vy, t*vz)
    and t = -1/vx.
    But it may intersect first with another plane.
    So we always need to take the first intersection among the three possible planes (corresponding to the sign of each coord)
    """
    vx, vy, vz = ray
    plane_x = 0 if vx < 0 else 1
    plane_y = 2 if vy < 0 else 3
    plane_z = 4 if vz < 0 else 5
    plane_indices = [plane_x, plane_y, plane_z]

    tx = 1 / abs(vx)
    ty = 1 / abs(vy)
    tz = 1 / abs(vz)
    idx = np.argmin((tx,ty,tz))
    t = np.min((tx, ty, tz))
    
    coord = []
    for i in range(3):
        if i == idx:
            continue
        coord.append(ray[i] * t)
    return plane_indices[idx], tuple(coord)


def pixel2proj(i, j, w, h):
    return (
        (i / (w-1)) * 2 * np.pi - np.pi,
        (j / (h-1)) * np.pi - 0.5 * np.pi
    )

def lookup_plane(coord, w, h):
    x, y = coord
    i = int(0.5 * (x + 1) * (w-1))
    j = int(0.5 * (y + 1) * (h-1))
    return (i,j)


if __name__ == "__main__":
    cw = 128
    ch = 128
    w = 1024
    h = 512
    cubemaps = [np.zeros((ch, cw, 3)) for _ in range(6)]
    result = np.zeros((h, w, 3))

    cubemaps[0][:,:] = np.array([1,0,0])
    cubemaps[1][:,:] = np.array([0,1,0])
    cubemaps[2][:,:] = np.array([0,0,1])
    cubemaps[3][:,:] = np.array([1,1,0])
    cubemaps[4][:,:] = np.array([1,0,1])
    cubemaps[5][:,:] = np.array([0,1,1])

    for i in range(w):
        for j in range(h):
            x, y = pixel2proj(i, j, w, h)
            ray = proj2sphere(x, y)
            idx, coord = cast_ray_to_cube(ray)
            i_, j_ = lookup_plane(coord, cw, ch)
            result[j,i,:] = cubemaps[idx][j_, i_, :]
    cv2.imwrite("spheremap.png", result*255)
