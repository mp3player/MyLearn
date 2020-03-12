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

struct DirectionLight {
    vec3 color;
    vec3 pos;
    vec3 lookAt;
    float intensity;
};
uniform DirectionLight light;

out vec3 oColor;
out vec2 oUv;

void main(){
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1);

    oColor = color;
    oUv = uv;

    //计算法线
    vec3 transformNormal = normalize((normalMatrix * modelMatrix * vec4(normal,1)).xyz);
    //计算光线方向
    vec3 vec = normalize((viewMatrix * vec4(light.pos,1)).xyz - (viewMatrix* vec4(light.lookAt,1)).xyz);
    float angle = max(dot(transformNormal ,vec),0.0);
    vec3 dColor = angle * light.color * light.intensity;
    oColor = dColor;
}