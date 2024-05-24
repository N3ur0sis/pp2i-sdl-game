#include <Component.h>

void FreeAttachementComponent(AttachmentComponent* AttachmentComponent){
    if (AttachmentComponent){
    //ModelFree(AttachmentComponent->parentModel);
    //FreeAnimator(AttachmentComponent->parentAnimator);
    free(AttachmentComponent);
    }
}

void FreeRigidBody(RigidBody* rb){
    free(rb);
}