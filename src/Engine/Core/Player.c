#include <Player.h>



void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera){

	vec3 front;
	vec3 right;

	glm_vec3_copy(camera->Front, front);
	glm_vec3_copy(camera->Right, right);

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
	float turningSpeed = 8.0f * deltaTime;
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
			x +=  front[0] * realSpeedDiag + right[0] * realSpeedDiag;
        	z += front[2] * realSpeedDiag + right[2] * realSpeedDiag;
		}
		else{
			x +=  front[0] * speedDiag + right[0] * speedDiag;
        	z += front[2] * speedDiag + right[2] * speedDiag;
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
			x -=  front[0] * realSpeedDiag + right[0] * realSpeedDiag;
        	z -= front[2] * realSpeedDiag + right[2] * realSpeedDiag;
		}
		else{
			x -=  front[0] * speedDiag + right[0] * speedDiag;
        	z -= front[2] * speedDiag + right[2] * speedDiag;
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
			x +=  front[0] * realSpeedDiag - right[0] * realSpeedDiag;
        	z += front[2] * realSpeedDiag - right[2] * realSpeedDiag;
		}
		else{
			x +=  front[0] * speedDiag - right[0] * speedDiag;
        	z += front[2] * speedDiag - right[2] * speedDiag;
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
			x -=  front[0] * realSpeedDiag - right[0] * realSpeedDiag;
        	z -= front[2] * realSpeedDiag - right[2] * realSpeedDiag;
		}
		else{
			x -=  front[0] * speedDiag - right[0] * speedDiag;
        	z -= front[2] * speedDiag - right[2] * speedDiag;
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
			x += front[0] * realSpeed;
        	z += front[2] * realSpeed;
		}
		else{
			x += front[0] * speed;
        	z += front[2] * speed;
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
			x -= front[0] * realSpeed;
        	z -= front[2] * realSpeed;
		}
		else{
			x -= front[0] * speed;
        	z -= front[2] * speed;
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
            x -= right[0] * realSpeed;
        	z -= right[2] * realSpeed;
        }
        else{
            x -= right[0] * speed;
        	z -= right[2] * speed;
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
            x += right[0] * realSpeed;
        	z += right[2] * realSpeed;
        }
        else{
            x += right[0] * speed;
        	z += right[2] * speed;
        }   
    }
	moveCameraPlayer(camera, (vec3){x, y, z}, deltaTime);
    // Calcul de la différence d'angle entre la rotation actuelle et la rotation souhaitée
	

    position[0] = x;
    position[1] = y;
    position[2] = z;
    rotation[0] = xRot;
    rotation[1] = yRot;
    rotation[2] = zRot;
}



void moveCameraPlayer(Camera* camera, vec3 position, float deltaTime) {
	if (position[0] < -25.0f) {
		if (camera->Yaw != 180.0f) {
			camera->Yaw = 180.0f;
		}

		// vec3 old_camera_vect;
		// vec3 new_camera_vect;
		// glm_vec3_copy(camera->Position, old_camera_vect);
		// glm_vec3_copy(camera->Position, new_camera_vect);
		// new_camera_vect[0] = position[0] + 25.0f;
		// new_camera_vect[1] = position[1] + 25.0f;
		// new_camera_vect[2] = position[2];
		deltaTime ++;
		// changeCameraSmoothly(camera, old_camera_vect, new_camera_vect, 1.0f, deltaTime);

		camera->Position[0] = position[0] + 25.0f;
		camera->Position[1] = position[1] + 25.0f;
		camera->Position[2] = position[2];
	} else {
		if (camera->Yaw != 90.0f) {
			camera->Yaw = 90.0f;
		}
		camera->Position[0] = position[0];
		camera->Position[1] = position[1] + 25.0f;
		camera->Position[2] = position[2] - 25.0f;
	}
	updateCameraVectors(camera);
}


// void changeCameraSmoothly(Camera* camera, vec3 old_camera, vec3 new_camera, float transitionTime, float deltaTime) {
// 	float elapsedTime = 0.0f;


//     vec3 direction = new_camera - old_camera;
// 	glm_normalize(direction);

//     // float distance = glm_distance(old_camera, new_camera);

    
//     while (elapsedTime < transitionTime) {
//         float t = elapsedTime / transitionTime;

//         vec3 newPosition = glm_mix(old_camera, new_camera, t);
// 		glm_vec3_copy(newPosition, old_camera);

//         updateCameraVectors(camera);


//         elapsedTime += deltaTime;
//     }

// 	old_camera[0] = new_camera[0];
// 	old_camera[1] = new_camera[1];
// 	old_camera[2] = new_camera[2];
// }