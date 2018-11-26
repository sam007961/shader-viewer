#version 130
in vec3 aPosition;
in vec3 aNormal;
// in vec3 aTexCoord;

// uniform mat4 uModelViewMatrix;
// uniform mat4 uProjectionMatrix;
// uniform mat4 uNormalMatrix;

// out vec3 vPosition;
// out vec3 vNormal;
// out vec3 aTexCoord;

void main(){
    gl_Position = vec4(aPosition.x, aPosition.z, 0, 0);
}