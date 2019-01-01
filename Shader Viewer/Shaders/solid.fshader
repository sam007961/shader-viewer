#version 130

uniform vec3 uAlbedo;

out vec4 fragColor;
void main(){
    fragColor = vec4(uAlbedo, 1.0);
}