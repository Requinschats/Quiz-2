#version 330 core

//comments also apply to the color shader

const float PI = 3.1415926535897932384626433832795;

//attributes set from the code that apply lighting
//_N refers to the light's index
uniform vec3 light_color;
uniform vec3 light_position_0;
uniform vec3 light_position_1;
uniform vec3 light_direction_0;
uniform vec3 light_direction_1;
uniform vec3 object_color;


// attributes of the lighting: strength, how much its spreads...
const float shading_ambient_strength = 0.6;
const float shading_diffuse_strength = 0.6;
const float shading_specular_strength = 0.6;


//more lighting attributes refering to the light's index
uniform float light_cutoff_outer;
uniform float light_cutoff_inner;
uniform float light_near_plane_0;
uniform float light_near_plane_1;
uniform float light_far_plane_0;
uniform float light_far_plane_1;
uniform vec3 view_position;
uniform sampler2D shadow_map;
uniform sampler2D textureSampler;


//inputs from the vertex shader
in vec3 fragment_position;
in vec4 fragment_position_light_space;
in vec3 fragment_normal;
in vec3 fragment_color;
in vec4 gl_FragCoord;
in vec2 vertexUV;
in float fragment_alpha;

//output of the fragment shader
out vec4 result;
out vec4 FragColor;

//computes the ambient color of the object
vec3 ambient_color(vec3 light_color_arg) {
    return shading_ambient_strength * light_color_arg;
}

//computes the diffuse color of the object
vec3 diffuse_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction_0 = normalize(light_position_arg - fragment_position);
    return shading_diffuse_strength * light_color_arg * max(dot(normalize(fragment_normal), light_direction_0), 0.0f);
}

//computes the specular color of the object
vec3 specular_color(vec3 light_color_arg, vec3 light_position_arg) {
    vec3 light_direction_0 = normalize(light_position_arg - fragment_position);
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_light_direction = reflect(-light_direction_0, normalize(fragment_normal));
    return shading_specular_strength * light_color_arg * pow(max(dot(reflect_light_direction, view_direction), 0.0f), 32);
}

//computes the shadow color of the object
float shadow_scalar() {
    vec3 normalized_device_coordinates = fragment_position_light_space.xyz / fragment_position_light_space.w;
    normalized_device_coordinates = normalized_device_coordinates * 0.5 + 0.5;
    float closest_depth = texture(shadow_map, normalized_device_coordinates.xy).r;
    float current_depth = normalized_device_coordinates.z;
    float bias = 0;
    return ((current_depth - bias) < closest_depth) ? 1.0 : 0.0;
}


//computes the scalar of the first light
float spotlight_scalar_0() {
    float theta = dot(normalize(fragment_position - light_position_0), light_direction_0);

    if (theta > light_cutoff_inner) {
        return 1.0;
    } else if (theta > light_cutoff_outer) {
        return (1.0 - cos(PI * (theta - light_cutoff_outer) / (light_cutoff_inner - light_cutoff_outer))) / 2.0;
    } else {
        return 0.0;
    }
}

//computes the scalar of the second light
float spotlight_scalar_1() {
    float theta = dot(normalize(fragment_position - light_position_1), light_direction_1);

    if (theta > light_cutoff_inner) {
        return 1.0;
    } else if (theta > light_cutoff_outer) {
        return (1.0 - cos(PI * (theta - light_cutoff_outer) / (light_cutoff_inner - light_cutoff_outer))) / 2.0;
    } else {
        return 0.0;
    }
}

void main()
{
    vec3 ambient = vec3(0.0f);
    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);

    //computes the exact color of the pixel from the previous lighting computations and the texture
    float scalar_0 = shadow_scalar() * spotlight_scalar_0();
    float scalar_1 = shadow_scalar() * spotlight_scalar_1();
    ambient = ambient_color(light_color);
    diffuse = scalar_1 * scalar_0 * diffuse_color(light_color, light_position_0);
    specular = scalar_1 * scalar_0 * specular_color(light_color, light_position_0);

    FragColor = vec4((vec3(texture(textureSampler, vertexUV)) * (specular + diffuse + ambient)), fragment_alpha);
}