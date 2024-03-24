#include <Shader.h>

Shader* LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    
    Shader *shader = (Shader*)malloc(sizeof(Shader));

    //Read Shader Content
    const char *vertexShaderSource = get_shader_content(vertex_file_path);
    const char *fragmentShaderSource = get_shader_content(fragment_file_path);

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint vertexShaderStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderStatus);
    if (vertexShaderStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        if (maxLength > 1) {
            GLchar *infoLog = (GLchar *)malloc(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);
            printf("Vertex shader compilation log:\n%s\n", infoLog);
            free(infoLog);
        }
        // Handle compilation error
        glDeleteShader(vertexShader);
        return 0;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLint fragmentShaderStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderStatus);
    if (fragmentShaderStatus == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        if (maxLength > 1) {
            GLchar *infoLog = (GLchar *)malloc(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);
            printf("Fragment shader compilation log:\n%s\n", infoLog);
            free(infoLog);
        }
        // Handle compilation error
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    // Link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    shader->m_program = shaderProgram;

    //Cleanup  shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free((void*)vertexShaderSource);
    free((void*)fragmentShaderSource);



    //Setting shader locations
    shader->m_locations.Model = glGetUniformLocation(shaderProgram, "model");
    shader->m_locations.View = glGetUniformLocation(shaderProgram, "view");
    shader->m_locations.Projection = glGetUniformLocation(shaderProgram, "projection");    
	shader->m_locations.ambientLightColor = glGetUniformLocation(shaderProgram, "ambientLightColor");
	shader->m_locations.ambientLightIntensity = glGetUniformLocation(shaderProgram, "ambientLightIntensity");
	shader->m_locations.pointLightColor = glGetUniformLocation(shaderProgram, "pointLightColor");
	shader->m_locations.pointLightPosition = glGetUniformLocation(shaderProgram, "pointLightPosition");
	shader->m_locations.pointLightIntensity = glGetUniformLocation(shaderProgram, "pointLightIntensity");
	shader->m_locations.pointLightAttenuation = glGetUniformLocation(shaderProgram, "pointLightAttenuation");
	shader->m_locations.transformationMatrix = glGetUniformLocation(shaderProgram, "transformationMatrix");
	shader->m_locations.normalTransformationMatrix = glGetUniformLocation(shaderProgram, "normalTransformationMatrix");
    
    return shader;
}


void UseShaders(Shader* shader){
    glUseProgram(shader->m_program);
}

void DeleteShaders(Shader* shader){
    glDeleteProgram(shader->m_program);
    free(shader);
}