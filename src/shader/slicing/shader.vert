#version 430 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 texture_pos;

out vec3 fragment_pos;
out vec3 fragment_texture_pos;
out float check;

uniform mat4 model;
uniform mat4 matrix;

uniform vec4 clip_plane;

void main()
{
    fragment_pos = vec3(model * vec4(a_pos, 1.0));
    fragment_texture_pos = texture_pos;

    check = dot(vec4(fragment_pos, 1.0), clip_plane);

    gl_Position = matrix * vec4(a_pos, 1.0);

}
