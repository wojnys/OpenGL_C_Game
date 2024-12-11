//#include "Texture.h"
//#include <iostream>
//#include <SOIL.h>
//
//Texture::Texture(const char* texturePath, int textureUnitNumber) : filePath(texturePath)  {
//
//    this->textureUnitNumber = textureUnitNumber;
//    //Texture one in texture unit 1,2,3,4,5...
//    glActiveTexture(GL_TEXTURE0 + this->textureUnitNumber);
//    textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
//    if (textureID == NULL) {
//        std::cout << "An error occurred while loading texture." << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//
//
//    ///////
//    //    //Textures - Albedo
//    //glActiveTexture(GL_TEXTURE0 + this->textureUnitNumber);
//    //textureID = SOIL_load_OGL_cubemap("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
//    //if (textureID == NULL) {
//    //    std::cout << "An error occurred while loading CubeMap." << std::endl;
//    //    exit(EXIT_FAILURE);
//    //}
//    ////glBindTexture(GL_TEXTURE_2D, textureID);
//    //glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
//}
//
//Texture::~Texture() {
//    glDeleteTextures(1, &textureID);
//}
//
//void Texture::bind(GLenum textureUnit) const {
// /*   glActiveTexture(textureUnit);
//    glBindTexture(GL_TEXTURE_2D, textureID);*/
//}
//
//void Texture::unbind() const {
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
