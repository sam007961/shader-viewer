#version 430

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

layout(location=0) in vec3 aPosition;
layout(location=2) in vec2 aTexCoord;

out vec2 vTexCoord; // texture coordinates

void main() {
    // texture coordinates
    vTexCoord = aTexCoord; 
    
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPosition, 1.0);
}