# RayTracer

# TODO
- add bi-linear interpolation for texture lookup
- add functionality to read normal maps

# Notes
- The file reader expects that vertices, normals, and texturecoords before the faces are defined.
- Textures must be placed in the `/input/texture/` directory for the program to find it.
- Program defaults to using hard-shadows. Add `softshadows 1` to the input description to use softshadows with point lights and attenuated point lights. This will significantly slow down the program.
- The `/images` directory contains images showcasing the different capabilities of the program. Their corresponding input file can be found in `/input`

# Rendering
The program has the following rendering capabilities:
- Spheres
- Triangles
- Lighting using the Blinn-Phong illumination model
- Directional lights
- Point lights
- Light source attenuation
- Depthcueing
- Shadows
- Soft shadows
- Texture mapping
- Reflections
- Refractions

# Overview
This program takes the name of a scene description file and outputs a `.ppm` file. The program has raytracing functionality. It can render spheres, and cast rays into the scene to determine if a ray intersects with a sphere. Spheres are shaded using the Blinn-Phong illumination model. Shading and raycasting is done inside of scene.cpp and pixels are written to the output file in render.cpp. Recursive raytracing is used to model the reflective and refractive properties of materials as described by their material properties.

The program is capable of mapping textures to both spheres and triangles. 

Input files should contain some or all of the following information:
```
imsize width height
eye x y z
viewdir x y z
vfov degrees
updir x y z
bkgcolor r g b refractionIndex
mtlcolor odr odg odb osr osg osb ka kd ks n opacity refractionIndex
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

softshadows flag

```

# Input File Parameters
*imsize*
- `imsize` defines the resolution of the output image
- `width` the width of the image
- `height` the height of the image

  
*eye*
- `eye` defines the location of the eye (or camera) from which the scene is viewed from
- `x` the x position of the eye in a 3d plane
- `y` the y position of the eye in a 3d plane
- `z` the z poisition of the eye in a 3d plane

*viewdir*
- `viewdir` the direction from which the eye is looking into the scene from
- `x` the x component of a 3d vector to describe a direction
- `y` the y component of a 3d vector to describe a direction
- `z` the z component of a 3d vector to describe a direction
  
*vfov*
- `vfov` the vertical field of view for the viewing window
- `degrees` the amount in degrees to describe the vertival field of view
  
*updir*
- `updir` the up direction relative the the eye
- `x` the x component of a 3d vector to describe a direction
- `y` the y component of a 3d vector to describe a direction
- `z` the z component of a 3d vector to describe a direction

*bkgcolor*
- `bkgcolor` the color of the background
- `r` the red color component [0.0-1.0]
- `g` the green color component [0.0-1.0]
- `b` the blue color component [0.0-1.0]

*mtlcolor*
- `mtlcolor` defines the material properties of the objects that are included below this parameter in the input file
- `odr` the red component of the material's diffuse color [0.0-1.0]
- `odg` the green component of the material's diffuse color [0.0-1.0]
- `odb` the blue component of the material's diffuse color [0.0-1.0]
- `osr` the red component of the material's specular color [0.0-1.0]
- `osg` the green component of the material's specular color [0.0-1.0]
- `osb` the blue component of the material's specular color [0.0-1.0]
- `ka` the ambient coefficient of the mateial [0.0-1.0]
- `kd` the diffuse coefficient of the material [0.0-1.0]
- `ks` the specular coefficient of the material [0.0-1.0]
- `n` the specular exponent of the material
- `opacity` the material's opacity [0.0-1.0]
- `refractionIndex` the materials index of refraction

*sphere*
- `sphere` a sphere object
- `x` the x position of the sphere in a 3d plane
- `y` the y position of the sphere in a 3d plane
- `z` the z poisition of the sphere in a 3d plane
- `r` the radius of the sphere

*light*
- `light` a light used in the scene (can be a point light or directional light)
- `x` the x position or x component of a direction
- `y` the y position or y component of a direction
- `z` the z position or z component of a direction
- `w` 1 for a point light (xyz are then a position) or 0 for a directional light (xyz are then a direction)
- `i` the intensity of the light [0.0-1.0]

*attlight*
- `attlight` an attenuated light source where the light intensity falls off with distance from the light
- `x` the x position 
- `y` the y position
- `z` the z position 
- `w` attenuated lights will always be a point light
- `i` the intensity of the light [0.0-1.0]
- `c1` attenuation coefficient to describe the drop off
- `c2` attenuation coefficient to describe the drop off
- `c3` attenuation coefficient to describe the drop off

*depthcueing*
- `depthcueing` adds the effect of depthcueing where objects further away blend into the background
- `dcr` the red component of the depthcueing blend color [0.0-1.0]
- `dcg` the green component of the depthcueing blend color [0.0-1.0]
- `dcb` the blue component of the depthcueing blend color [0.0-1.0]
- `aMin` the minimum value of the blending factor that should be applied
- `aMax` the maximum value of the blending factor that should be applied (choose aMin and aMax to range in [0.0-1.0]
- `distMin` the minimum distance when the blending factor should begin to be applied
- `distMax` the maximum distance the blending factor should be applied

*v*
- `v` describes a vertex in the scene (used to create triangles)
- `x` the x position of the vertex in a 3d plane
- `y` the y position of the vertex in a 3d plane
- `z` the z poition of the vertex in a 3d plane

*vt*
- `vt` describes a texture coordinate of a vertex [(0,0)-(1,1)] where (0,0) is the top-left corner and (1,1) is the bottom-right corner
- `u` the horizontal value
- `v` the vertical value

*vn*
- `vn` describes a normal for a vertex
- `x` the x direction of the normal
- `y` the y direction of the normal
- `z` the z direction of the normal

*texture*
- `texture` a texture map in the form of a `.ppm` using the P3 format. Specifically it should follow the format:

   ```
      P3
      width height
      maxColorValue (a value [0-255])
      r g b r g b r g b ...
   ```
- `filename` the name of the file which follows the format described above

*f*
- `f` describes a triangle face which can follow three different formats:
    - `v1 v2 v3` forms a triangle using three of the supplied vertices supplied in the input file
    - `v1/vt1 v2/vt2 v3/vt3` forms a triangle with three vertices and attaches a corresponding texture coordinate to each vertex
    - `v1//vn1 v2//vn2 v3//vn3` forms a triangle with three vertices and attaches a normal to each vertex
    - `v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3` forms a triangle with three vertices and attachs a normal and texture coordinate to each vertex

*softshadows*
- `softshadows` simulates how light bleeds around objects and doesn't cast a hard shadow
- `flag` 0 for off and 1 for on. Omitting this defaults to off

**Example scene description**
```
imsize 512 512
eye  0 0 5
viewdir  0 0 -1
updir  0 1 0
vfov 60

bkgcolor 0.7 0.7 0.7 1

light 4 0 0 1 1

mtlcolor 0.2 1 0.2 1 1 1 0.2 0.6 0.0 100 1.0 1.0
sphere -4 0 -3 2

mtlcolor 1 0 0 1 1 1 0.02 0.06 0.2 100 0.2 1.5
sphere 0 0 -3 2

softshadows 0

```
# Usage
Include any desired texture files inside of `/input/texture/`.
Then, run the following commands
```
make
./raytracer1d input/showcase.txt
```
The output file will be in the same location where the input file is.

Clean the build files using.
```
make clean
```
