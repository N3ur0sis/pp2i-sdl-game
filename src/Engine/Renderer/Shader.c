#include <Shader.h>
#include "ReadShader.h"


Shader* LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    const char *vertexShaderSource = get_shader_content(vertex_file_path);
    const char *fragmentShaderSource = get_shader_content(fragment_file_path);
    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Shader *shader = (Shader*)malloc(sizeof(Shader));
    shader->program = shaderProgram;
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    GLuint modelLoc = glGetUniformLocation(shader->program, "model");
    shader->locations.Model = modelLoc;
    shader->locations.View = viewLoc;
    shader->locations.Projection = projectionLoc;
    
    return shader;
}

void useShaders(GLuint program){
    glUseProgram(program);
}
