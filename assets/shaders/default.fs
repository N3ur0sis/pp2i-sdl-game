#version 330 core


in vec3 fragPosition;
in vec2 fragTexture;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D sampler;

uniform mat4 transformationMatrix;
uniform mat4 normalTransformationMatrix;

uniform vec3 ambientLightColor;
uniform float ambientLightIntensity;

uniform vec3 pointLightColor;
uniform vec3 pointLightPosition;
uniform float pointLightIntensity;
uniform float pointLightAttenuation;

void main() {
    // ambient
    vec3 ambient = ambientLightIntensity * ambientLightColor;
  	
    // diffuse 
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(pointLightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * pointLightColor;
            
    vec3 result = (ambient + diffuse);
	vec4 surfaceColor = texture(sampler, fragTexture);
    fragColor = vec4(result * surfaceColor.rgb, surfaceColor.a);
}