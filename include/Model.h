/**
 * @file Model.h
 * @brief Header file for the model component.
*/

#pragma once
#include <SDL2/SDL.h>
#include <Mesh.h>
#include <Shader.h>
#include <Camera.h>
#include <Textures.h>
#include <Algebra.h>

/**
 * @brief Struct representing a node.
*/
typedef struct _Node {
    char name[256];                     /**< Name of the node */
    struct _Node* children[MAX_BONES];  /**< Array of children nodes */
    vec3* pos_keys;                     /**< Array of position keys */
    versor* rot_keys;                   /**< Array of rotation keys */
    vec3* sca_keys;                     /**< Array of scale keys */
    float* pos_key_times;               /**< Array of position key times */
    float* rot_key_times;               /**< Array of rotation key times */
    float* sca_key_times;               /**< Array of scale key times */
    size_t pos_keys_count;              /**< Number of position keys */
    size_t rot_keys_count;              /**< Number of rotation keys */
    size_t sca_keys_count;              /**< Number of scale keys */
    size_t child_count;                 /**< Number of children nodes */
    int bone_idx;                       /**< Index of the bone */
} Node;


/**
 * @brief A Model class to represent a 3D object in the scene 
*/
typedef struct _Model{
    Mesh*    meshes;        /**< Arrays of meshes forming the model */
    Texture* materials;     /**< Arrays of materials used by meshes */
    size_t   meshCount;     /**< Number of meshes within the model  */
    size_t   matCount;      /**< Nmmber of materials in the model   */
    char*    directory;     /**< Path to the folder of the model    */
    vec3     position;      /**< Position of the model in the scene */
    vec3     rotation;      /**< Rotation of the model in the scene */
    vec3     scale;         /**< Scale of the model in the scene    */
    vec3     center;        /**< Center of the volume of the model  */
    mat4     modelMatrix;   /**< Model Matrix of the model          */
    mat4 bones[MAX_BONES];  /**< Array of bones matrices            */
    char bone_names[MAX_BONES][256];    /**< Array of bone names */
    size_t bone_count;      /**< Number of bones in the model        */
    bool isAnimated;        /**< Boolean flag indicating if the model is animated */
    bool isRenderable;      /**< Boolean flag indicating if the model is renderable */
    bool isBusy;            /**< Boolean flag indicating if the model is busy */
} Model;



/**
 * @brief Import a model from a file using assimp library.
 * Flags for importation can be configured.  
 * 
 * @param path Relative path of the model from the executable file
 * @return A scene struct that contains all the data of the model
 * in the format of assimp
*/
const struct aiScene* ModelLoad(char* path);

/**
 * @brief Organize the assimp model data format to a format usable by OpenGL.
 * Calls the ModelLoad function to load the data from the file, calls MeshCreate
 * to convert each Mesh data and load them to GL buffers and process every material found
 * 
 * @param path Relative path of the model from the executable file.
 * @return A Model struct in usable format for OpenGL.
 * @note Animation should be load here as well as other texture type like Specular or Normal.
*/
void ModelCreate(Model* model, char* path);

/**
 * @brief Render the Model with DrawElement using VAO and EBO. 
 * Calculate a Model Matrix and link it to the shader.
 * 
 * @param model A model the we want to draw.
 * @param shader The shader we want to give the Model Matrix to.
 * @param camera The camera that will show the model.
 * @return Nothing, act on the render pipeline.
*/
void ModelDraw(Model* model, Shader* shader, Camera* camera, mat4 customModelMatrix);

/**
 * @brief Auxiliar function of the rendering process. It calculates based on a positon
 * rotation and scale vector a transformation matrix to "move" our model vefore rendering.
 * 
 * @param position The target position of the model
 * @param rotation The target rotation of the model
 * @param scale    The target scale of the model
 * @return Nothing, act on the shaders.
 * @note The Projection and View matrices should not be send from here since it does not nessecary change on every frame.
 * 
*/
void ModelMatrixCalculate(vec3 position,vec3 rotation, vec3 scale , Camera* camera, Shader* sahder, mat4 modelMatrix);

/**
 * @brief Free the memory allocated for the model object.
 * 
 * @param model A model object to be freed.
*/
void ModelFree(Model* model);

/**
 * @brief Function to animate the model.
 * 
 * This function animates the model.
 * 
 * @param node Pointer to the node.
 * @param anim_time Time of the animation.
 * @param parent_mat Parent matrix.
 * @param bones Array of bones.
 * @param bone_anim_mats Array of bone animation matrices.
*/
void ModelAnimate(Node* node, float anim_time, mat4 parent_mat, mat4* bones,mat4* bone_anim_mats);

void ModelDrawAttached(Model* model, Shader* shader, Camera* camera);

/**
 * @brief Function to compute the center of volume of the model.
 * 
 * This function computes the center of volume of the model.
 * 
 * @param model Pointer to the model.
*/
void compute_center_of_volume(Model* model);