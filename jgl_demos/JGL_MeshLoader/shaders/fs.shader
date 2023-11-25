#version 330 core

/*
struct DirLight
{
  vec3 position;
  vec3 color;
  float strength;
};
*/

uniform mat4 model;
uniform vec3 albedo;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos; 
uniform sampler2D diffuseMap;

in vec2 TexCoord;
in vec3 WorldPos;
in vec3 Normal;

out vec4 fOutput;

void main ()
{
  //ambient
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;
  
  //diffuse
  mat3 normalMatrix = transpose(inverse(mat3(model)));
  vec3 normal = normalize(normalMatrix * Normal);
  vec3 light_Dir = normalize(lightPos - vec3(model * vec4(WorldPos, 1)));
  float diff = max(dot(normal, light_Dir), 0.0f);
  vec3 diffuse = diff * lightColor;
  
  //specular
  float specularStrength = 0.5f;
  vec3 viewDir = normalize(viewPos - vec3(model * vec4(WorldPos, 1)));
  vec3 reflectDir = reflect(-light_Dir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 result = (ambient + diffuse + specular) * texture(diffuseMap, TexCoord).rgb;//
  fOutput = vec4(result, 1.0f);
}