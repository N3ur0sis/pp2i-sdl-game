/*
* @file Dungeon.c
* @brief implementation of the Dungeon
*/

#include "Dungeon.h"

/**
 * @brief Create a Dungeon object
 * 
 * This function creates a Dungeon object.
 * 
 * @return Dungeon* The Dungeon object
 */
Dungeon* dj_create(){
    Dungeon *dj = malloc(sizeof(Dungeon)); 
    if (dj == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour Dungeon\n");
        exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));
    dj->nb_rooms = rand() % (NB_ROOM_MAX + 1 - NB_ROOM_MIN) + NB_ROOM_MIN;
    
    dj->rooms = malloc((dj->nb_rooms )  * sizeof(Room));
    if (dj->rooms == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour rooms\n");
        exit(EXIT_FAILURE);
    }
    dj->current_room = 0;
    dj->previous_room = 0;
    dj->direction = 'S';
    dj->previous_direction = 'S';
    dj->change = true;
    dj->hasKey = false;
    dj->nb_enemy = 0;
    dj->quit = false;
    dj->lastRoomChangeTime = 0;

    return dj;
}

/**
 * @brief Initialize the adjacency list
 * 
 * This function initializes the adjacency list of the dungeon.
 * 
 * @param dj The dungeon
 */
void initializeAdjacencyList(Dungeon *dj) {
    dj->adj = malloc(dj->nb_rooms * sizeof(char*));
    if (dj->adj == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la liste d'adjacence\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dj->nb_rooms; i++) {
        dj->adj[i] = malloc((dj->nb_rooms + 1) * sizeof(char)); 
        if (dj->adj[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la liste d'adjacence\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < dj->nb_rooms; j++) {
            dj->adj[i][j] = 'O';
        }
        dj->adj[i][dj->nb_rooms] = '\0'; 
    }
}

/**
 * @brief Free the Dungeon object
 * 
 * This function frees the Dungeon object.
 * 
 * @param dj The Dungeon object
 */
void freeDungeon(Dungeon *dj) {
    if (dj == NULL) {
        return;
    }
    printf("je free\n");
    freeTypeRooms(dj);
    freeAdjacencyList(dj);
    freeRooms(dj);
    free(dj);
}

/**
 * @brief Free the rooms
 * 
 * This function frees the rooms of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void freeRooms(Dungeon* dj){
    for (int i =0;i<dj->nb_rooms;i++){
        freeRoom(&dj->rooms[i]);
    }
    free(dj->rooms);
}

/**
 * @brief Free the type of rooms
 * 
 * This function frees the type of rooms of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void freeTypeRooms(Dungeon* dj){
    if (dj->type_room){
        
    for (int i =0;i<NB_MODEL_SALLE;i++){
        freeLRoom(&dj->type_room[i]);
    }
    free(dj->type_room);
    }
    
}

/**
 * @brief Free the adjacency list
 * 
 * This function frees the adjacency list of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void freeAdjacencyList(Dungeon *dj) {
    if (dj->adj){
        
    for (int i = 0; i < dj->nb_rooms; i++) {
        free(dj->adj[i]);
    }
    free(dj->adj);
    }
}

/**
 * @brief Initialize the dungeon
 * 
 * This function initializes the dungeon.
 * 
 * @param dj The Dungeon object
 */
void initialize(Dungeon *dj){
    initializeAdjacencyList(dj);
    initializeLRooms(dj);
    char *l = "SENW";
    srand(time(NULL));
    int nb_door_init = rand() % (MAX_DOOR - MIN_DOOR) + MIN_DOOR;
    int nb_salle = 1+nb_door_init;
    bool dir_used[4] = {false,false,false,false};
    dir_used[0] = true;
    List *Pile = NULL;
    for (int i =1;i<=nb_door_init;i++){
        int dir;
        do {
            dir = rand() % 4; 
        } while (dir_used[dir]); 
        dj->adj[0][i] = l[dir]; 
        dj->adj[i][0] = l[(dir + 2) % 4]; 
        dir_used[dir] = true; 
        append(&Pile,i); 
    }

    while (len(Pile)+nb_salle<dj->nb_rooms){
        if (Pile ==NULL){
            break;
        }
        int ind = Pile->val;
        List *temp = Pile; 
        Pile = Pile->next;
        free(temp);  
        int nb_door = rand() % (4+1-2 ) + 2;
        if (nb_door==1 && len(Pile)+nb_salle<dj->nb_rooms){
            nb_door++;
        }
        if (nb_door==1){continue;}
        bool dir_used[4] = {false,false,false,false};
        for (int i=0;i<dj->nb_rooms;i++){
            if (dj->adj[ind][i]!='O'){
                for (int j=0;j<4;j++){
                    if (dj->adj[ind][i]==l[j]){
                        dir_used[j]=true;
                    }
                }
            }
        }
        bool flag = true;
        for (int i =nb_salle;i<nb_salle+nb_door-1;i++){
            int dir= rand() % 4;
            do {
                dir = rand() % 4; 
            } while (dir_used[dir]); 
            dj->adj[ind][i] = l[dir]; 
            dj->adj[i][ind] = l[(dir + 2) % 4]; 
            dir_used[dir] = true; 
            if (len(Pile)+i==dj->nb_rooms){
                flag = false;
                nb_salle = i+1;
                break;}
            
            append(&Pile,i);

        }
        if (flag){
        nb_salle+=nb_door-1;
        }
    }
    while (Pile && nb_salle<dj->nb_rooms){
        int ind = Pile->val;
        List *temp = Pile; 
        Pile = Pile->next;
        free(temp); 
        bool dir_used[4] = {false,false,false,false};
        for (int i=0;i<dj->nb_rooms;i++){
            if (dj->adj[ind][i]!='O'){
                for (int j=0;j<4;j++){
                    if (dj->adj[ind][i]==l[j]){
                        dir_used[j]=true;
                    }
                }
            } 
        }
        int dir= rand() % 4;
        do {
            dir = rand() % 4; 
        } while (dir_used[dir]); 
        dj->adj[ind][nb_salle] = l[dir]; 
        dj->adj[nb_salle][ind] = l[(dir + 2) % 4]; 
        if (Pile){nb_salle++;}
    }
    
    free_list(Pile);
}

/**
 * @brief Print the adjacency list
 * 
 * This function prints the adjacency list of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void printAdjList(Dungeon *dj){    
    for (int i =0;i<dj->nb_rooms;i++){
        printf("%s\n",dj->adj[i]);
    }

}

/**
 * @brief Find the maximum of two integers
 * 
 * This function finds the maximum of two integers.
 * 
 * @param a The first integer
 * @param b The second integer
 * @return int The maximum of the two integers
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

void depthFirstSearch(Dungeon *dj, int room, int depth, int *depths, int *visited) {
    visited[room] = 1;
    depths[room] = depth;
    for (int i = 0; i < dj->nb_rooms; i++) {
        if (dj->adj[room][i] == 'O') continue;
        if (!visited[i]) {
            depthFirstSearch(dj, i, depth + 1, depths, visited);
        }
    }
}

/**
 * @brief Find the depth of each room
 * 
 * This function finds the depth of each room in the dungeon.
 * 
 * @param dj The Dungeon object
 * @return int* The depth of each room
 */
int *profondeur(Dungeon *dj) {
    int *depths = (int *)malloc(dj->nb_rooms * sizeof(int));
    int *visited = (int *)calloc(dj->nb_rooms, sizeof(int)); 

    for (int i = 0; i < dj->nb_rooms; i++) {
        if (!visited[i]) {
            depthFirstSearch(dj, i, 0, depths, visited);
        }
    }

    free(visited);
    return depths;
}

/**
 * @brief Print the depth of each room
 * 
 * This function prints the depth of each room in the dungeon.
 * 
 * @param depths The depth of each room
 * @param nb_rooms The number of rooms
 */
void printDepth(int *depths, int nb_rooms) {
    for (int i = 0; i < nb_rooms; i++) {
        printf("Profondeur de la salle %d: %d\n", i, depths[i]);
    }
}

/**
 * @brief Find the maximum of a list of integers
 * 
 * This function finds the maximum of a list of integers.
 * 
 * @param list The list of integers
 * @param size The size of the list
 * @return int The maximum of the list
 */
int maxList(int list[], int size) {
    if (size <= 0) {
        return 0;
    }

    int max = list[0];

    for (int i = 1; i < size; i++) {
        if (list[i] > max) {
            max = list[i];
        }
    }

    return max;
}

/**
 * @brief Initialize the rooms
 * 
 * This function initializes the rooms of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void initializeRooms(Dungeon *dj){
    int * li = profondeur(dj);
    int m = maxList(li,dj->nb_rooms);
    bool hasBossRoom = false;
    for (int i =0;i<dj->nb_rooms;i++){
        int nb = 0 ;
        for (int j = 0;j<dj->nb_rooms;j++){
            if (dj->adj[i][j]!='O'){
                nb++;
        }
        }
        if (i==0){nb++;
            dj->adj[0][0] = 'S';
}
        dj->rooms[i].nb_door = nb;
        dj->rooms[i].type =-1 ;
        dj->rooms[i].isCompleted = false;
        dj->rooms[i].nb_enemy = 0;
        for (int k = 0; k < NB_ENEMY; k++) {
            dj->rooms[i].id_enemy[k] = 0;
        }
        int nb_model;
        int val_model;
        srand(time(NULL));
        char *l = "SENW";
        switch (nb)
        {
        case 1:
            if (li[i]==m&&!hasBossRoom){
                hasBossRoom = true;
                dj->rooms[i].id = 7;//B
                break;
            }
            dj->rooms[i].id = 0;//1C

            break;
        case 2:
            bool dir_used[4] = {false,false,false,false};
            for (int k=0;k<dj->nb_rooms;k++){
                if (dj->adj[i][k]!='O'){
                    for (int j=0;j<4;j++){
                        if (dj->adj[i][k]==l[j]){
                            dir_used[j]=true;
                        }
                    }
                }
            }
            if ((dir_used[0]&&(dir_used[2]))||(dir_used[1]&&(dir_used[3]))){
                nb_model = 2;
            val_model = rand() % (nb_model ) + 1;
            switch (val_model)
            {
            case 1:
                dj->rooms[i].id = 1;//2C
                break;
            case 2:
                dj->rooms[i].id = 2;//2I
                break;
            }      
            }
            else{
                dj->rooms[i].id = 3;//2L
            }
            break;
        case 3:
            nb_model = 2;
            val_model = rand() % (nb_model ) + 1;
            switch (val_model)
            {
            case 1:
                dj->rooms[i].id = 4;//3C
                break;
            case 2:
                dj->rooms[i].id = 5;//3T
                break;
            }
            break;
        case 4:
            dj->rooms[i].id = 6;//4C
            break;
        }
    }
free(li);
}

/**
 * @brief Initialize the rooms
 * 
 * This function initializes the rooms of the dungeon.
 * 
 * @param dj The Dungeon object
 */
void initializeLRooms(Dungeon *dj) {
    dj->type_room = malloc(NB_MODEL_SALLE * sizeof(L_Room));
    for (int i = 0; i < NB_MODEL_SALLE; i++) {
        dj->type_room[i].model = malloc(sizeof(Model));
        dj->type_room[i].col = malloc(sizeof(Collider));
    }
    ModelCreate(dj->type_room[0].model, "assets/models/Room/Room1C.obj");
    dj->type_room[0].col = ColliderCreate("assets/models/Room/ColC.obj");

    ModelCreate(dj->type_room[1].model, "assets/models/Room/Room2C.obj");
    dj->type_room[1].col = ColliderCreate("assets/models/Room/ColC.obj");

    ModelCreate(dj->type_room[4].model, "assets/models/Room/Room3C.obj");
    dj->type_room[4].col = ColliderCreate("assets/models/Room/ColC.obj");

    ModelCreate(dj->type_room[6].model, "assets/models/Room/Room4C.obj");
    dj->type_room[6].col = ColliderCreate("assets/models/Room/ColC.obj");

    ModelCreate(dj->type_room[5].model, "assets/models/Room/Room3T.obj");
    dj->type_room[5].col = ColliderCreate("assets/models/Room/ColT.obj");

    ModelCreate(dj->type_room[2].model, "assets/models/Room/Room2I.obj");
    dj->type_room[2].col = ColliderCreate("assets/models/Room/ColI.obj");

    ModelCreate(dj->type_room[7].model, "assets/models/Room/RoomB.obj");
    dj->type_room[7].col = ColliderCreate("assets/models/Room/ColB.obj");

    ModelCreate(dj->type_room[3].model, "assets/models/Room/Room2L.obj");
    dj->type_room[3].col = ColliderCreate("assets/models/Room/ColL.obj");
}

/**
 * @brief Load the room
 * 
 * This function loads the room.
 * 
 * @param scene The scene
 * @param player The player
 * @param dj The Dungeon object
 * @param body The RigidBody
 * @param collider The Collider
 * @param gameState The GameState
 */
void LoadRoom(Scene* scene, Model* player, Dungeon* dj,RigidBody* body, Collider* collider,GameState* gameState) {
    char d1;
    switch (dj->direction){
        case 'S': 
            d1 = 'N';
            break;
        case 'E': 
            d1= 'W';
            break;
        case 'W': 
            d1 = 'E';
            break;
        case 'N': 
            d1 = 'S';
            break;
        default :
            d1 ='S';
            break;
    }
    if (dj->quit){
        gameState->nextSceneIndex = 2;
        gameState->previousSceneIndex = 1;
        ChangeSceneEvent(gameState->nextSceneIndex);
        return;
    }
    switch (dj->rooms[dj->current_room].id) {
        case 0:
            LoadRoom1C(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col, player,dj,body);
            break;
        case 1:
            LoadRoom2C(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            break;
        case 4:
            LoadRoom3C(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player, dj,body);
            break;
        case 6:
            LoadRoom4C(scene,gameState,player,dj,body);
            break;
        case 5:
            LoadRoom3T(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col, player, dj,body);
            break;
        case 3:
            LoadRoom2L(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player, dj,body);
            break;
        case 2:
            LoadRoom2I(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            break;
        case 7:
            if (!dj->hasKey){
                for (int i =0;i<dj->nb_rooms;i++){
                if (dj->adj[dj->current_room][i]!='O'){
                    dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                    dj->direction = d1;
                    dj->change = true;
                    player->isBusy = true;
                    break;
                }
            } 
            }
            else{
            LoadRoomB(scene,gameState,dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            }
            break;
    }
    

    mat4 id;
    glm_translate_make(id,body->velocity);
    glm_aabb_transform(collider->boundingBoxReference[0],id,collider->boundingBox[0]);
}

/**
 * @brief prints the information of the dungeon
 * 
 * This function prints the information of the dungeon.
 * 
 * @param dj The Dungeon object
*/
void Affiche(Dungeon *dj){
    printf("\n");
    printAdjList(dj);
    printf("Nb de salle:%d\n",dj->nb_rooms);
    int nb_boss = 0;
    int nb_key = 0;
    int nb_loot = 0;
    int nb_fight = 0;
    int id0 = 0;
    int id1 = 0;
    int id2 = 0;
    int id3 = 0;
    int id4 = 0;
    int id5 = 0;
    int id6 = 0;
    int id7 = 0;
    for (int i =0;i<dj->nb_rooms;i++){
        if (dj->rooms[i].type==0){
            nb_boss++;
        }
        else if (dj->rooms[i].type==1){
            nb_key++;
        }
        else if (dj->rooms[i].type==2){
            nb_loot++;
        }
        else if (dj->rooms[i].type==3){
            nb_fight++;
        }

        if (dj->rooms[i].id==0){
            id0++;
        }
        else if (dj->rooms[i].id==1){
            id1++;
        }
        else if (dj->rooms[i].id==2){
            id2++;
        }
        else if (dj->rooms[i].id==3){
            id3++;
        }
        else if (dj->rooms[i].id==4){
            id4++;
        }
        else if (dj->rooms[i].id==5){
            id5++;
        }
        else if (dj->rooms[i].id==6){
            id6++;
        }
        else if (dj->rooms[i].id==7){
            id7++;
        }
     printf("Le type de la salle %d est %d et son id est %d et a %d enemy : id %d et %d\n",i,dj->rooms[i].type,dj->rooms[i].id,dj->rooms[i].nb_enemy,dj->rooms[i].id_enemy[0],dj->rooms[i].id_enemy[1]);


    }
    printf("Il y a %d boss, il y a %d clé, il y a %d salles de loot, il y a %d salles de fight.\n",nb_boss,nb_key,nb_loot,nb_fight);
    printf("Il y a %d 1C,%d 2C,%d 2I,%d 2L, %d 3C,%d 3T, %d 4C, %d B\n",id0,id1,id2,id3,id4,id5,id6,id7);

}

/**
 * @brief Load the room 1C
 * 
 * This function loads the room 1C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom1C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    float rot;
        switch (dj->direction){
        case 'S': 
            rot = glm_rad(180.0f);
            break;
        case 'E': 
            rot = glm_rad(-90.0f);
            break;
        case 'W': 
            rot = glm_rad(90.0f);
            break;
        case 'N': 
            rot = glm_rad(0.0f);
            break;
        default:
            rot = glm_rad(0.0f);
            break;
          }
    int n =-1;
    if (dj->rooms[dj->current_room].type==1){
        n=4;
    }
    else if (dj->rooms[dj->current_room].type==2){   
        n=5;
    }
    if (n!=-1){
        Entity* Chest = &scene->entities[n];
        ((Model*)Chest->components[0].data)->rotation[1] = rot;
        ((Model*)Chest->components[1].data)->rotation[1] = rot;
        glm_rotate_make(((Collider*)Chest->components[2].data)->transformMatrix,rot,(vec3){0.0f,1.0f,0.0f});
        for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(((Collider*)Chest->components[2].data)->boundingBoxReference[i],((Collider*)Chest->components[2].data)->transformMatrix,((Collider*)Chest->components[2].data)->boundingBox[i]); }
        UpdateCollider(((Collider*)Chest->components[2].data));
        if (dj->rooms[dj->current_room].isCompleted){
        ((Model*)Chest->components[1].data)->isRenderable = true;
        }
        else{
        ((Model*)Chest->components[0].data)->isRenderable = true;
        }
    }
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(180.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-2.0f,0.0f,-3.5f}, body->velocity);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){2.0f,0.0f,3.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(-90.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
    
}

/**
 * @brief Load the room B
 * 
 * This function loads the room B.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoomB(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
     
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(180.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){0.0f,0.0f,-11.0f},  body->velocity);    
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){0.0f,0.0f,11.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(-90.0f),(vec3){0.0f,1.0f,0.0f});
            for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-11.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){11.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
    
}

/**
 * @brief Load the room 2C
 * 
 * This function loads the room 2C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
     
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-2.0f,0.0f,-3.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){2.0f,0.0f,3.0},  body->velocity);
        break;
    case 'E':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
           for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

/**
 * @brief Load the room 3C
 * 
 * This function loads the room 3C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom3C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    char *l = "NSWE";
    int c =0;
    bool dir_used[4] = {false,false,false,false};
    for (int k = 0; k < dj->nb_rooms && c < 3; k++) {
    if (dj->adj[dj->current_room][k] != 'O') {
        for (int j = 0; j < 4; j++) {
            if (dj->adj[dj->current_room][k] == l[j]) {
                dir_used[j] = true;
                c++;
                break;
            }
        }
    }
}
    if (!(dir_used[0])){
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else if (!(dir_used[1])){
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(-90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else if (!(dir_used[2])){
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(180.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    switch (dj->direction)
    {
    case 'S':
        glm_vec3_copy((vec3){-2.0f,0.0f,-2.5f},  body->velocity);
        break;
    case 'N':
        glm_vec3_copy((vec3){2.0f,0.0f,3.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

/**
 * @brief Load the room 4C
 * 
 * This function loads the room 4C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom4C(Scene* scene,GameState* gameState,Model* player,Dungeon*dj,RigidBody* body){
    switch (dj->direction)
    {
        case 'N':
            glm_vec3_copy((vec3){2.0f,0.0f,3.0f},  body->velocity);
            player->rotation[1] =glm_rad(180.0f);
            break;
        case 'S':
            glm_vec3_copy((vec3){-2.2f,0.0f,-3.0f},  body->velocity);
            break;
        case 'W':
            glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
            player->rotation[1] =glm_rad(-90.0f);
            break;
        case 'E':
            glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
            player->rotation[1] =glm_rad(90.0f);
            break;
    }
}

/**
 * @brief Load the room 2I
 * 
 * This function loads the room 2I.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2I(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon * dj,RigidBody* body) {
     
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){0.0f,0.0f,-3.5f},  body->velocity);
        player->rotation[1] =glm_rad(0.0f);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){0.0f,0.0f,3.5f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
             for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){-3.5f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
            for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        glm_vec3_copy((vec3){3.5f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

/**
 * @brief Load the room 3T
 * 
 * This function loads the room 3T.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom3T(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    int c=0;
    for (int k = 0; k < dj->nb_rooms && c < 3; k++) {
    if (dj->adj[dj->current_room][k] != 'O') {
        for (int j = 0; j < 4; j++) {
            if (dj->adj[dj->current_room][k] == l[j]) {
                dir_used[j] = true;
                c++;
                break;
            }
        }
    }
}
    if (!dir_used[0]){
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else if (!dir_used[1]){
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(-90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else if (!dir_used[2]){
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(180.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    switch (dj->direction)
    {
    case 'S':
        glm_vec3_copy((vec3){-0.0f,0.0f,-5.5f},  body->velocity);
        break;
    case 'N':
        glm_vec3_copy((vec3){0.0f,0.0f,6.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        glm_vec3_copy((vec3){-6.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        glm_vec3_copy((vec3){6.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

/**
 * @brief Load the room 2L
 * 
 * This function loads the room 2L.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2L(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    for (int k=0;k<dj->nb_rooms;k++){
        if (dj->adj[dj->current_room][k]!='O'){
            for (int j=0;j<4;j++){
                if (dj->adj[dj->current_room][k]==l[j]){
                    dir_used[j]=true;
                }
            }
        }
    }
    if (dir_used[1]&&dir_used[2]){        
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else if (dir_used[1]&&dir_used[3]){        
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(180.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
        
    }else if (dir_used[0]&&dir_used[3]){        
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(-90.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,glm_rad(0.0f),(vec3){0.0f,1.0f,0.0f});
              for (int i = 0; i < col->numCollider; i++) {glm_aabb_transform(col->boundingBoxReference[i],col->transformMatrix,col->boundingBox[i]); }
    }
    switch (dj->direction)
    {
    case 'S':
        if (dir_used[3]){
        glm_vec3_copy((vec3){-0.5f,0.0f,-3.5f},  body->velocity);
        }
        else {glm_vec3_copy((vec3){-7.3f,0.0f,-11.5f},  body->velocity);}
        break;
    case 'N':
        if (dir_used[3]){
        glm_vec3_copy((vec3){7.5f,0.0f,11.0f},  body->velocity);
        }
        else {glm_vec3_copy((vec3){0.15f,0.0f,3.6f},  body->velocity);}
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        if (dir_used[1]){
        glm_vec3_copy((vec3){-11.1f,0.0f,7.25f},  body->velocity);
        }
        else {glm_vec3_copy((vec3){-3.5f,0.0f,0.0f},  body->velocity);}
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        if (dir_used[1]){
        glm_vec3_copy((vec3){3.8f,0.0f,0.0f},  body->velocity);
        }
        else {glm_vec3_copy((vec3){11.2f,0.0f,-7.8f},  body->velocity);}
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

/*
* @brief Handle the logic of the room 1C
*
* This function handles the logic of the room 1C.
*
* @param scene The scene
* @param gameState The GameState
* @param dj The Dungeon object
* @param body The RigidBody
*/
void LogicRoom1C(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){  
    SDL_Color color_black = {0, 0, 0, 0};
    SDL_Color color_white = {255, 255, 255, 0};
    Entity* player = &scene->entities[2];
    Model* playerModel = (Model*)getComponent(player,COMPONENT_RENDERABLE);
    RigidBody* playerrb = (RigidBody*)getComponent(player,COMPONENT_RIGIDBODY);
    vec3 DoorPosition={0.0f,0.0f,0.0f};
    vec3 DoorDir;
    char d1 = dj->direction;
    if (dj->rooms[dj->current_room].type==1){
        Entity* keyBossChest = &scene->entities[4];
        Model* chestModel;
        vec3 ChestPosition;   
        if (dj->rooms[dj->current_room].isCompleted){

        }
        else{
            float x = playerModel->position[0];
            float y = playerModel->position[1];
            if (y < 1.f && y > -1.f && x < 1.08f && x > -1.0){
                RenderText("Appuyer sur E pour ouvrir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                if (getKeyState(SDLK_e)){
                    dj->rooms[dj->current_room].isCompleted = true;
                    ((Model*)keyBossChest->components[0].data)->isRenderable = false;
                    ((Model*)keyBossChest->components[1].data)->isRenderable = true;
                    playerModel->isBusy = true;
                    dj->hasKey = true;
                }
            }
            }
        if (playerModel->isBusy ){
                RenderText("Coffre         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                RenderText("Vous venez de récupérer la clé du donjon !", color_black, gameState->g_WindowWidth / 2 - 115, gameState->g_WindowHeight / 15 + 100, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                RenderImage("assets/images/redBossKey.png", gameState->g_WindowWidth/2, gameState->g_WindowHeight/30 , gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                if (getMouseButtonState(1)){
                    playerModel->isBusy = false;
        }
        }   
    }
    else if (dj->rooms[dj->current_room].type==2){
        Entity* Chest = &scene->entities[5];
        Model* chestModel;
        vec3 ChestPosition;   
        if (dj->rooms[dj->current_room].isCompleted){
            
        }
        else{
            chestModel = (Model*)Chest->components[0].data;
            vec3 ChestDir;
            glm_vec3_sub( playerModel->position, ChestPosition, ChestDir);
            if (glm_vec3_norm(ChestDir)<1.5f ){
                RenderText("Appuyer sur E pour ouvrir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                if (getKeyState(SDLK_e)){
                    dj->rooms[dj->current_room].isCompleted = true;
                    ((Model*)Chest->components[0].data)->isRenderable = false;
                    ((Model*)Chest->components[1].data)->isRenderable = true;
                    playerModel->isBusy = true;
                }
                 
            }
            }
        if (playerModel->isBusy ){
                RenderText("Coffre         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                RenderText("Vous venez de récupérer un objet !", color_black, gameState->g_WindowWidth / 2 - 135, gameState->g_WindowHeight / 15 + 100, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                if (getMouseButtonState(1)){
                    playerModel->isBusy = false;
        }
        }   
    }
    switch (dj->direction){
        case 'S': 
            glm_vec3_copy((vec3){-2.15f,0.0f,-4.15f},DoorPosition);
            d1 = 'N';
            break;
        case 'E': 
            glm_vec3_copy((vec3){-3.8f,0.0f,2.4f},DoorPosition);
            d1 = 'W';
            break;
        case 'W': 
            glm_vec3_copy((vec3){3.9f,0.0f,-3.1f},DoorPosition);
            d1 = 'E';
            break;
        case 'N': 
            glm_vec3_copy((vec3){2.1f,0.0f,4.3f},DoorPosition);
            d1 = 'S';
            break;
    }
    glm_vec3_sub( body->velocity, DoorPosition, DoorDir);
    float DoorDist = glm_vec3_norm(DoorDir);
    if (DoorDist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]!='O'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }



}

/**
 * @brief Handle the logic of the room 2C
 *
 * This function handles the logic of the room 2C.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom2C(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    vec3 Door1Position;
    vec3 Door2Position;
    vec3 Door1Dir;
    vec3 Door2Dir;
    char d1='S';
    char d2='N';
    switch (dj->direction){
        case 'S': 
            glm_vec3_copy((vec3){-2.15f,0.0f,-4.15f},Door1Position);//D1<=>S
            glm_vec3_copy((vec3){2.1f,0.0f,4.3f},Door2Position);//D2<=>N
            d1 = 'S';d2='N';
            break;
        case 'E': 
            glm_vec3_copy((vec3){-3.8f,0.0f,2.4f},Door1Position);//D1<=>E
            glm_vec3_copy((vec3){3.9f,0.0f,-3.1f},Door2Position);//D2<=>W
            d1 = 'E';d2='W';
            break;
        case 'W': 
            glm_vec3_copy((vec3){-3.8f,0.0f,2.4f},Door1Position);//E
            glm_vec3_copy((vec3){3.9f,0.0f,-3.1f},Door2Position);//W
            d1 = 'E';d2='W';
            break;
        case 'N': 
            glm_vec3_copy((vec3){-2.15f,0.0f,-4.15f},Door1Position);
            glm_vec3_copy((vec3){2.1f,0.0f,4.3f},Door2Position);
            d1 = 'S';d2='N';
            break;
    }
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);

    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    if (Door1Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d2){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }


}

/**
 * @brief Handle the logic of the room 3C
 *
 * This function handles the logic of the room 3C.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom3C(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    for (int k=0;k<dj->nb_rooms;k++){
        if (dj->adj[dj->current_room][k]!='O'){
            for (int j=0;j<4;j++){
                if (dj->adj[dj->current_room][k]==l[j]){
                    dir_used[j]=true;
                }
            }
        }
    }
    vec3 Door1Position={0.0f,0.0f,0.0f};
    vec3 Door2Position={0.0f,0.0f,0.0f};
    vec3 Door3Position={0.0f,0.0f,0.0f};
    vec3 Door4Position={0.0f,0.0f,0.0f};
    vec3 Door1Dir;
    vec3 Door2Dir;
    vec3 Door3Dir;
    vec3 Door4Dir;
    glm_vec3_copy((vec3){-2.15f,0.0f,-4.15f},Door1Position);//D1 = S
    glm_vec3_copy((vec3){2.1f,0.0f,4.3f},Door2Position);//D2 = N
    glm_vec3_copy((vec3){-3.8f,0.0f,2.4f},Door3Position);//D3 = E
    glm_vec3_copy((vec3){3.9f,0.0f,-3.1f},Door4Position);//D4 = W
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);
    glm_vec3_sub( body->velocity, Door3Position, Door3Dir);
    glm_vec3_sub( body->velocity, Door4Position, Door4Dir);
    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    float Door3Dist = glm_vec3_norm(Door3Dir);
    float Door4Dist = glm_vec3_norm(Door4Dir);

    if (Door1Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[1] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'N';
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[0] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='N'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'S';
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[3] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'W';
                break;
            }
        }
        dj->change = true;
    }
    else if (Door4Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[2]){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='W'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'E';
                break;
            }
        }
        dj->change = true;
    }
    else{
        return;
    }

}

/**
 * @brief Handle the logic of the room 4C
 *
 * This function handles the logic of the room 4C.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom4C(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    vec3 Door1Position={0.0f,0.0f,0.0f};
    vec3 Door2Position={0.0f,0.0f,0.0f};
    vec3 Door3Position={0.0f,0.0f,0.0f};
    vec3 Door4Position={0.0f,0.0f,0.0f};
    vec3 Door1Dir;
    vec3 Door2Dir;
    vec3 Door3Dir;
    vec3 Door4Dir;
    glm_vec3_copy((vec3){-2.15f,0.0f,-4.15f},Door1Position);//D1 = S
    glm_vec3_copy((vec3){2.1f,0.0f,4.3f},Door2Position);//D2 = N
    glm_vec3_copy((vec3){-3.8f,0.0f,2.4f},Door3Position);//D3 = E
    glm_vec3_copy((vec3){3.9f,0.0f,-3.1f},Door4Position);//D4 = W
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);
    glm_vec3_sub( body->velocity, Door3Position, Door3Dir);
    glm_vec3_sub( body->velocity, Door4Position, Door4Dir);
    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    float Door3Dist = glm_vec3_norm(Door3Dir);
    float Door4Dist = glm_vec3_norm(Door4Dir);

    if (Door1Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'N';
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='N'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'S';
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'W';
                break;
            }
        }
        dj->change = true;
    }
    else if (Door4Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='W'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = 'E';
                break;
            }
        }
        dj->change = true;
    }
    else{
        return;
    }

}

/**
 * @brief Handle the logic of the room 3T
 *
 * This function handles the logic of the room 3T.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom3T(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    for (int k=0;k<dj->nb_rooms;k++){
        if (dj->adj[dj->current_room][k]!='O'){
            for (int j=0;j<4;j++){
                if (dj->adj[dj->current_room][k]==l[j]){
                    dir_used[j]=true;
                }
            }
        }
    }
    vec3 Door1Position;
    vec3 Door2Position;
    vec3 Door3Position;
    vec3 Door1Dir;
    vec3 Door2Dir;
    vec3 Door3Dir;
    char d1;
    char d2;
    char d3;
    char d4;
    if (!dir_used[0]){
        glmc_vec3_copy((vec3){0.2f,0.0f,-7.4f},Door1Position);//s
        glmc_vec3_copy((vec3){-7.5f,0.0f,-0.3f},Door2Position);//E
        glmc_vec3_copy((vec3){7.5f,0.0f,-0.3f},Door3Position);//w
        d1 = 'S';d2 = 'N';d3 = 'E';d4 = 'W';

    }
    else if (!dir_used[1]){
        glmc_vec3_copy((vec3){0.0f,0.0f,7.5f},Door1Position);//N
        glmc_vec3_copy((vec3){7.5f,0.0f,0.0f},Door2Position);//W
        glmc_vec3_copy((vec3){-7.6f,0.0f,-0.25f},Door3Position);//E
        d1 = 'N';d2 = 'S';d3 = 'W';d4 = 'E';
    }
    else if (!dir_used[2]){
        glmc_vec3_copy((vec3){-7.4f,0.0f,-0.5f},Door1Position);//E
        glmc_vec3_copy((vec3){0.0f,0.0f,7.5f},Door2Position);//N
        glmc_vec3_copy((vec3){0.20f,0.0f,-7.5f},Door3Position);//S
        d1 = 'E';d2 = 'W';d3 = 'N';d4 = 'S';

    }
    else{
        glmc_vec3_copy((vec3){7.5f,0.0f,0.0f},Door1Position);//W
        glmc_vec3_copy((vec3){0.0f,0.0f,-7.5f},Door2Position);//S
        glmc_vec3_copy((vec3){0.0f,0.0f,7.5f},Door3Position);//N
        d1 = 'W';d2 = 'E';d3 = 'S';d4 = 'N';

    }
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);
    glm_vec3_sub( body->velocity, Door3Position, Door3Dir);
    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    float Door3Dist = glm_vec3_norm(Door3Dir);

    if (Door1Dist<1.8f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.8f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d3){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d4;
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.8f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d4){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d3;
                break;
            }
        }
        dj->change = true;
    }
}

/**
 * @brief Handle the logic of the room 2L
 *
 * This function handles the logic of the room 2L.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom2L(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    for (int k=0;k<dj->nb_rooms;k++){
        if (dj->adj[dj->current_room][k]!='O'){
            for (int j=0;j<4;j++){
                if (dj->adj[dj->current_room][k]==l[j]){
                    dir_used[j]=true;
                }
            }
        }
    }

    vec3 Door1Position;
    vec3 Door2Position;
    vec3 Door1Dir;
    vec3 Door2Dir;
    char d1='S';
    char d2='N';
    if (dir_used[1]){
        d1 = 'N';
        if (dir_used[2]){//S&W
            glmc_vec3_copy((vec3){-7.3f,0.0f,-12.4f},Door1Position);//S
            glmc_vec3_copy((vec3){4.7f,0.0f,-0.3f},Door2Position);//W
            d2 = 'E';

        }
        else {//S&E
            glmc_vec3_copy((vec3){0.0f,0.0f,-5.0f},Door1Position);//S
            glmc_vec3_copy((vec3){-12.5f,0.0f,7.25f},Door2Position);//E
            d2 = 'W';
        }
    }
    else {
        d1 = 'S';
        if (dir_used[2]){//N&W
            glmc_vec3_copy((vec3){0.0f,0.0f,5.0f},Door1Position);//N
            glmc_vec3_copy((vec3){12.4f,0.0f,-8.0f},Door2Position);//W
            d2 = 'E';

        }
        else {//N&E
            glmc_vec3_copy((vec3){7.3f,0.0f,12.4f},Door1Position);//N
            glmc_vec3_copy((vec3){-5.0f,0.0f,-0.3f},Door2Position);//E
            d2 = 'W';

        }
    }
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);
    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);

    if (Door1Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'||dj->adj[dj->current_room][i]=='N'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'||dj->adj[dj->current_room][i]=='W'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
}

/**
 * @brief Handle the logic of the room 2I
 *
 * This function handles the logic of the room 2I.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoom2I(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    vec3 Door1Position;
    vec3 Door2Position;
    vec3 Door1Dir;
    vec3 Door2Dir;
    char d1='S';
    char d2='N';
    switch (dj->direction){
        case 'S': 
            glm_vec3_copy((vec3){0.0f,0.0f,-4.75f},Door1Position);//D1<=>S
            glm_vec3_copy((vec3){0.0f,0.0f,4.75f},Door2Position);//D2<=>N
            d1 = 'S';d2='N';
            break;
        case 'E': 
            glm_vec3_copy((vec3){-4.75f,0.0f,0.0f},Door1Position);//D1<=>E
            glm_vec3_copy((vec3){4.75f,0.0f,0.0f},Door2Position);//D2<=>W
            d1 = 'E';d2='W';
            break;
        case 'W': 
            glm_vec3_copy((vec3){-4.75f,0.0f,0.0f},Door1Position);//D1<=>E
            glm_vec3_copy((vec3){4.75f,0.0f,0.0f},Door2Position);//D2<=>W
            d1 = 'E';d2='W';
            break;
        case 'N': 
            glm_vec3_copy((vec3){0.0f,0.0f,-4.75f},Door1Position);
            glm_vec3_copy((vec3){0.0f,0.0f,4.75},Door2Position);
            d1 = 'S';d2='N';
            break;
    }
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);

    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    if (Door1Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d2){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }

}

/**
 * @brief Handle the logic of the room B
 *
 * This function handles the logic of the room B.
 *
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LogicRoomB(Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body ){
    Entity* player = &scene->entities[2];
    Model* playerModel = ((Model*)getComponent(player, COMPONENT_RENDERABLE));
    RigidBody* playerRb = ((RigidBody*)getComponent(player, COMPONENT_RIGIDBODY));
    vec3 DoorPosition={0.0f,0.0f,0.0f};
    vec3 DoorDir;
    char d1=dj->direction;
    switch (dj->direction){
        case 'S': 
            glm_vec3_copy((vec3){0.0f,0.0f,-12.6f},DoorPosition);
            d1 = 'N';
            break;
        case 'E': 
            glm_vec3_copy((vec3){-12.6f,0.0f,0.0f},DoorPosition);
            d1= 'W';
            break;
        case 'W': 
            glm_vec3_copy((vec3){12.6f,0.0f,0.0f},DoorPosition);
            d1 = 'E';
            break;
        case 'N': 
            glm_vec3_copy((vec3){0.0f,0.0f,12.6f},DoorPosition);
            d1 = 'S';
            break;
    }
    if (dj->rooms[dj->current_room].isCompleted){
        Entity* gem = &scene->entities[5+NB_ENEMY+2];
        Model* gemModel = ((Model*)getComponent(gem, COMPONENT_RENDERABLE));
        if (!gameState->hasGreenGem&&!gemModel->isRenderable){
            gemModel->isRenderable = true;
        }
        gemModel->rotation[1] += 0.01;
        float dist_joueur_gem = sqrt(pow(playerModel->position[0] - gemModel->position[0], 2) + pow(playerModel->position[2] - gemModel->position[2], 2));
        if (dist_joueur_gem < 1.0f) {
            gemModel->isRenderable = false;
            gameState->hasGreenGem = true;
            playerModel->isBusy = true;
        }
        if (gameState->hasGreenGem){
            playerModel->rotation[1] += 0.1;
            playerRb->velocity[1] += 0.1;
            if (playerRb->velocity[1] > 20.0f){
                gameState->nextSceneIndex = 2;
                gameState->previousSceneIndex = 1;
                playerModel->isBusy = false;
                gameState->isForestDungeonDone = true;
                ChangeSceneEvent(gameState->nextSceneIndex);
            }
        }
    }


    glm_vec3_sub( body->velocity, DoorPosition, DoorDir);
    float DoorDist = glm_vec3_norm(DoorDir);
    if ((DoorDist<1.5f&&getKeyState(SDLK_e)&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime)){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]!='O'){
                if (i==dj->current_room){dj->quit = true;}
                dj->previous_direction = dj->direction;
                dj->previous_room = dj->current_room;

                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }


}

/**
 * @brief Set the type of the rooms
 * 
 * This function sets the type of the rooms.
 * 
 * @param dj The Dungeon object
*/
void setTypeRoom(Dungeon* dj){
    bool hasKeyBoss = false;
    srand(time(NULL));
    for (int i =1 ; i<dj->nb_rooms;i++){
        if (dj->rooms[i].id == 0 && !hasKeyBoss){
            dj->rooms[i].type = 1;
            hasKeyBoss = true;
        }
        else if (dj->rooms[i].id == 7){
            dj->rooms[i].type = 0;
        }
        else if (dj->rooms[i].id == 0){
            int n = rand()% LootChance;
            n+=1;
            if (n == 1 || n==0){
                 dj->rooms[i].type = 2;
                 }
            else if (n==2){
                dj->rooms[i].type = 3;
            }

        }
        else {
            int n = rand()%LootChance;
            n+=1;
            if (n==2){
                dj->rooms[i].type = 3;
                }
            }
        if (dj->rooms[i].type == 3){
            if (dj->nb_enemy<NB_ENEMY-1){
                dj->rooms[i].id_enemy[0] = 6 + dj->nb_enemy;
                dj->rooms[i].id_enemy[1] = 6 + (dj->nb_enemy+1);
                dj->nb_enemy+=2;
                dj->rooms[i].nb_enemy = 2;
            }
            else if (dj->nb_enemy<NB_ENEMY){
                dj->rooms[i].id_enemy[0] = 6 + dj->nb_enemy;
                dj->nb_enemy+=1;
                dj->rooms[i].nb_enemy = 1;
            }
            else{
                dj->rooms[i].type = -1;
            }
        }
        }
     }
        
/*
* @brief Display the minimap
*
* This function displays the minimap.
*
* @param scene The scene
* @param dj The Dungeon object
* @param gameState The GameState
*/
void displayMiniMap(Scene* scene, Dungeon* dj,GameState* gameState){
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    int c=0;
    for (int k = 0; k < dj->nb_rooms && c < 3; k++) {
    if (dj->adj[dj->current_room][k] != 'O') {
        for (int j = 0; j < 4; j++) {
            if (dj->adj[dj->current_room][k] == l[j]) {
                dir_used[j] = true;
                c++;
                break;
            }
        }
    }
    }
     RenderImage("assets/images/map.png", gameState->g_WindowWidth - 180, gameState->g_WindowHeight /15-40, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
     if (dir_used[0]){
        RenderImage("assets/images/map.png", gameState->g_WindowWidth - 180, gameState->g_WindowHeight /15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
     }
     if (dir_used[1]&&dj->current_room!=0){
        RenderImage("assets/images/map.png", gameState->g_WindowWidth - 180, gameState->g_WindowHeight /15-150, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
     }
     if (dir_used[2]){
        RenderImage("assets/images/map.png", gameState->g_WindowWidth - 290, gameState->g_WindowHeight /15-40, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
     }
     if (dir_used[3]){
        RenderImage("assets/images/map.png", gameState->g_WindowWidth - 70, gameState->g_WindowHeight /15-40, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
     }

}