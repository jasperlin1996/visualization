#version 430 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

out vec4 object_color;

uniform mat4 matrix;

void main(){
    object_color = vec4(color, 1.0f);
    
    gl_PointSize = 2.0f;
    gl_Position = matrix * vec4(pos, 0.0, 1.0);
}