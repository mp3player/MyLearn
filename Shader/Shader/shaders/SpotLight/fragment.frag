#version 330 core
in vec2 oUv;
in vec3 oColor;
in vec3 oNormal;
in vec3 oPosition;

out vec4 fColor;

uniform sampler2D images;
//环境光
struct AmbientLight{
    vec3 color;
    float intensity;
};
//光照计算
struct SpotLight {
    vec3 position;
    vec3 lookAt;
    vec3 color;
    float intensity;
};
uniform AmbientLight ambient;
uniform SpotLight light;
uniform mat4 viewMatrix;


void main(){
    //图片采样
    vec3 color = texture(images,oUv).rgb;
    //输出片元颜色
    fColor = vec4(oColor * color,1);
    //计算法线
    vec3 normal = normalize(oNormal);
    //计算光线照射方向
    vec3 vec = normalize((viewMatrix * vec4(light.position,1)).xyz - (viewMatrix * vec4(light.lookAt,1)).xyz);
    //计算光线方向
    vec3 lightVec = normalize((viewMatrix * vec4(light.position,1)).xyz - oPosition);
    //计算光线和照射方向的夹角
    float off = max(dot(vec,lightVec),0);
    //计算照射的夹角
    float angle = max(dot(normal,normalize(-lightVec)),0.0);

    if(off > .8){

        fColor = vec4((ambient.color * ambient.intensity + light.color * light.intensity * angle * pow(off,10)) * color.rgb ,1);
    }else{
        fColor = vec4(ambient.color * ambient.intensity * color.rgb,1);
    }

    //fColor = vec4(ambient.color,1);


}