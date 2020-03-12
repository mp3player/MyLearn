#version 330 core
in vec2 oUv;
in vec3 oColor;

out vec4 fColor;

uniform sampler2D images;
//光照计算

void main(){
    vec3 color = texture(images,oUv).rgb;
    // fColor = vec4( color * oColor,1);
    fColor = vec4(oColor * color,1);
}