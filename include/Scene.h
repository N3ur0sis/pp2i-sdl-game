#pragma once
#include <Model.h>

typedef void (*LoadScene)(); 
typedef void (*UnloadScene)(); 
typedef void (*UpdateScene)(); 
typedef void (*RenderScene)(); 


typedef struct _Scene{
    /* Scene's Data Memeber*/
    Model modelComponents[10];
    int entities;
    /* Scene's Member Methods */
    LoadScene loadScene;
    UnloadScene unloadScene;
    UpdateScene updateScene;
    RenderScene renderScene;
} Scene;

