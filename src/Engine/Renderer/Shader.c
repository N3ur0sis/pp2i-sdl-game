#include <Shader.h>
#include <ReadShader.h>


Shader* LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

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
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    shader->locations.Model = modelLoc;
    shader->locations.View = viewLoc;
    shader->locations.Projection = projectionLoc;
    
	shader->locations.ambientLightColor = glGetUniformLocation(shaderProgram, "ambientLightColor");
	shader->locations.ambientLightIntensity = glGetUniformLocation(shaderProgram, "ambientLightIntensity");
	shader->locations.pointLightColor = glGetUniformLocation(shaderProgram, "pointLightColor");
	shader->locations.pointLightPosition = glGetUniformLocation(shaderProgram, "pointLightPosition");
	shader->locations.pointLightIntensity = glGetUniformLocation(shaderProgram, "pointLightIntensity");
	shader->locations.pointLightAttenuation = glGetUniformLocation(shaderProgram, "pointLightAttenuation");
	shader->locations.transformationMatrix = glGetUniformLocation(shaderProgram, "transformationMatrix");
	shader->locations.normalTransformationMatrix = glGetUniformLocation(shaderProgram, "normalTransformationMatrix");
    
    return shader;
}

void useShaders(GLuint program){
    glUseProgram(program);
}
