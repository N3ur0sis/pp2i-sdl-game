#include <Renderer.h>

void RenderText(const char* message, SDL_Color color, int x, int y, int size, int windowWidth, int windowHeight, GLuint shaderProgram) {

    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", size);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* sFont = TTF_RenderText_Blended(font, message, color);
    if (!sFont) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    glPixelStorei(GL_UNPACK_ROW_LENGTH, sFont->pitch / sFont->format->BytesPerPixel);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLfloat vertices[6][4] = {
        { x - sFont->w / 2, y + sFont->h / 2, 0.0f, 0.0f },
        { x - sFont->w / 2, y - sFont->h / 2, 0.0f, 1.0f },
        { x + sFont->w/2, y - sFont->h / 2, 1.0f, 1.0f },

        { x - sFont->w / 2, y + sFont->h / 2, 0.0f, 0.0f },
        { x + sFont->w/2, y - sFont->h / 2, 1.0f, 1.0f },
        { x + sFont->w/2, y + sFont->h / 2, 1.0f, 0.0f }
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);

    mat4 projection;
    glm_ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f, projection);
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "textTexture"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    TTF_CloseFont(font);
    SDL_FreeSurface(sFont);
}

void RenderImage(const char* path, int x, int y, int windowWidth, int windowHeight, GLuint shaderProgram) {

    SDL_Surface* sFont = IMG_Load(path);


    glPixelStorei(GL_UNPACK_ROW_LENGTH, sFont->pitch / sFont->format->BytesPerPixel);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sFont->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLfloat vertices[6][4] = {
        { x - sFont->w / 2, y + sFont->h, 0.0f, 0.0f },
        { x - sFont->w / 2, y, 0.0f, 1.0f },
        { x + sFont->w/2, y, 1.0f, 1.0f },

        { x - sFont->w / 2, y + sFont->h, 0.0f, 0.0f },
        { x + sFont->w/2, y, 1.0f, 1.0f },
        { x + sFont->w/2, y + sFont->h, 1.0f, 0.0f }
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);

    mat4 projection;
    glm_ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f, projection);
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "textTexture"), 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    SDL_FreeSurface(sFont);
}