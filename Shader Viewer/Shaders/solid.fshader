#version 130
// in vec3 vPosition;
// in vec3 vNormal;
// in vec3 vTexCoord;

// uniform sampler2D uTex;
// uniform vec3 uLightPosition;
uniform vec3 uColor;

out vec4 fragColor;
void main(){
    fragColor = vec4(uColor, 1.0);
}