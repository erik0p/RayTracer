# RayTracer

# Notes
- Flat-shaded triangles are contained in the Triangle class.
- Smooth-shaded triangles are contained in the SmoothShadedTriangle class.
- The file reader currently expects that vertices, normals, and texturecoords before the faces are defined.
- Need to refactor Objects to no longer have a Material object, and instead use a material index. The program consumes a large amount of memory and this should help reduce memory usage. Example7.txt used over 1.5gb of memory
- Textures must be placed in the input/texture/ directory for the program to find it.
- Point lights slow down the program significantly due to needing to shoot many jittered shadow rays
- showcase image obj file and texture obtained from https://www.cgtrader.com/free-3d-models/exterior/landscape/free-low-poly-granite-rock-108f002d-0232-4af4-8906-fe0dd21ba16e

# Overview
This program takes the name of a scene description file and outputs a `.ppm` file. The program has raytracing functionality. It can render spheres, and cast rays into the scene to determine if a ray intersects with a sphere. Spheres are shaded using the Blinn-Phong illumination model. Shading and raycasting is done inside of scene.cpp and pixels are written to the output file in render.cpp. In this program all point lights (including attenuated point lights) use soft shadows, and all directional lights use hard shadows. 

The program is capable of mapping textures to both spheres and triangles. 

Input files should contain some or all of the following information:
```
imsize width height
eye x y z
viewdir x y z
vfov degrees
updir x y z
bkgcolor r g b
mtlcolor odr odg odb osr osg osb ka kd ks n
sphere x y z r
light x y z w i
attlight x y z w i c1 c2 c3
depthcueing dcr dcg dcb aMin aMax distMin distMax
v x y z
vt u v
vn x y z
texture filename.ppm
f v1 v2 v3
f v1/vt1 v2/vt2 v3/vt3
f v1//vn1 v2//vn2 v3//vn3
f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
```
**Example scene description**
```
imsize 512 512
eye 0 0 2
viewdir 0 0 -1
updir 0 1 0
vfov 45
bkgcolor 0.1 0.1 0.1
light -2 1 0 1 1
mtlcolor 0 1 1 1 1 1 0.2 0.6 0.2 20
texture wood.ppm
v -1 1 -4
v -1 -1 -4
v 1 -1 -4
v 1 1 -4

f 1 2 3
```

# Usage
Clean the object files using
```
make clean
```
Run the following commands
```
make
./raytracer1c input/showcase.txt
```
The output file will be in the same location where the input file is.
