#include "Dungeon.h"
Dungeon* dj_create(){
    Dungeon *dj = malloc(sizeof(Dungeon)); 
    if (dj == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour Dungeon\n");
        exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));
    dj->nb_rooms = rand() % (NB_ROOM_MAX + 1 - NB_ROOM_MIN) + NB_ROOM_MIN;
    initializeAdjacencyList(dj);
    
    dj->rooms = malloc((dj->nb_rooms )  * sizeof(Room));
    if (dj->rooms == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour rooms\n");
        exit(EXIT_FAILURE);
    }
    dj->current_room = 0;
    dj->direction = 'S';
    dj->change = true;
    dj->lastRoomChangeTime = 0;
    initializeLRooms(dj);
    return dj;
}
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
void freeDungeon(Dungeon *dj) {
    if (dj == NULL) {
        return;
    }
    freeTypeRooms(dj);
    freeAdjacencyList(dj);
    freeRooms(dj);
    free(dj);
}
void freeRooms(Dungeon* dj){
    for (int i =0;i<dj->nb_rooms;i++){
        freeRoom(&dj->rooms[i]);
    }
    free(dj->rooms);
}
void freeTypeRooms(Dungeon* dj){
    for (int i =0;i<NB_MODEL_SALLE;i++){
        freeLRoom(&dj->type_room[i]);
    }
    free(dj->type_room);
}

void freeAdjacencyList(Dungeon *dj) {
    for (int i = 0; i < dj->nb_rooms; i++) {
        free(dj->adj[i]);
    }
    free(dj->adj);
}
void initialize(Dungeon *dj){
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


void printAdjList(Dungeon *dj){    
    for (int i =0;i<dj->nb_rooms;i++){
        printf("%s\n",dj->adj[i]);
    }

}



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

void printDepth(int *depths, int nb_rooms) {
    for (int i = 0; i < nb_rooms; i++) {
        printf("Profondeur de la salle %d: %d\n", i, depths[i]);
    }
}
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
                printf("La salle du Boss est la salle %d\n",i);
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

void LoadRoom(Model* player, Dungeon* dj,RigidBody* body) {
    printf("Changement de salle du type : %d\n",dj->rooms[dj->current_room].id);
    printf("On vient du %c\n",dj->direction);

    switch (dj->rooms[dj->current_room].id) {
        case 0:
            LoadRoom1C(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col, player,dj,body);
            break;
        case 1:
            LoadRoom2C(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            break;
        case 4:
            LoadRoom3C(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player, dj,body);
            break;
        case 6:
            LoadRoom4C(player,dj,body);
            break;
        case 5:
            LoadRoom3T(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col, player, dj,body);
            break;
        case 3:
            LoadRoom2L(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player, dj,body);
            break;
        case 2:
            LoadRoom2I(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            break;
        case 7:
            LoadRoomB(dj->type_room[dj->rooms[dj->current_room].id].model,dj->type_room[dj->rooms[dj->current_room].id].col,  player,dj,body);
            break;
    }
    if (dj->current_room==0&&dj->direction=='N'){
        printf("On quitte le donjon\n");
        dj->direction = 'S';

        return;
    }
    printf("Nous sommes dans la salle %d  (id = %d) depuis le %c\n",dj->current_room,dj->rooms[dj->current_room].id,dj->direction);
}


void Affiche(Dungeon *dj){
    printf("\n");
    printAdjList(dj);
    printf("Nb de salle:%d\n",dj->nb_rooms);
}
//on doit pouvoir factoriser les LoadRoomiC mais flemme
void LoadRoom1C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,180.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-2.0f,0.0f,-3.5f}, body->velocity);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){2.0f,0.0f,3.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,-90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
    
}
void LoadRoomB(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,180.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){0.0f,0.0f,-11.0f},  body->velocity);    
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){0.0f,0.0f,11.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,-90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-11.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){11.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
    
}
void LoadRoom2C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-2.0f,0.0f,-3.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){2.0f,0.0f,3.0},  body->velocity);
        break;
    case 'E':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-3.8f,0.0f,2.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){3.8f,0.0f,-2.8f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}
void LoadRoom3C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
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
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (!(dir_used[1])){
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,-90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (!(dir_used[2])){
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,180.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
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
void LoadRoom4C(Model* player,Dungeon*dj,RigidBody* body){
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

void LoadRoom2I(Model* map,Collider* col, Model* player,Dungeon * dj,RigidBody* body) {
    switch (dj->direction)
    {
    case 'S':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){0.0f,0.0f,-4.0f},  body->velocity);
        break;
    case 'N':
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){0.0f,0.0f,4.0f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){-4.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        map->rotation[1] = glm_rad(90.0f);
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
        glm_vec3_copy((vec3){4.0f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

void LoadRoom3T(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
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
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (!dir_used[1]){
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,-90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (!dir_used[2]){
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,180.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    switch (dj->direction)
    {
    case 'S':
        glm_vec3_copy((vec3){-0.0f,0.0f,-6.0f},  body->velocity);
        break;
    case 'N':
        glm_vec3_copy((vec3){0.0f,0.0f,6.5f},  body->velocity);
        player->rotation[1] =glm_rad(180.0f);
        break;
    case 'E':
        glm_vec3_copy((vec3){-6.5f,0.0f,0.0f},  body->velocity);
        player->rotation[1] =glm_rad(90.0f);
        break;
    case 'W':
        glm_vec3_copy((vec3){6.5f,0.0f,-0.4f},  body->velocity);
        player->rotation[1] =glm_rad(-90.0f);
        break;
    }
}

void LoadRoom2L(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body) {
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
        glm_rotate_make(col->transformMatrix,90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (dir_used[1]&&dir_used[3]){        
        map->rotation[1] = glm_rad(180.0f);
        glm_rotate_make(col->transformMatrix,180.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else if (dir_used[0]&&dir_used[3]){        
        map->rotation[1] = glm_rad(-90.0f);
        glm_rotate_make(col->transformMatrix,-90.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    else{
        map->rotation[1] = glm_rad(0.0f);
        glm_rotate_make(col->transformMatrix,0.0f,(vec3){0.0f,1.0f,0.0f});
        UpdateCollider(col);
    }
    switch (dj->direction)
    {
    case 'S':
        if (dir_used[3]){
        glm_vec3_copy((vec3){-0.5f,0.0f,-4.25f},  body->velocity);
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
        else {glm_vec3_copy((vec3){-3.8f,0.0f,0.0f},  body->velocity);}
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
void LogicRoom1C(Dungeon*dj,RigidBody* body ){  
    vec3 DoorPosition={0.0f,0.0f,0.0f};
    vec3 DoorDir;
    char d1 = dj->direction;
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
    if (DoorDist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]!='O'){
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (getKeyState(SDLK_o)){
        printf("D1 = %f\n",DoorDist);
    }

}
void LogicRoom2C(Dungeon*dj,RigidBody* body){
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
    if (Door1Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d2){
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (getKeyState(SDLK_o)){
        printf("D1 = %f,D2 = %f\n",Door1Dist,Door2Dist);
    }

}
void LogicRoom3C(Dungeon*dj,RigidBody* body ){
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
    if (getKeyState(SDLK_o)){
        printf("S : %f, N : %f, E : %f, W : %f\n",Door1Dist,Door2Dist,Door3Dist,Door4Dist);
    }
    if (Door1Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[1] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'){
                dj->current_room = i;
                dj->direction = 'N';
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[0] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='N'){
                dj->current_room = i;
                dj->direction = 'S';
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[3] ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'){
                dj->current_room = i;
                dj->direction = 'W';
                break;
            }
        }
        dj->change = true;
    }
    else if (Door4Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime&&dir_used[2]){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='W'){
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

void LogicRoom4C(Dungeon*dj,RigidBody* body){
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
    if (getKeyState(SDLK_o)){
        printf("S : %f, N : %f, E : %f, W : %f\n",Door1Dist,Door2Dist,Door3Dist,Door4Dist);
    }
    if (Door1Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'){
                dj->current_room = i;
                dj->direction = 'N';
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='N'){
                dj->current_room = i;
                dj->direction = 'S';
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'){
                dj->current_room = i;
                dj->direction = 'W';
                break;
            }
        }
        dj->change = true;
    }
    else if (Door4Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='W'){
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

void LogicRoom3T(Dungeon*dj,RigidBody* body){
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
        glmc_vec3_copy((vec3){4.5f,0.0f,0.0f},Door2Position);//W
        glmc_vec3_copy((vec3){-7.6f,0.0f,-0.25f},Door3Position);//E
        d1 = 'N';d2 = 'S';d3 = 'E';d4 = 'W';
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
    if (getKeyState(SDLK_o)){
        printf("D1 : %f, D2 : %f, D3 : %f\n",Door1Dist,Door2Dist,Door3Dist);
    }
    if (getKeyState(SDLK_f)){
        printf("D1 : %c, D2 : %c, D3 : %c,D4 : %c\n",d1,d2,d3,d4);
    }
    if (Door1Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }

        dj->change = true;
    }
    else if (Door2Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d3){
                dj->current_room = i;
                dj->direction = d4;
                break;
            }
        }
        dj->change = true;
    }else if (Door3Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime){
        for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d4){
                dj->current_room = i;
                dj->direction = d3;
                break;
            }
        }
        dj->change = true;
    }
}

void LogicRoom2L(Dungeon*dj,RigidBody* body){
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
    if (getKeyState(SDLK_o)){
        printf("D1 : %f, D2 : %f\n",Door1Dist,Door2Dist);
    }
    if (Door1Dist<0.5f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='S'||dj->adj[dj->current_room][i]=='N'){
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<0.5f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]=='E'||dj->adj[dj->current_room][i]=='W'){
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
}
void LogicRoom2I(Dungeon*dj,RigidBody* body){
    vec3 Door1Position;
    vec3 Door2Position;
    vec3 Door1Dir;
    vec3 Door2Dir;
    char d1='S';
    char d2='N';
    switch (dj->direction){
        case 'S': 
            glm_vec3_copy((vec3){0.0f,0.0f,-4.75f},Door1Position);//D1<=>S
            glm_vec3_copy((vec3){0.0f,0.0f,5.0f},Door2Position);//D2<=>N
            d1 = 'S';d2='N';
            break;
        case 'E': 
            glm_vec3_copy((vec3){-5.0f,0.0f,0.0f},Door1Position);//D1<=>E
            glm_vec3_copy((vec3){5.0f,0.0f,0.0f},Door2Position);//D2<=>W
            d1 = 'E';d2='W';
            break;
        case 'W': 
            glm_vec3_copy((vec3){-5.0f,0.0f,0.0f},Door1Position);//D1<=>E
            glm_vec3_copy((vec3){5.0f,0.0f,0.0f},Door2Position);//D2<=>W
            d1 = 'E';d2='W';
            break;
        case 'N': 
            glm_vec3_copy((vec3){0.0f,0.0f,-4.75f},Door1Position);
            glm_vec3_copy((vec3){0.0f,0.0f,5.0f},Door2Position);
            d1 = 'S';d2='N';
            break;
    }
    glm_vec3_sub( body->velocity, Door1Position, Door1Dir);
    glm_vec3_sub( body->velocity, Door2Position, Door2Dir);
    if (getKeyState(SDLK_f)){
            printf("D1 : %c, D2 : %c\n",d1,d2);
        }
    float Door1Dist = glm_vec3_norm(Door1Dir);
    float Door2Dist = glm_vec3_norm(Door2Dir);
    if (Door1Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d1){
                dj->current_room = i;
                dj->direction = d2;
                break;
            }
        }
        dj->change = true;
    }
    if (Door2Dist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]==d2){
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (getKeyState(SDLK_o)){
        printf("D1 = %f,D2 = %f\n",Door1Dist,Door2Dist);
    }
}
void LogicRoomB(Dungeon*dj,RigidBody* body ){
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
    glm_vec3_sub( body->velocity, DoorPosition, DoorDir);
    float DoorDist = glm_vec3_norm(DoorDir);
    if (DoorDist<1.0f&&playerInteract()&&(SDL_GetTicks()-dj->lastRoomChangeTime)>=ChangeTime ){
         for (int i =0;i<dj->nb_rooms;i++){
            if (dj->adj[dj->current_room][i]!='O'){
                dj->current_room = i;
                dj->direction = d1;
                break;
            }
        }
        dj->change = true;
    }
    if (getKeyState(SDLK_o)){
        printf("D1 = %f\n",DoorDist);
    }

}