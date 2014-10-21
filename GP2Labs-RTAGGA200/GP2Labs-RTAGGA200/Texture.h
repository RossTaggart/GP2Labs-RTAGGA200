#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

GLuint loadTextureFromFile(const std::string& filename);
GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text);
GLuint convertSDLSurfaceToGLTexture(SDL_Surface *surface);

#endif