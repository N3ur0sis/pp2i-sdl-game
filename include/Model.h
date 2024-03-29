#pragma once
#include <SDL2/SDL.h>
#include <Mesh.h>
#include <Shader.h>
#include <Camera.h>
#include <Textures.h>



/* A Model class to represent a 3D object in the scene */
typedef struct _Model{
    Mesh*    meshes;        /* Arrays of meshes forming the model */
    Texture* materials;     /* Arrays of materials used by meshes */
    size_t   meshCount;     /* Number of meshes within the model  */
    size_t   matCount;      /* Nmmber of materials in the model   */
    char*    directory;     /* Path to the folder of the model    */
    vec3     position;      /* Position of the model in the scene */
    vec3     rotation;      /* Rotation of the model in the scene */
    vec3     scale;         /* Scale of the model in the scene    */
} Model;


/**
 * Import a model from a file using assimp library.
 * Flags for importation can be configured.  
 * 
 * @param path Relative path of the model from the executable file
 * @return A scene struct that contains all the data of the model
 * in the format of assimp
*/
const struct aiScene* ModelLoad(char* path);

/**
 * Organize the assimp model data format to a format usable by OpenGL.
 * Calls the ModelLoad function to load the data from the file, calls MeshCreate
 * to convert each Mesh data and load them to GL buffers and process every material found
 * 
 * @param path Relative path of the model from the executable file.
 * @return A Model struct in usable format for OpenGL.
 * @note Animation should be load here as well as other texture type like Specular or Normal.
*/
void ModelCreate(Model* model, char* path);

/**
 * Render the Model with DrawElement using VAO and EBO. 
 * Calculate a Model Matrix and link it to the shader.
 * 
 * @param model A model the we want to draw.
 * @param shader The shader we want to give the Model Matrix to.
 * @param camera The camera that will show the model.
 * @return Nothing, act on the render pipeline.
*/
void ModelDraw(Model* model, Shader* shader, Camera* camera);

/**
 * Auxiliar function of the rendering process. It calculates based on a positon
 * rotation and scale vector a transformation matrix to "move" our model vefore rendering.
 * 
 * @param position The target position of the model
 * @param rotation The target rotation of the model
 * @param scale    The target scale of the model
 * @return Nothing, act on the shaders.
 * @note The Projection and View matrices should not be send from here since it does not nessecary change on every frame.
 * 
*/
void ModelMatrixCalculate(vec3 position,vec3 rotation, vec3 scale , Camera* camera, Shader* sahder);


void ModelFree(Model* model);