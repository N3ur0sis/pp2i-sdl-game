/**
* @file Camera.h
* @brief Camera header file
*/

#pragma once

#include <cglm/cglm.h>
#include <cglm/call.h>

/**
 * @brief Structure representing a camera.
 * 
 * This structure represents a camera.
*/
typedef struct{
    vec3 Position;          /**< Position of the camera */
    vec3 Front;             /**< Front vector of the camera */
    vec3 Up;                /**< Up vector of the camera */
    vec3 Right;             /**< Right vector of the camera */
    vec3 WorldUp;           /**< World up vector */
    float Yaw;              /**< Yaw of the camera */
    float Pitch;            /**< Pitch of the camera */
    float MovementSpeed;    /**< Movement speed of the camera */
    float MouseSensitivity; /**< Mouse sensitivity of the camera */
    float Zoom;             /**< Zoom of the camera */
    mat4 viewMatrix;        /**< View matrix of the camera */
    mat4 projectionMatrix;  /**< Projection matrix of the camera */
} Camera;

/**
 * @brief Creates a new Camera instance.
 * 
 * @param posX The x position of the camera.
 * @param posY The y position of the camera.
 * @param posZ The z position of the camera.
 * @param width The width of the camera.
 * @param height The height of the camera.
 * @return Pointer to the created Camera instance or NULL on failure.
 */
Camera* camera_create(float posX, float posY, float posZ, float width, float height);

/**
 * @brief Gets the view matrix of the camera.
 * 
 * This function gets the view matrix of the camera.
 * 
 * @param camera The camera to get the view matrix from.
 * @param view The view matrix.
 */
void getViewMatrix(Camera* camera, vec4* view);

/**
 * @brief Updates the camera vectors.
 * 
 * This function updates the camera vectors.
 * 
 * @param camera The camera to update.
 */
void updateCameraVectors(Camera* camera );


void panCamera(Camera* camera);


void cameraControl(Camera* camera);