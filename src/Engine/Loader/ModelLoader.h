//
// Created by Victor Davillé on 20/02/2024.
//

#ifndef PP2I_MODELLOADER_H
#define PP2I_MODELLOADER_H

#include <stdbool.h>
#include "../../DataStructures/Vector.h"

bool ModelLoader(char* path, Vector** vertices, Vector** normals, Vector** uvs, Vector** indices);

#endif //PP2I_MODELLOADER_H
