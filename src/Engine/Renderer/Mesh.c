#include <Mesh.h>

Mesh* MeshCreate(struct aiMesh* aiMesh){

    /* Read data from assimp mesh */
    const size_t vertexCount = aiMesh->mNumVertices;
    const size_t faceCount = aiMesh->mNumFaces;
    size_t indexCount = 0;

    /* Initialize all Mesh's member */
    Mesh *mesh = calloc(1, sizeof(Mesh));
    mesh->vertices = calloc(vertexCount, sizeof(Vertex));
    mesh->indices = NULL;
    mesh->vertexCount = vertexCount;
    mesh->indiceCount = 0;
    mesh->matID = aiMesh->mMaterialIndex;

    /* For each vertex we copy the data into our struct */
    for(size_t i = 0; i< vertexCount; ++i){

        /* Posiiton always present in a mesh */
        mesh->vertices[i].Position[0] = aiMesh->mVertices[i].x;
        mesh->vertices[i].Position[1] = aiMesh->mVertices[i].y;
        mesh->vertices[i].Position[2] = aiMesh->mVertices[i].z;
        /* Check if we have textures and copy data */
        if(aiMesh->mTextureCoords[0]){
            mesh->vertices[i].TexCoords[0] = aiMesh->mTextureCoords[0][i].x;
            mesh->vertices[i].TexCoords[1] = aiMesh->mTextureCoords[0][i].y;
        }
        /* Check if we have normals and copy data */
        if(aiMesh->mNormals){
            mesh->vertices[i].Normal[0] = aiMesh->mNormals[i].x;
            mesh->vertices[i].Normal[1] = aiMesh->mNormals[i].y;
            mesh->vertices[i].Normal[2] = aiMesh->mNormals[i].z;
        }
    }

    /* Counting number of indices present in the mesh */
    for(size_t i=0; i<faceCount; ++i){
        indexCount += aiMesh->mFaces[i].mNumIndices;
    }
    /* Copy all indices in the right order */
    mesh->indiceCount = indexCount;
    mesh->indices = calloc(indexCount, sizeof(unsigned int));
    {
        size_t iter = 0;
        for(size_t i=0; i<faceCount; ++i)
            for(size_t j=0; j<aiMesh->mFaces[i].mNumIndices; ++j)
                mesh->indices[iter++] = aiMesh->mFaces[i].mIndices[j];
    }

    /* We are ready to wrap data into GL buffers */
    MeshSetup(mesh);

    return mesh;
}

void MeshSetup(Mesh* mesh){

    /* Generate GL buffers */
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    /* We want to bind VAO to link every buffers to this object*/
    glBindVertexArray( mesh->VAO);

    /* Processing VBO */
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertexCount * sizeof(Vertex), mesh->vertices, GL_STATIC_DRAW);
    /* Position attribute*/
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    /* Texture Coordinates attribute*/
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    /* Normals attribute */
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    /* Processing EBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indiceCount * sizeof(unsigned int), mesh->indices, GL_STATIC_DRAW);

    /* Unbind our VAO to prevent the overriding of our buffers */
    glBindVertexArray(0);
}

void MeshDraw(Mesh* mesh) {
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indiceCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
