#pragma once

#include "BlenderModelIntreface.h"
#include "ModelBase.h"
#include "string"
#include "iostream"

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags



class BlenderModel :  public ModelBase
{
public:
    BlenderModel(std::string modelName) {
        this->indicesCount = 0;
        this->VAO = 0;

		this->load(modelName);
    }

	~BlenderModel() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
	}
    void bind() {
        glBindVertexArray(VAO);
    }

    void unbind() {
        glBindVertexArray(0);
    }

    GLenum getShapeType() const {
        return 0;
        //return shapeType;
    }
    int getFirst() const {
        return 0;
        //return first;
    }
    int getCount() const {
        return 0;
        //return count;
    }

    int getIndiciesCount() {
		return indicesCount;
    }

    void load(std::string filename) {
        {
            Assimp::Importer importer;
            unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
                | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
                | aiProcess_JoinIdenticalVertices       // Removes duplicate vertices
                | aiProcess_CalcTangentSpace;           // Computes tangents and bitangents

            //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals

            const aiScene* scene = importer.ReadFile(filename, importOptions);

            if (scene) { //pokud bylo nacteni uspesne
                printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
                printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
                //Materials
                for (unsigned int i = 0; i < scene->mNumMaterials; i++)
                {
                    const aiMaterial* mat = scene->mMaterials[i];
                    aiString name;
                    mat->Get(AI_MATKEY_NAME, name);
                    printf("Material [%d] name %s\n", i, name.C_Str());
                    aiColor4D d;
                    glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
                    if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                        diffuse = glm::vec4(d.r, d.g, d.b, d.a);
                }
                //Objects
                for (unsigned int i = 0; i < scene->mNumMeshes; i++)
                {
                    aiMesh* mesh = scene->mMeshes[i];
                    Vertex* pVertices = new Vertex[mesh->mNumVertices];
                    std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
                    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
                    {
                        if (mesh->HasPositions()) {
                            pVertices[i].Position[0] = mesh->mVertices[i].x;
                            pVertices[i].Position[1] = mesh->mVertices[i].y;
                            pVertices[i].Position[2] = mesh->mVertices[i].z;
                        }

                        if (mesh->HasNormals()) {
                            pVertices[i].Normal[0] = mesh->mNormals[i].x;
                            pVertices[i].Normal[1] = mesh->mNormals[i].y;
                            pVertices[i].Normal[2] = mesh->mNormals[i].z;
                        }

                        if (mesh->HasTextureCoords(0)) {
                            pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                            pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                        }

                        if (mesh->HasTangentsAndBitangents()) {
                            pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                            pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                            pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                        }
                    }

                    unsigned int* pIndices = nullptr;
                    if (mesh->HasFaces()) {
                        pIndices = new unsigned int[mesh->mNumFaces * 3];
                        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                            pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                            pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                            pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                        }
                    }

                    glGenVertexArrays(1, &VAO);

                    GLuint VBO = 0;
                    glGenBuffers(1, &VBO);

                    GLuint IBO = 0;
                    glGenBuffers(1, &IBO);

                    glBindVertexArray(VAO);
                    glBindBuffer(GL_ARRAY_BUFFER, VBO);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
                    glEnableVertexAttribArray(2);
                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

                    //Tangent for Normal Map
                    glEnableVertexAttribArray(3);
                    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

                    //Index Buffer
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    glBindVertexArray(VAO);

                    GLuint err = glGetError();
                    if (err != GL_NO_ERROR) {
                        std::cout << "GL ERROR: " << err << std::endl;
                        exit(0);
                    }
                    indicesCount = mesh->mNumFaces * 3;
                    delete[] pVertices;
                    delete[] pIndices;
                }
            }
            else {
                exit(0);
                printf("Error during parsing mesh from %s : %s \n", filename.c_str(), importer.GetErrorString());
            }
            glBindVertexArray(0);
        }
    }


    private:
        GLuint VBO, VAO;

        GLenum shapeType;
        int first;
        int count;

        struct Vertex
        {
            float Position[3];
            float Normal[3];
            float Texture[2];
            float Tangent[3];
        };

        int indicesCount;

};
