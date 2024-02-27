#include <Camera.h>

Camera* camera_create(float posX, float posY, float posZ, float width, float height){
    Camera* camera = (Camera*)malloc(sizeof(Camera));
    camera->Position[0] = posX;
    camera->Position[1] = posY;
    camera->Position[2] = posZ;
    camera->WorldUp[0] = 0.0f;
    camera->WorldUp[1] = 0.1f;
    camera->WorldUp[2] = 0.0f;
    camera->Yaw = -90.0f;
    camera->Pitch = 0.0f;
    camera->MouseSensitivity = 0.2f;
    camera->MovementSpeed = 2.5f;
    camera->Zoom = 45.0f;
    updateCameraVectors(camera);
    glm_perspective(glm_rad(60.0f), (float)(width)/(float)height, 0.1f, 100.0f, camera->projectionMatrix);
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

void panCamera(Camera* camera, float xrel, float yrel){
        xrel *= camera->MouseSensitivity;
        yrel *= camera->MouseSensitivity;
        camera->Yaw   += xrel;
        camera->Pitch -= yrel;

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
}

void ProcessKeyboard(Camera* camera, Camera_Movement direction, float deltaTime)
{
    (void)deltaTime;
    float velocity = camera->MovementSpeed * 0.03f;
    if (direction == FORWARD){
        vec3 temp;
        glm_vec3_scale(camera->Front, velocity, temp);
        glm_vec3_add(camera->Position, temp, camera->Position);
    }
        if (direction == BACKWARD){
        vec3 temp;
        glm_vec3_scale(camera->Front, velocity, temp);
        glm_vec3_sub(camera->Position, temp, camera->Position);
    }
        if (direction == LEFT){
        vec3 temp;
        glm_vec3_scale(camera->Right, velocity, temp);
        glm_vec3_sub(camera->Position, temp, camera->Position);
    }
        if (direction == RIGHT){
        vec3 temp;
        glm_vec3_scale(camera->Right, velocity, temp);
        glm_vec3_add(camera->Position, temp, camera->Position);
    }


    updateCameraVectors(camera);
}