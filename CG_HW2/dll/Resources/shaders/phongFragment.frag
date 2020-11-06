#version 330 core

//////////////////// TODO /////////////////////
/*
* Hint:
* 1. Receive mainTex, WorldLightPos and WorldCamPos from uniform
* 2. Recieve all light color you defined in opengl from uniform
* 3. Recieve texcoord, worldPos and Normal from vertex shader
* 4. Calculate and return final color to opengl
*/

out vec4 FragColor;

in vec3 Normal;
in vec3 WorldPos;
in vec2 TexCoord;

uniform sampler2D mainTex;

uniform vec3 WorldCamPos;
uniform vec3 WorldLightPos;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 La;
uniform vec3 Ld;
uniform vec3 Ls;
uniform float gloss; 

vec3 N = normalize(Normal);
vec3 L = normalize(WorldLightPos - WorldPos);
vec3 V = normalize(WorldCamPos - WorldPos);
vec3 R = normalize(reflect(-L, N));
vec3 H = normalize(L + V);

void main()
{
    vec3 albedo = texture2D(mainTex, TexCoord).rgb;
    vec3 ambient = La * Ka * albedo;
    vec3 diffuse = Ld * Kd * albedo * max(dot(L, N), 0.0);

    vec3 specularPhong = Ls * Ks * pow(max(dot(V, R), 0.0), gloss / 4.0);
    vec3 specularBlinn = Ls * Ks * pow(max(dot(N, H), 0.0), gloss);
    vec3 specular = mix(specularPhong, specularBlinn, 0);

    vec3 color = ambient + diffuse + specular;
    // out color must be vec4
    FragColor = vec4(color, 1.0);
}
