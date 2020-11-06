#version 330 core

//////////////////// TODO /////////////////////
/*
* Hint:
* 1. Receive mainTex, noiseTex, and other variables passed from uniform
* 2. Recieve texcoord from vertex shader
* 3. Calculate and return final color to opengl
*/

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D mainTex;
uniform sampler2D noiseTex;

uniform float _EdgeLength;
uniform float _Threshold;
uniform vec3 _EdgeColor;

void main()
{
    vec3 albedo = texture2D(mainTex, TexCoord).rgb;
    float noise = texture(noiseTex, TexCoord).x;

    if (noise - _Threshold < 0.0)
        discard;

    // use EdgeLength/2 as threshold to prevent
    // exactly _Threshold + _EdgeLength - noise is 0
	float flag = step(_EdgeLength/2, _Threshold+_EdgeLength-noise);
	
    vec3 color = mix(albedo, _EdgeColor, flag);
	// out color must be vec4
    FragColor = vec4(color, albedo);
}

