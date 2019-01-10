#version 430

uniform mat4 uModelViewMatrix;
uniform mat4 uModelLightSpaceMatrix;
uniform mat4 uProjectionMatrix;
uniform mat3 uNormalMatrix;

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 aTangent;
layout(location=4) in vec3 aBitangent;

out vec3 vPosition; // camera frame position (vec3)
out vec4 vPosLightSpace; // light-space position
out vec3 vNormal; // camera frame normal
out vec2 vTexCoord; // texture coordinates
out mat3 vTBN; // tangent-bitangent-normal matrix


void main() {
    // normal, tangent, bitangent
    vec3 T = normalize(vec3(uModelViewMatrix * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(uModelViewMatrix * vec4(aBitangent, 0.0)));
    vec3 N = normalize(uNormalMatrix * aNormal);
    vTBN = mat3(T, B, N);
    vNormal = N;

    // texture coordinates
    vTexCoord = aTexCoord; 

    // light-space
    vPosLightSpace = uModelLightSpaceMatrix * vec4(aPosition, 1.0);   

    // position
    vec4 cPosition =  uModelViewMatrix * vec4(aPosition, 1.0); // camera frame position (vec4
    vPosition = vec3(cPosition); 

    gl_Position = uProjectionMatrix * cPosition;
}