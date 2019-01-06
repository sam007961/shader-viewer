#version 430

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

layout(location=0) in vec3 aPosition;

void main() {
    gl_Position = uProjectionMatrix * uModelViewMatrixvec4(aPosition, 1.0);
}