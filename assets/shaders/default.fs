#version 330

uniform mat4 model;
uniform vec3 cameraPosition;

uniform sampler2D materialTex;
float materialShininess = 250;
vec3 materialSpecularColor = vec3(0.5);

uniform struct Light {
   vec4 position;
   vec3 intensities; //a.k.a the color of the light
   float attenuation;
   float ambientCoefficient;
} allLights;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; //no attenuation for directional lights
    }

    //ambient
    vec3 ambient = light.ambientCoefficient * surfaceColor.rgb * light.intensities;

    //diffuse
    float diffuseCoefficient = max(dot(normal, surfaceToLight), 0.0);
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;
    
    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * light.intensities;

    //linear color (color before gamma correction)
    return ambient + attenuation*(diffuse + specular);
}

void main() {
    vec3 normal = normalize(transpose(inverse(mat3(model))) *fragNormal);
    vec3 surfacePos = vec3(model * vec4(fragVert, 1.0));
    vec4 surfaceColor = texture(materialTex, fragTexCoord);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

    //combine color from all the lights
    vec3 linearColor = vec3(0);
    linearColor += ApplyLight(allLights, surfaceColor.rgb, normal, surfacePos, surfaceToCamera);
    
    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);
}