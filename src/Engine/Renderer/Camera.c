#include <Camera.h>

bool firstLook = true;
bool firstMove = true;

//Camera constructor
Camera* camera_create(float posX, float posY, float posZ, float width, float height){
    Camera* camera = (Camera*)malloc(sizeof(Camera));
    camera->Position[0] = posX;
    camera->Position[1] = posY;
    camera->Position[2] = posZ;
    camera->WorldUp[0] = 0.0f;
    camera->WorldUp[1] = 0.1f;
    camera->WorldUp[2] = 0.0f;
    camera->Yaw = 90.0f;
    camera->Pitch = -50.0f;
    camera->MouseSensitivity = 0.1f;
    camera->MovementSpeed = 2.5f;
    camera->Zoom = 60.0f;
    updateCameraVectors(camera);
    glm_perspective(glm_rad(60.0f), (float)(width)/(float)height, 0.1f, 500.0f, camera->projectionMatrix);
    return camera;
}


void getViewMatrix(Camera* camera, vec4* view){
    vec3 center;
    glm_vec3_add(camera->Position, camera->Front, center);
    glm_lookat(camera->Position, center , camera->Up, view);
}


void updateCameraVectors(Camera* camera){
        // calculate the new Front vector
        vec3 front;
        front[0] = cos(glm_rad(camera->Yaw)) * cos(glm_rad(camera->Pitch));
        front[1] = sin(glm_rad(camera->Pitch));
        front[2] = sin(glm_rad(camera->Yaw)) * cos(glm_rad(camera->Pitch));
        glm_normalize(front);
        camera->Front[0] = front[0];
        camera->Front[1] = front[1];
        camera->Front[2] =front[2];

        // also re-calculate the Right and Up vector
        glm_cross(camera->Front, camera->WorldUp,camera->Right);
        glm_normalize(camera->Right);  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        glm_cross(camera->Right, camera->Front, camera->Up);
        glm_normalize(camera->Up);

        glm_mat4_identity(camera->viewMatrix);
        getViewMatrix(camera, camera->viewMatrix);

}

void cameraControl(Camera* camera, GameState* gameState){
    glm_perspective(glm_rad(60.0f), (float)(gameState->g_WindowWidth)/(float)gameState->g_WindowHeight, 0.1f, 500.0f, camera->projectionMatrix);  
    //Tilt camere
    if(getMouseButtonState(SDL_BUTTON_RIGHT) == true){
        float xpos = getMousePosition(0);
        float ypos = getMousePosition(1);
        if (firstLook)
        {
            setMousePosition(2, xpos);
            setMousePosition(3, ypos);
            firstLook = false;
        }
        float xoffset = xpos - getMousePosition(2);
        float yoffset = getMousePosition(3) - ypos; // reversed since y-coordinates go from bottom to top
        setMousePosition(2, xpos);
        setMousePosition(3, ypos);
        xoffset *= camera->MouseSensitivity;
        yoffset *= camera->MouseSensitivity;
        camera->Yaw   += xoffset;
        camera->Pitch += yoffset;
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (true)
        {
            if (camera->Pitch > 89.0f)
                camera->Pitch = 89.0f;
            if (camera->Pitch < -89.0f)
                camera->Pitch = -89.0f;
        }
                // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors(camera);
    }else{
        firstLook = true;
    }
    //Pan camera
    if(getMouseButtonState(SDL_BUTTON_MIDDLE) == SDL_PRESSED){
            float xpos = getMousePosition(0);
            float ypos = getMousePosition(1);

            if (firstMove)
            {
                setMousePosition(2, xpos);
                setMousePosition(3, ypos);
                firstMove = false;
            }
            float xoffset = xpos - getMousePosition(2);
            float yoffset = getMousePosition(3) - ypos; // reversed since y-coordinates go from bottom to top

            setMousePosition(2, xpos);
            setMousePosition(3, ypos);
            vec3 velocityY;
            glm_vec3_scale(camera->Up, yoffset*0.01f, velocityY);
            glm_vec3_sub(camera->Position, velocityY, camera->Position);
            vec3 velocityX;
            glm_vec3_scale(camera->Right, xoffset*0.01f, velocityX);
            glm_vec3_sub(camera->Position, velocityX, camera->Position);
            updateCameraVectors(camera);
    }else{
            setMousePosition(2, getMousePosition(0));
            setMousePosition(3, getMousePosition(1));
    }
    //Zoom Camera
    float zpos = getMousePosition(4);
    float zoffset = zpos - getMousePosition(5);
    setMousePosition(5, zpos);
    vec3 velocityZ;
    glm_vec3_scale(camera->Front, zoffset*1.5f, velocityZ);
    glm_vec3_add(camera->Position, velocityZ, camera->Position);
    updateCameraVectors(camera);
}