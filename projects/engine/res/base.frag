#version 460 core

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 viewPos;

// Entrées 
in vec4 fColor;             // Couleur provenant du vertex shader
in vec3 fNormal;            // Normale du fragment
in vec3 fPosition;          // Position du fragment
in vec2 fTexCoord;          // UV de texture
// in vec4 boneWeights;
// in vec4 boneIndices;

// Sorties
out vec4 oColor; 

void main()
{
	oColor = fColor;
}
