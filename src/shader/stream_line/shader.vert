#version 430 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 color;
layout (location = 2 ) in float scale;

out vec4 object_color;

uniform mat4 matrix;

void main(){
    object_color = color;
    
    gl_PointSize = scale;
    gl_Position = matrix * vec4(pos, 0.0, 1.0);
}