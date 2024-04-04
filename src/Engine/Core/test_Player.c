#include <stdio.h>
#include <assert.h>
#include "Player.h"

void testMoveCameraPlayer() {
    Camera camera;
    vec3 position = {0.0f, 0.0f, 0.0f};
    vec3 targetPosition = {10.0f, 10.0f, 10.0f};
    float deltaTime = 0.1f;

    // Test case 1: position[0] < -25.0f
    position[0] = -30.0f;
    moveCameraPlayer(&camera, position, targetPosition, deltaTime);
    assert(camera.Yaw == 180.0f);
    assert(camera.Position[0] == -5.0f);
    assert(camera.Position[1] == 25.0f);
    assert(camera.Position[2] == 10.0f);

    // Test case 2: position[0] >= -25.0f
    position[0] = 0.0f;
    moveCameraPlayer(&camera, position, targetPosition, deltaTime);
    assert(camera.Yaw == 90.0f);
    assert(camera.Position[0] == 0.0f);
    assert(camera.Position[1] == 25.0f);
    assert(camera.Position[2] == -15.0f);

    printf("All tests passed!\n");
}

int main(void) {
    testMoveCameraPlayer();

    return 0;
}