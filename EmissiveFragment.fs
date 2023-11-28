#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;

// Material properties
uniform vec3 objectColor;  // Color of the object
uniform vec3 emissiveColor;  // Emissive color (emission)

void main()
{
    // Calculate the light emitted from the sphere
    vec3 emissive = emissiveColor;

    FragColor = vec4(emissive + objectColor, 1.0);
}