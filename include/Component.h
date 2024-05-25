#pragma once

#include <Animator.h>
#include <Light.h>
#include <Collider.h>

typedef enum {
    COMPONENT_RENDERABLE,
    COMPONENT_ANIMATION,
    COMPONENT_ANIMATOR,
    COMPONENT_COLLIDER,
    COMPONENT_LIGHT,
    COMPONENT_ATTACHMENT,
    COMPONENT_RIGIDBODY,
    COMPONENT_DUNGEON,
    COMPONENT_HEALTH,
    COMPONENT_DAMAGE,
    COMPONENT_ENEMY,
    COMPONENT_PLAYER
} ComponentType;

typedef struct _Component{
    ComponentType type;
    void* data;
} Component;

typedef struct {
    int boneIndex;       // Index of the bone to which the model is attached
    Model* parentModel;
    Animator* parentAnimator;
    vec3 offsetPosition; // Offset position relative to the bone
    vec3 offsetRotation; // Offset rotation relative to the bone
    vec3 offsetScale;    // Offset scale relative to the bone
} AttachmentComponent;

typedef struct {
    vec3 velocity;
    float speed; 
} RigidBody;

void FreeAttachementComponent(AttachmentComponent* AttachmentComponent);
void FreeRigidBody(RigidBody* rb);


typedef struct _PlayerComponent {
    bool isAttacking;
    bool isAlive;
    bool hasWeapon;
    float currentHealth;
    float maxHealth;
    float attackDamage;
    float attackRange;
} PlayerComponent;