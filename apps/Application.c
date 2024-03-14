#include <Engine.h>


//GLOBAL VARIABLES
static const int WIDTH = 1280;
static const int HEIGHT = 720;
static const char*  title = "Game";


//Entry Point of the Game
int main(void){

    //Initialize SDL and Create window
    SDL_Window* window = window_create(WIDTH, HEIGHT, title);
    //Initialize OpenGL and create ViewPort
    engine_start(WIDTH, HEIGHT);
    //Load and Compile Shaders into OpenGL
    Shader* shader = LoadShaders("../assets/shaders/default.vs", "../assets/shaders/default.fs");
    useShaders(shader->program);
    //Create and Initialize scene Camera
    Camera* camera = camera_create(0.0f, 1.0f, 5.0f, WIDTH, HEIGHT);
    //Initialize Engine Components
    Time* time = (Time*)malloc(sizeof(Time));
    SDL_Event e;


    /***************DEMONSTRATION SCENE*****************/
    //Load a model
    Obj obj = loadObj("../assets/models/table.obj");
    Mesh* cube = mesh_create(obj.vertices, obj.uvs, obj.normals, (GLuint*)obj.indices, obj.numVertices, obj.numIndices);
    load_textures(cube,"../assets/images/table.png");
    
    //Creating scene light
    
	vec3 color = {1.0f, 1.0f, 1.0f};
	light_setAmbientLight(shader, color, 0.2f);
    vec3 pointColor = {1.0f, 1.0f, 1.0f};
    vec3 pointPosition = {10.0f, 5.0f, -2.0f};
	pointLight *point = light_createPointLight(shader, pointColor, pointPosition, 5.0f, 0.6f);
    /***************************************************/



    //Game Loop
    bool done = false;
    time->lastUpdate = SDL_GetTicks();
    while(!done) {

        //Per-frame time logic
        time->currentUpdate = SDL_GetTicks();
        time->deltaTime = (time->currentUpdate - time->lastUpdate) / 1000.0f;

        //Input Handling
        while(SDL_PollEvent(&e)){
            processInput(&e, &done);
        }
        //Game Logic
        //...

        //Rendering
		//point->position[0] = 5*sinf(time->deltaTime);
        light_updatePointLight(shader, point);
        cameraControl(camera);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        mesh_draw(cube, shader, camera, time);
        //mesh_draw(rectangle, shader, camera, time);
        SDL_GL_SwapWindow(window);
    }

    //CleanUp
    free(cube);
    free(camera);
    free(shader);
    SDL_DestroyWindow(window);
    engine_quit();
}
