#version 430

in vec2 vTexCoord;

uniform sampler2D uTexture;

out vec4 fragColor;

void main() {

   vec3 color = texture(uTexture, vTexCoord).rgb;
   fragColor = vec4(color, 1.0);
}