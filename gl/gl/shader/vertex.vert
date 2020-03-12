precision mediump float;

attribute vec3 position;
attribute vec3 color;

varying vec3 vColor;

void main(){
    gl_Position = vec4(position,1);
    vColor = color;
}