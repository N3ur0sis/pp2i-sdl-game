#include <Player.h>



void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera, vec3 playerbb[2], vec3 playerbbo[2], vec3 treebb[2], Model* map){

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
	moveCameraPlayer(camera, position, (vec3){x, y, z}, deltaTime);

	mat4 id;
    glm_translate_make(id,(vec3){x,y,z});
    glm_aabb_transform(playerbbo,id,playerbb);

	for (size_t i = 30; i < map->meshCount; i++)
	{
		
		vec3 treebb[2] = {
        {map->meshes[i].aabb.mMin.x,
        map->meshes[i].aabb.mMin.y,
        map->meshes[i].aabb.mMin.z},
        {map->meshes[i].aabb.mMax.x,
        map->meshes[i].aabb.mMax.y,
        map->meshes[i].aabb.mMax.z}
    };
	if(glm_aabb_aabb(playerbb,treebb)){

	}
	}
	
	(void)treebb;

    position[0] = x;
    position[1] = y;
    position[2] = z;
    rotation[0] = xRot;
    rotation[1] = yRot;
    rotation[2] = zRot;
}



void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime) {
	targetPosition++;
	if (position[0] < -25.0f) {
		if (camera->Yaw != 180.0f) {
			float oldYaw = camera->Yaw;
			float newYaw = 180.0f;
			camera->Yaw = glm_lerp(oldYaw, newYaw, deltaTime*3);
			vec3 old_camera;
			glm_vec3_copy(camera->Position, old_camera);
			vec3 new_camera = {position[0]+25.0f, position[1]+25.0f, position[2]};
			vec3 copy;
			glm_vec3_lerp(old_camera, new_camera, deltaTime*2, copy);
			camera->Position[0] = copy[0];
			camera->Position[1] = copy[1];
			camera->Position[2] = copy[2];
		}
		vec3 old_camera;
		glm_vec3_copy(camera->Position, old_camera);
		vec3 new_camera = {position[0]+25.0f, position[1]+25.0f, position[2]};
		vec3 copy;
		glm_vec3_lerp(old_camera, new_camera, deltaTime*2, copy);
		camera->Position[0] = copy[0];
		camera->Position[1] = copy[1];
		camera->Position[2] = copy[2];

		
	} else {
		if (camera->Yaw != 90.0f) {
			float oldYaw = camera->Yaw;	
			float newYaw = 90.0f;
			camera->Yaw = glm_lerp(oldYaw, newYaw, deltaTime*3);
			vec3 old_camera;
			glm_vec3_copy(camera->Position, old_camera);
			vec3 new_camera = {position[0], position[1] + 25.0f, position[2] - 25.0f};
			vec3 copy;
			glm_vec3_lerp(old_camera, new_camera, deltaTime*2, copy);
			camera->Position[0] = copy[0];
			camera->Position[1] = copy[1];
			camera->Position[2] = copy[2];
		}
		vec3 old_camera;
		glm_vec3_copy(camera->Position, old_camera);
		vec3 new_camera = {position[0], position[1] + 25.0f, position[2] - 25.0f};
		vec3 copy;
		glm_vec3_lerp(old_camera, new_camera, deltaTime*2, copy);
		camera->Position[0] = copy[0];
		camera->Position[1] = copy[1];
		camera->Position[2] = copy[2];
	}

	updateCameraVectors(camera);
}


void lerp_vec3(vec3 a, vec3 b, vec3 res, float t) {
    res[0] = a[0] + (b[0] - a[0]) * t;
    res[1] = a[1] + (b[1] - a[1]) * t;
    res[2] = a[2] + (b[2] - a[2]) * t;
}

float lerp_float(float a, float b, float t) {
    return a + (b - a) * t;
}


void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration) {
	duration *= 1000;
    for (int i = 0; i <= steps; ++i) {
        float t = (float)i / steps;
		vec3 interpolated_pos;
        lerp_vec3(old_pos, new_pos, interpolated_pos, t);
        float interpolated_yaw = lerp_float(old_yaw, new_yaw, t);

        camera->Position[0] = interpolated_pos[0];
		camera->Position[1] = interpolated_pos[1];
		camera->Position[2] = interpolated_pos[2];
		camera->Yaw = interpolated_yaw;

		updateCameraVectors(camera);
    }
}