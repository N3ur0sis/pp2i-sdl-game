#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 depthMVP;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec4 fragPosLight;

void main() {
    vec3 currentPos = vec3(model * vec4(position, 1.0f));
    gl_Position = projection * view * model * vec4(position, 1.0);
    // Pass some variables to the fragment shader
    fragTexCoord = texture;
    fragNormal =  normal;
    fragVert = position;
    fragPosLight = depthMVP * vec4(currentPos, 1.0f);
}
