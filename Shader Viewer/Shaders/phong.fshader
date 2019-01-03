#version 430

in vec3 vPosition;
in vec3 vNormal;
out vec4 fragColor;

uniform vec3 uAlbedo;
uniform vec3 uAmbient;
uniform vec3 uLight;

void main() {
    vec3 normal = normalize(vNormal);
    if(!gl_FrontFacing) normal = -normal;
    vec3 toLight = normalize(uLight - vPosition);
    float diffuse = clamp(dot(toLight, normal), 0, 1);
    vec3 color = diffuse * uAlbedo + uAmbient * uAlbedo;
    fragColor = vec4(color, 1.0);
}