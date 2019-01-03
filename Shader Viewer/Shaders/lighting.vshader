#version 430

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat3 uNormalMatrix;

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

out vec3 vPosition; // camera frame position (vec3)
out vec3 vNormal; // camera frame normal
out vec2 vTexCoord; // texture coordinates

void main(){
    vNormal = uNormalMatrix * aNormal;
    vTexCoord = aTexCoord; 
    vec4 cPosition =  uModelViewMatrix * vec4(aPosition, 1.0); // camera frame position (vec4)
    vPosition = vec3(cPosition); 
    gl_Position = uProjectionMatrix * cPosition;
}