#version 460 core
out vec4 FragColor;

in vec2 TexCoords;


uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between the two textures (%80 container, %20 awesomeface)
	FragColor = mix(texture(texture1, TexCoords), texture(texture2, TexCoords), 0.2); 
}