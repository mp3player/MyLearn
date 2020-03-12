#version 330 core
in vec2 oUv;
in vec3 oColor;
in vec3 oNormal;
in vec3 oPosition;

out vec4 fColor;

uniform sampler2D images;
//光照计算
struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};
uniform PointLight light;
uniform mat4 viewMatrix;

void main(){
    //图片采样
    vec3 color = texture(images,oUv).rgb;
    //输出片元颜色
    fColor = vec4(oColor * color,1);
    
    //计算光线方向
    vec3 pointVector = normalize((viewMatrix * vec4(light.position,1)).xyz - oPosition);
    vec3 normal = normalize(oNormal);

    float angle = max(dot(pointVector,normal),0.0);

    float len = distance(light.position,oPosition);

    fColor = vec4(light.color * angle * color.rgb * light.intensity / len ,1);


}