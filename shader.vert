#version 430 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

out vec3 our_color;
out vec3 normal;
out vec3 frag_pos;

uniform vec3 color;
uniform mat4 model;
uniform mat4 matrix;

uniform vec4 ClipPlane;
out float check;

void main()
{
    frag_pos = vec3(model * vec4(a_pos, 1.0));

    check = dot(vec4(frag_pos, 1.0), ClipPlane);

    gl_Position = matrix * vec4(a_pos, 1.0);
    normal = mat3(transpose(inverse(model))) * a_normal;
    our_color = color;
}
