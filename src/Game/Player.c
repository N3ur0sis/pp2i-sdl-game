#include <Player.h>



void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera, vec3 playerbb[2], vec3 playerbbo[2], vec3 treebb[2], Model* map){


    float speed = 6.0f;
	float horizontalInput = 0.0f;
	float verticalInput = .0f;

	if ((getKeyState(SDLK_d))) {
		horizontalInput = -1.0f;
	}
	if (getKeyState(SDLK_q)) {
		horizontalInput = 1.0f;
	}
		
    if (getKeyState(SDLK_z)) {
		verticalInput = 1.0f;
	}
	if (getKeyState(SDLK_s)) {
		verticalInput = -1.0f;
	}
	vec3 xDir;
	glm_vec3_scale(camera->Right,-horizontalInput, xDir);
	vec3 yDir;
	glm_vec3_scale(camera->Front,verticalInput, yDir);
	vec3 movementDirection;
	glm_vec3_add(xDir,yDir,movementDirection);
	movementDirection[1] = 0.0f;
	glm_vec3_normalize(movementDirection);
	//sometimes my genius is almost frithening
	if(movementDirection[0] != .0f || movementDirection[1] != .0f || movementDirection[2] != .0f){
	float omega = acos(glm_dot((vec3){0,0,1},movementDirection));
	if (movementDirection[0] < 0) {
		omega = -omega;
	}
	float currentAngleDeg = glm_deg(rotation[1]);
    float targetAngleDeg = glm_deg(omega);

    // Ensure the that the fucking target angle is within the range of -180 to 180 degrees (i spent three fucking hours just to realize the angles wasn't normalized , fuck me!)
    while (targetAngleDeg - currentAngleDeg > 180) {
        targetAngleDeg -= 360;
    }
    while (targetAngleDeg - currentAngleDeg < -180) {
        targetAngleDeg += 360;
    }

    // Perform linear interpolation
    float rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);

    printf("%f\n", rotTarget);
    rotation[1] = glm_rad(rotTarget);
	printf("%f\n", glm_deg(omega));
	}
	printf("%f,%f,%f\n", movementDirection[0], movementDirection[1], movementDirection[2]);
	//fuck this, because of this shit i didn't prepare anything to eat. Im just gonna order some junk food.  

	glm_vec3_scale(movementDirection,speed*deltaTime,movementDirection);
	glm_vec3_add(position,movementDirection,position);

	moveCameraPlayer(camera, position, (vec3){position[0], position[1], position[2]}, deltaTime);

	mat4 id;
    //glm_translate_make(id,(vec3){x,y,z});
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
	(void)camera;
	(void)rotation;
	(void)treebb;
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