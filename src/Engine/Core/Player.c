#include <Player.h>



void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera){
    float speed = 6.0f * deltaTime;
    float speedDiag = speed / sqrt(2);

    float realSpeed = 8.0f * deltaTime;
    float realSpeedDiag = realSpeed / sqrt(2);


    float x = position[0];
    float y = position[1];
    float z = position[2];
    float xRot = rotation[0];
    float yRot = rotation[1];
    float zRot = rotation[2];

	if (yRot > 2 * PI) {
		yRot -= 2 * PI;
	}
	else if (yRot < 0) {
		yRot += 2 * PI;
	}
	float turningSpeed = 0.0075;
	// printf("yRot: %f\n", yRot);


	if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_d))) {
		if (yRot != 1.75 * PI) {
			if ((yRot >= 0.75 * PI) && (yRot < 1.75 * PI)) {
				yRot += turningSpeed;
			}
			else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z += realSpeedDiag;
			x -= realSpeedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z += speedDiag;
			x -= speedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_q))) {
		if (yRot != 0.75 * PI) {
			if (!((yRot > 0.75 * PI) && (yRot <= 1.75 * PI))) {
				yRot += turningSpeed;
			} else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z -= realSpeedDiag;
			x += realSpeedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z -= speedDiag;
			x += speedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
	else if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_q))) {
		if (yRot != 0.25 * PI) {
			if (!((yRot > 0.25 * PI) && (yRot <= 1.25 * PI))) {
				yRot += turningSpeed;
			}
			else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z += realSpeedDiag;
			x += realSpeedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z += speedDiag;
			x += speedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_d))) {
		if (yRot != 1.25 * PI) {
			if ((yRot >= 0.25 * PI) && (yRot < 1.25 * PI)) {
				yRot += turningSpeed;
			}
			else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z -= realSpeedDiag;
			x -= realSpeedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z -= speedDiag;
			x -= speedDiag;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
    else if (getKeyState(SDLK_z)) {
		if (yRot != 0.0f) {
			if (yRot > PI) {
				yRot += turningSpeed;
			}
			else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z += realSpeed;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z += speed;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
	else if (getKeyState(SDLK_s)) {
		if (yRot != PI) {
			if (yRot < PI) {
				yRot += turningSpeed;
			} else {
				yRot += -turningSpeed;
			}
		}
		if (getKeyState(SHIFT)){
			z -= realSpeed;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
		else{
			z -= speed;
			moveCameraPlayer(camera, (vec3){x, y, z});
		}
	}
	else if (getKeyState(SDLK_q)) {
        if (yRot != 0.5 * PI) {
			if (!((yRot > 0.5 * PI) && (yRot <= 1.5 * PI))) {
				yRot += turningSpeed;
			} else {
				yRot += -turningSpeed;
			}
		}
        if (getKeyState(SHIFT)){
            x += realSpeed;
			moveCameraPlayer(camera, (vec3){x, y, z});
        }
        else{
            x += speed;
			moveCameraPlayer(camera, (vec3){x, y, z});
        }
    }
    else if (getKeyState(SDLK_d)) {
        if (yRot != 0.5 * PI) {
			if (((yRot > 0.5 * PI) && (yRot <= 1.5 * PI))) {
				yRot += turningSpeed;
			} else {
				yRot += -turningSpeed;
			}
		}
        if (getKeyState(SHIFT)){
            x -= realSpeed;
			moveCameraPlayer(camera, (vec3){x, y, z});
        }
        else{
            x -= speed;
			moveCameraPlayer(camera, (vec3){x, y, z});
        }   
    }

    // Calcul de la différence d'angle entre la rotation actuelle et la rotation souhaitée
	

    position[0] = x;
    position[1] = y;
    position[2] = z;
    rotation[0] = xRot;
    rotation[1] = yRot;
    rotation[2] = zRot;
}



void moveCameraPlayer(Camera* camera, vec3 position) {
	camera->Position[0] = position[0];
	camera->Position[1] = position[1] + 7.5f;
	camera->Position[2] = position[2] - 7.5f;
	updateCameraVectors(camera);
}