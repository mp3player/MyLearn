#version 330 core

// #pragma debug(on)
// #pragma optimize(on)

layout(location = 0)in vec3 position;
layout(location = 1)in vec3 color;
layout(location = 2)in vec2 uv;
layout(location = 3)in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 oColor;
out vec2 oUv;
out vec3 oNormal;
out vec3 oPosition;

void main(){
    oPosition = (viewMatrix * modelMatrix * vec4(position,1)).xyz;
    gl_Position = projectionMatrix * vec4(oPosition,1) ;

    oUv = uv;
    //计算法线
    oNormal = normalize((normalMatrix * modelMatrix * vec4(normal,1)).xyz);
    
}