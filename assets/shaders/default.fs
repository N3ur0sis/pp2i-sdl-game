#version 330

uniform mat4 model;
uniform vec3 cameraPosition;

uniform sampler2D materialTex;
uniform sampler2D shadowMap;
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
in vec4 fragPosLight;

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

    float shadow = 0.0;
    float bias = 0.0005;  
    vec3 lightCoord = fragPosLight.xyz / fragPosLight.w;
    if(lightCoord.z <= 1.0f){
        lightCoord = (lightCoord + 1.0f) / 2.0f;
        float closestDepth = texture(shadowMap, lightCoord.xy).r;
        float currenDepth = lightCoord.z;

        //if(currenDepth - bias > closestDepth)
          //  shadow = 1.0f;

        
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, lightCoord.xy + vec2(x, y) * texelSize).r; 
                shadow += currenDepth - bias > pcfDepth  ? 1.0 : 0.0;        
            }    
        }
        shadow /= 9.0;
    
        // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
        if(lightCoord.z > 1.0)
            shadow = 0.0;
        }


    //linear color (color before gamma correction)
    return ambient + attenuation*(diffuse * (1.0f - shadow) + specular);
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