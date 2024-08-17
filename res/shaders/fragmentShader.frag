#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewerPos;

void main()
{
    float ambientStrength = 0.1;
    // Ambience
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - FragPos);

    // Diffuse 
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;

    // Changed around viewerPos and FragPos since for some reason it ended up on the bottom of my cube.

    vec3 viewDirection = normalize(FragPos - viewerPos);
    vec3 reflectDir = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}