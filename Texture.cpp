#include <olectl.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "Texture.h"

Texture::Texture()
{
	filename = "";
	id = -1;
	width = height = 0;
}

Texture::Texture(string f)
{
	filename = f;
	id = -1;
	width = height = 0;
}

Texture::~Texture()
{}

void Texture::operator=(Texture tex)
{
	memcpy(this, &tex, sizeof(Texture));
}

bool Texture::operator ==(Texture t)
{
	if(t.bpp == this->bpp && t.filename == this->filename && t.height == this->height &&
		t.id == this->id && t.width == this->width)
	{
		return true;
	}

	return false;
}

void BuildCubeMap(char *filename, GLuint &texid)
{
	if(!filename)
		return;

	ILuint handle;
	ilGenImages(1, &handle);
	ilBindImage(handle);
	
	glGenTextures(1, &texid);

	for (int i=0; i<6; i++)
	{
		char fname[256];
		switch (i)
		{
		case 0:
			sprintf_s(fname, "%s-px.png", filename);
			break;
		case 1:
			sprintf_s(fname, "%s-nx.png", filename);
			break;
		case 2:
			sprintf_s(fname, "%s-py.png", filename);
			break;
		case 3:
			sprintf_s(fname, "%s-ny.png", filename);
			break;
		case 4:
			sprintf_s(fname, "%s-pz.png", filename);
			break;
		case 5:
			sprintf_s(fname, "%s-nz.png", filename);
			break;
		}
		printf("filename: %s\n", fname);


		if(ilLoadImage(fname) == IL_FALSE)
		{
			texid = -1;
			return;
		}

		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int len = width * height;
		int bpp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		int format;
	
		ilEnable(IL_ORIGIN_SET);
		ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);	
		BYTE* data = new BYTE[width * height * (bpp / 8)];

		if(bpp == 32)
		{
			format = GL_RGBA;
			ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);
		}
		else
		{
			format = GL_RGB;
			ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
		}
		ilDeleteImages(1, &handle);
		
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
		glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, texid);
		for (int i=0; i<6; i++) { 
		  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, 
			0,
			GL_RGB8,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			&data);
		}

		free(data);
	}
}

void BuildTexture(char *filename, GLuint &texid)
{
	if(!filename)
		return;

	ILuint handle;
	ilGenImages(1, &handle);
	ilBindImage(handle);
	
	if(ilLoadImage(filename) == IL_FALSE)
	{
		texid = -1;
		return;
	}

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int len = width * height;
	int bpp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	int format;
	
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);	
	BYTE* data = new BYTE[width * height * (bpp / 8)];

	if(bpp == 32)
	{
		format = GL_RGBA;
		ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);
	}
	else
	{
		format = GL_RGB;
		ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, data);
	}
	ilDeleteImages(1, &handle);

	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data);

	delete[] data;
}

void BuildTexture(char *filename, Texture &tex)
{
	BuildTexture(filename, tex.id);
}