# LIYM triple quantizer
takes a liym as an input and creates C header files of compressed data in the format the Wii's GP supports. the name is misleading it does double quantization for texture coordinates
## Concept
to save space on models, we can assign pieces of model data in float form to smaller indecies in integer form. generally, the larger the pieces of the float data we can assign to each integer, the smaller our resulting data can be. 
## Philosophy
3d models tend to have an inherent locality, where it is often that one will want to create closed meshes in a 3d model to create the illusion of a complete object. to achieve this, one creates meshes where the edges of each triangle touch eachother. this locality implies that the vertecies of each triangle will have the same position of some of the vertecies as other triangles, and thus the data making up the position and often the normal, and texture coordinate of that vertex, can often be reused. for positions and normals, we index 3 floats with 1 int, and for texture coordinates, we index 2 floats with 1 int. this is the quantized data format that the Wii's GP supports.
