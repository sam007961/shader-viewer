#version 430

in vec3 vPosition;
in vec4 vPosLightSpace;
in vec2 vTexCoord;
in vec3 vNormal;
in mat3 vTBN;
out vec4 fragColor;

uniform sampler2D uTexture;
uniform sampler2D uSpecularMap;
uniform sampler2D uNormalMap;
uniform sampler2D uShadowMap;
uniform vec3 uAmbient;
uniform vec3 uLight;
uniform vec3 uLightColor;   

float getShadow(vec4 posLightSpace){
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    return currentDepth > closestDepth ? 1.0 : 0.0;
}

void main() {
    // shadow
    float shadow = getShadow(vPosLightSpace);

    //vec3 projCoords = vPosLightSpace.xyz / vPosLightSpace.w;
    //projCoords = projCoords * 0.5 + 0.5;
    //float closestDepth = texture(uShadowMap, projCoords.xy).r;
    //float currentDepth = projCoords.z;

    // normal
    vec3 normal = texture(uNormalMap, vTexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0); // map [0, 1] -> [-1, 1]
    normal = vTBN * normal;
    
    vec3 toLight = normalize(uLight - vPosition);
    vec3 toCamera = normalize(-vPosition);
    vec3 reflected = reflect(-toLight, normal);

    // material
    vec4 surfaceColor = texture(uTexture, vTexCoord);
    vec4 specularIntensity = texture(uSpecularMap, vTexCoord);

    // ambient
    vec3 ambient = uAmbient * surfaceColor.rgb;

    // diffuse
    float diff = max(dot(toLight, normal), 0.0);
    vec3 diffuse = diff * surfaceColor.rgb;

    // specular 
    float spec = pow(max(dot(toCamera, reflected), 0.0), 64);
    vec3 specular =  spec * specularIntensity.rgb;

    vec3 color = ((diffuse + specular)*(1.0 - shadow) + ambient) * uLightColor;
    fragColor = vec4(color, 1.0);
    //fragColor = vec4(vec3(currentDepth), 1.0);
}