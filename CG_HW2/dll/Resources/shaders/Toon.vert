#version 330 core

//////////////////// TODO /////////////////////
/*
* Hint:
* 1. Receive position, normal, texcoord from bind buffer
* 2. Receive Model matrix, View matrix, and Projection matrix from uniform
* 3. Pass texcoord, worldPos and Normal to fragment shader
* 4. Calculate view space by gl_Position (must be vec4)
*/

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // normal
layout (location = 2) in vec2 aTexCoord; // texture coordination

out vec3 Normal;
out vec2 TexCoord;
out vec3 WorldPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	gl_Position = P * V * M * vec4(aPos, 1.0);
	WorldPos = (M * vec4(aPos, 1.0)).xyz;
	Normal = mat3(transpose(inverse(M))) * aNormal;
	TexCoord = aTexCoord;
}
