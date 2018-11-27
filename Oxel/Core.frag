#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D texSampler;

uniform float rx;
uniform float ry;

vec2 repeatUV(vec2 invec, float x, float y);


void main()
{
	color = texture(texSampler, repeatUV(uv, rx, ry));//vec4( repeatUV(uv, 3f, 3f) , 1.0f, 1.0f);//
	//color = texture(texSampler, uv);
}

vec2 repeatUV(vec2 uv, float x, float y)
{
	return vec2(uv.x * x, uv.y * y);
}