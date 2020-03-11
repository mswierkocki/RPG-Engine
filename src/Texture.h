#pragma once

#include <string>

#include "GL/glfw.h" // Usually necessary where you'd need a texture.
#define GL_CLAMP_TO_EDGE 0x812F


class Texture
{
public:
	const char* file;		// Texture Image Source Filename
	GLuint	texID;			// Texture ID Used To Select A Texture
	GLuint	width;			// Image Width
	GLuint	height;			// Image Height
	GLuint	channels;		// Image Color Depth As 8-bit Channels Count

public:
	Texture(std::string filename = "");

	bool Load(std::string filename);
};
