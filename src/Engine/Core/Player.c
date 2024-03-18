//
// Created by Victor Davillé on 14/03/2024.
//

#include "Player.h"

Player* player_create(char* objPath, char* texturePath, Camera* camera, vec3 position, vec3 rotation, vec3 scale, float speed, float rotationSpeed) {
    Player* player = malloc(sizeof(Player));
    Obj obj = loadObj(objPath);
    player->model = mesh_create(obj.vertices, obj.uvs, obj.normals, (GLuint*)obj.indices, obj.numVertices, obj.numIndices);
    load_textures(player->model, texturePath);
    player->camera = camera;
    for (int i =0; i < 3; i++) {
        player->position[i] = position[i];
        player->rotation[i] = rotation[i];
        player->scale[i] = scale[i];
    }
    player->speed = speed;
    player->rotationSpeed = rotationSpeed;
    return player;
}

void player_update(Player* player, Time* time, Game* game) {
    (void)game;
    (void)time;
    (void)player;
}

void player_render(Player* player, Game* game) {
    mesh_draw(player->model, game->shader, player->camera, game->time);
}
