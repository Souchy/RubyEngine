#version 460 core

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Vertices inputs
layout(location=0)in vec4 vPosition;
layout(location=1)in vec3 vNormal;
layout(location=2)in vec2 vTexCoord;
layout(location=3)in vec4 vColor;

// Output for the fragment shader (interpolation)
out vec3 fNormal;
out vec3 fPosition;
out vec4 fColor;
out vec2 fTexCoord;

void main()
{
	fTexCoord=vTexCoord;
	fColor=vColor;
	
	// Normal in world space
	fNormal=transpose(inverse(mat3(worldMatrix)))*-vNormal;
	// Position in world space
	fPosition=vec3(worldMatrix*vPosition);
	
	// Position in camera space
	gl_Position=projectionMatrix*viewMatrix*worldMatrix*vPosition;
}
