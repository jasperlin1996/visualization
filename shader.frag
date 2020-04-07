#version 430 core
out vec4 frag_color;

in vec3 our_color;
in vec3 normal;
in vec3 frag_pos;

uniform vec3 light_pos; 
uniform vec3 view_pos; 
uniform vec3 light_color;

varying float check;

void main()
{
    
    frag_color = vec4(our_color, 1.0f);

    if(check < 0.0) {
        discard;
    }
    
    vec3 norm = normalize(normal);

    vec3 light_direction = normalize(light_pos - frag_pos);
    vec3 view_direction = normalize(view_pos - frag_pos);

    if (dot(norm, -view_direction) < 0) {
        norm = -norm;
    }

    vec3 reflect_direction = reflect(-light_direction, norm);

    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_color;

    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light_color;

    float specular_strength = 0.5;
    vec3 specular = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * light_color;

    vec3 light = clamp((ambient + diffuse + specular), vec3(0.0), vec3(1.0)) * our_color;
    frag_color = vec4(light, 1.0);
}
