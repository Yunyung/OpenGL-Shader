#version 330 core

//////////////////// TODO /////////////////////
/*
* Hint:
* 1. Receive mainTex, rampTex and WorldLightPos from uniform
* 2. Recieve texcoord, worldPos and Normal from vertex shader
* 3. Calculate and return final color to opengl
*/

out vec4 FragColor;

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoord;

uniform sampler2D mainTex;
uniform sampler2D rampTex;

uniform vec3 WorldLightPos;
uniform vec3 Kd;

vec3 N = normalize(Normal);
vec3 L = normalize(WorldLightPos - WorldPos);

void main()
{
	vec4 albedo = texture2D(mainTex, TexCoord);
	float rampCoord = max(dot(N, L), 0.0) * 0.5 + 0.5; // must between (0,1)
	if (rampCoord > 0.99) rampCoord = 0.99;
	if (rampCoord < 0.01) rampCoord = 0.01;
	vec4 diffuse = texture(rampTex, vec2(rampCoord, rampCoord));
	vec4 color = diffuse * vec4(Kd, 1.0) * albedo;

	// out color must be vec4
	FragColor = color;

}