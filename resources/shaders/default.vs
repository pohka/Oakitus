#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;


void main()
{
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	gl_Position = projection *  model * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	
}