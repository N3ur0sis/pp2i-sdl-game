#pragma once
#include <cglm/cglm.h>
#include <cglm/call.h>

typedef enum  {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
}Camera_Movement;

typedef struct{
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    mat4 viewMatrix;
    mat4 projectionMatrix;
} Camera;

Camera* camera_create(float posX, float posY, float posZ, float width, float height);
void getViewMatrix(Camera* camera, vec4* view);
void updateCameraVectors(Camera* camera );
void panCamera(Camera* camera,float xrel, float yrel);
void ProcessKeyboard(Camera* camera, Camera_Movement direction, float deltaTime);
