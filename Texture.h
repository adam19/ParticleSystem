#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#ifndef __GLEW_H__
#include <GL/glew.h>
#pragma comment(lib, "glew32.lib")
#endif

#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>

#pragma comment(lib, "lib/DevIL.lib")
#pragma comment(lib, "lib/ILU.lib")
#pragma comment(lib, "lib/ILUT.lib")

#include <string>

using namespace std;

class Texture
{
public:
	GLuint id;
	string filename;

	long width;	
	long height;

	int bpp;			//bits per pixel

	Texture();
	Texture(string f);
	~Texture();

	void	operator =(Texture t);
	bool	operator ==(Texture t);
};


//void InitTexture();
void BuildTexture(char *filename, GLuint &texid);
void BuildTexture(char *filename, Texture &tex);
void BuildCubeMap(char *filename, GLuint &texid);

#endif