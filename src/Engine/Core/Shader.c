#include <Shader.h>

char* get_shader_content(const char* fileName)
{
    FILE *fp;
    long size = 0;
    char* shaderContent;
    
    /* Read File to get size */
    fp = fopen(fileName, "rb");
    if(fp == NULL) {
        printf("Error: Could not open file %s\n", fileName);
        return "";
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fclose(fp);

    /* Read File for Content */
    fp = fopen(fileName, "r");
    shaderContent = memset(malloc(size), '\0', size);
    fread(shaderContent, 1, size-1, fp);
    fclose(fp);
    return shaderContent;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

 // Create the shaders
 GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
 GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

 //Read the vertex shader code from the file
 char* VertexShaderCode = get_shader_content(fragment_file_path);
 printf("VertexShaderCode: %s", VertexShaderCode);

 // Read the Fragment Shader code from the file
 char* FragmentShaderCode = get_shader_content(fragment_file_path);

 GLint Result = GL_FALSE;
 int InfoLogLength;

 // Compile Vertex Shader
 printf("Compiling shader : %s\n", vertex_file_path);
 char const * VertexSourcePointer = VertexShaderCode;
 glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
 glCompileShader(VertexShaderID);
 // Check Vertex Shader
 glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
 glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

 // Compile Fragment Shader
 printf("Compiling shader : %s\n", fragment_file_path);
 char const * FragmentSourcePointer = FragmentShaderCode;
 glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
 glCompileShader(FragmentShaderID);

 // Check Fragment Shader
 glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
 glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

 // Link the program
 printf("Linking program\n");
 GLuint ProgramID = glCreateProgram();
 glAttachShader(ProgramID, VertexShaderID);
 glAttachShader(ProgramID, FragmentShaderID);
 glLinkProgram(ProgramID);

 // Check the program
 glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
 glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

 glDetachShader(ProgramID, VertexShaderID);
 glDetachShader(ProgramID, FragmentShaderID);

 glDeleteShader(VertexShaderID);
 glDeleteShader(FragmentShaderID);

 return ProgramID;
}
