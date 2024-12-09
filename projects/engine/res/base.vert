#version 460 core

// Model & Camera matrices
layout(location=10)uniform mat4 worldMatrix;
layout(location=11)uniform mat4 viewMatrix;
layout(location=12)uniform mat4 projectionMatrix;
layout(location=13)uniform vec3 camPos;

// Vertices inputs
layout(location=0)in vec4 vPosition;
layout(location=1)in vec3 vNormal;
layout(location=2)in vec2 vTexCoord;
layout(location=3)in vec4 vColor;
// layout(location=4)in vec4 vBoneWeights;
// layout(location=5)in vec4 vBoneIndices;

// Output for the fragment shader (interpolation)
out vec3 fNormal;
out vec3 fPosition;
out vec2 fTexCoord;
out vec4 fColor;
// out vec4 fBoneWeights;
// out vec4 fBoneIndices;

void main()
{
	fTexCoord=vTexCoord;
	fColor=vColor;
	// fBoneWeights=vBoneWeights;
	// fBoneIndices=vBoneIndices;
	
	// Normal in world space
	fNormal=transpose(inverse(mat3(worldMatrix)))*-vNormal;
	// Position in world space
	fPosition=vec3(worldMatrix*vPosition);
	
	// Position in camera space
	gl_Position=projectionMatrix*viewMatrix*worldMatrix*vPosition;
}
