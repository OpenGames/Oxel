#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D texSampler;


void main()
{
	color = vec4(uv, 1.0f, 1.0f);//texture(texSampler, uv);
	//color = texture(texSampler, uv);
}