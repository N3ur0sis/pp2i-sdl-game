#include "DungeonTest.h"

void test_dj_create(void) {
    Dungeon* dj = dj_create();
    CU_ASSERT_PTR_NOT_NULL(dj);
    CU_ASSERT_PTR_NOT_NULL(dj->rooms);
    CU_ASSERT_PTR_NOT_NULL(dj->adj);
    CU_ASSERT_EQUAL(dj->current_room, 0);
    CU_ASSERT_EQUAL(dj->previous_room, 0);
    CU_ASSERT_EQUAL(dj->direction, 'S');
    CU_ASSERT_EQUAL(dj->previous_direction, 'S');
    CU_ASSERT_TRUE(dj->change);
    CU_ASSERT_FALSE(dj->hasKey);
    CU_ASSERT_EQUAL(dj->nb_enemy, 0);
    CU_ASSERT_FALSE(dj->quit);
    CU_ASSERT_EQUAL(dj->lastRoomChangeTime, 0.0f);
}

void test_initializeAdjacencyList(void) {
    Dungeon *dj = malloc(sizeof(Dungeon));
    dj->nb_rooms = 5;  // Exemple de nombre de salles
    initializeAdjacencyList(dj);
    for (int i = 0; i < dj->nb_rooms; i++) {
        CU_ASSERT_PTR_NOT_NULL(dj->adj[i]);
        for (int j = 0; j < dj->nb_rooms; j++) {
            CU_ASSERT_EQUAL(dj->adj[i][j], 'O');
        }
        CU_ASSERT_EQUAL(dj->adj[i][dj->nb_rooms], '\0');
    }
}