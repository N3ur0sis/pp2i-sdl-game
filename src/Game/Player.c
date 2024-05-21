#include <Player.h>


void playerMovement(Entity* player, float deltaTime, Camera* camera, Model* enemy){

	if (getKeyState(SHIFT)) {
		((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY))->speed = 8.0f;
	} else {
		((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY))->speed = 5.0f;
	}


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
	vec3 rotationDirection;
	vec3 enemyDir;
    glm_vec3_sub(enemy->position,((Model*)getComponent(player, COMPONENT_RENDERABLE))->position,  enemyDir);
    float enemyDist = glm_vec3_norm(enemyDir);
	        glm_vec3_normalize(enemyDir);
	if( enemyDist < 10.0f){
		glm_vec3_copy(enemyDir, rotationDirection);
	}else{
		glm_vec3_copy(movementDirection, rotationDirection);

	}
	if(movementDirection[0] != .0f || movementDirection[1] != .0f || movementDirection[2] != .0f){
	float omega = acos(glm_dot((vec3){0,0,1},rotationDirection));
	if (rotationDirection[0] < 0) {
		omega = -omega;
	}
	float currentAngleDeg = glm_deg(((Model*)getComponent(player, COMPONENT_RENDERABLE))->rotation[1]);
    float targetAngleDeg = glm_deg(omega);

    // Ensure the that the fucking target angle is within the range of -180 to 180 degrees (i spent three fucking hours just to realize the angles wasn't normalized , fuck me!)
    while (targetAngleDeg - currentAngleDeg > 180) {
        targetAngleDeg -= 360;
    }
    while (targetAngleDeg - currentAngleDeg < -180) {
        targetAngleDeg += 360;
    }

    // Perform linear interpolation²
    float rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);

    //printf("%f\n", rotTarget);
	glm_vec3_scale(movementDirection,((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY))->speed*deltaTime,movementDirection);
    vec3 newPos;
	glm_vec3_add(((Model*)getComponent(player, COMPONENT_RENDERABLE))->position,movementDirection,newPos);
	((Model*)getComponent(player, COMPONENT_RENDERABLE))->rotation[1] = glm_rad(rotTarget);

	moveCameraPlayer(camera, ((Model*)getComponent(player, COMPONENT_RENDERABLE))->position,newPos, deltaTime);
	glm_vec3_copy(newPos, ((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY))->velocity);
	mat4 id;
    glm_translate_make(id,((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY))->velocity);
    glm_aabb_transform(((Collider*)getComponent(player, COMPONENT_COLLIDER))->boundingBoxReference,id,((Collider*)getComponent(player, COMPONENT_COLLIDER))->boundingBox);
	}
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


void lerp_vec3(vec3 a, vec3 b, vec3 res, float t){
    res[0] = a[0] + (b[0] - a[0]) * t;
    res[1] = a[1] + (b[1] - a[1]) * t;
    res[2] = a[2] + (b[2] - a[2]) * t;
}

float lerp_float(float a, float b, float t) {
    return a + (b - a) * t;
}

bool playerInteract(){
	return getKeyState(SDLK_e);
}

Entity* create_player(Scene*  scene,float x,float y,float z){
	Entity* playerEntity = createEntity(scene);
    if (playerEntity != NULL) {
        Model* playerModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(playerModel, "assets/models/LoPotitChat/PlayerWalk.dae");
        Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerAttack.dae", playerModel, "playerAttackAnimation");
        Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerWalk.dae", playerModel, "playerWalkingAnimation");
        Animator* playerAnimator = AnimatorCreate(walkingAnimation);
        glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, playerModel->scale);
        RigidBody* playerRigidBody = (RigidBody*)calloc(1,sizeof(RigidBody));
        glm_vec3_copy((vec3){x, y, z}, playerRigidBody->velocity);
        playerRigidBody->speed = .0f;
        Collider* playerCollider = ColliderCreate("assets/models/LoPotitChat/PlayerWalk.dae");
        glm_scale_make(playerCollider->transformMatrix, (vec3){0.5f, 0.5f, 0.5f});
        UpdateCollider(playerCollider);

        addComponent(playerEntity, COMPONENT_RENDERABLE, playerModel);
        addComponent(playerEntity, COMPONENT_ANIMATION, attackAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, walkingAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATOR, playerAnimator);
        addComponent(playerEntity, COMPONENT_COLLIDER, playerCollider);
        addComponent(playerEntity, COMPONENT_RIGIDBODY, playerRigidBody);
    }
	return playerEntity;
}

