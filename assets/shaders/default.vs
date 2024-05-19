#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 norm;
layout(location = 1) in vec2 tex;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;
	
uniform bool isAnimated; // Flag to determine if the model is animated

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 depthMVP;

const int MAX_BONES = 50;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 bones_mat[MAX_BONES];
	
out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;
out vec4 fragPosLight;

void main() {
    vec3 currentPos;
    currentPos = vec3(model * vec4(pos, 1.0f));
    if (isAnimated) {
        vec4 totalPosition = vec4(0.0f);
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            if(boneIds[i] == -1) 
                continue;
            if(boneIds[i] >=MAX_BONES) 
            {

                totalPosition = vec4(pos,1.0f);
                break;
            }
            vec4 localPosition = bones_mat[boneIds[i]] * vec4(pos,1.0f);
            totalPosition += localPosition * weights[i];
            vec3 localNormal = mat3(bones_mat[boneIds[i]]) * norm;
        }
        mat4 viewModel = view * model;
        gl_Position =  projection * viewModel * totalPosition;
    } else {
        // If not animated, just transform using the model matrix
        gl_Position = projection * view * model * vec4(pos, 1.0);

    }

    
    // Pass some variables to the fragment shader
    fragTexCoord = tex;
    fragNormal =  norm;
    fragVert = pos;
    fragPosLight = depthMVP * vec4(currentPos, 1.0f);
}

