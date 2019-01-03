#version 430

in vec3 vPosition;
in vec3 vNormal;
out vec4 fragColor;

uniform vec3 uAlbedo;
uniform vec3 uAmbient;
uniform vec3 uLight;
uniform vec3 uLightColor;   

void main() {

    vec3 normal = normalize(vNormal);
    if(!gl_FrontFacing) normal = -normal;

    vec3 toLight = normalize(uLight - vPosition);
    vec3 toCamera = normalize(-vPosition);
    vec3 reflected = reflect(-toLight, normal);

    vec3 diffuse = max(dot(toLight, normal), 0.0) * uLightColor;
    vec3 specular = pow(max(dot(toCamera, reflected), 0.0), 32) * uLightColor;

    vec3 color = (diffuse + specular + uAmbient) * uAlbedo;
    fragColor = vec4(color, 1.0);
}