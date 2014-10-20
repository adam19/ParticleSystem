#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <fstream>
#include <string>

using namespace std;

class Shader
{
private:
	unsigned int vertId;
	unsigned int geomId;
	unsigned int fragId;


public:
	unsigned int progId;

	// Consolidate these into a HashMap
	unsigned int projMatrixLocation;
	unsigned int viewMatrixLocation;
	unsigned int modelMatrixLocation;

	Shader()
	{
		progId = 0;
		vertId = 0;
		geomId = 0;
		fragId = 0;
	}

	Shader(char* vertShader, char* fragShader)
	{
		Init(vertShader, fragShader);
	}

	~Shader() 
	{
		if (progId > 0)
		{
			glDetachShader(progId, fragId);
			glDetachShader(progId, vertId);
		}

		if (fragId > 0)
			glDeleteShader(fragId);
		if (geomId > 0)
			glDeleteShader(geomId);
		if (vertId > 0)
			glDeleteShader(vertId);
		if (progId > 0)
			glDeleteShader(progId);
	}

	void Init(char* vertShader, char* fragShader)
	{
		const GLchar* vtext = ReadFile(vertShader);
		const GLchar* ftext = ReadFile(fragShader);

		vertId = glCreateShader(GL_VERTEX_SHADER);
		fragId = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertId, 1, (const GLchar**)&vtext, 0);
		glShaderSource(fragId, 1, (const GLchar**)&ftext, 0);

		glCompileShader(vertId);
		ValidateShader(vertId, vertShader);
		glCompileShader(fragId);
		ValidateShader(fragId, fragShader);

		progId = glCreateProgram();
		glAttachShader(progId, vertId);
		glAttachShader(progId, fragId);
		glLinkProgram(progId);
		ValidateProgram(progId);

		// may not need to be here
		glBindAttribLocation(vertId, 0, "in_Position");
		glBindAttribLocation(vertId, 1, "out_Color");
	}

	void Init(char* vertShader, char* geomShader, char* fragShader)
	{		
		const GLchar* vtext = ReadFile(vertShader);
		const GLchar* gtext = ReadFile(geomShader);
		const GLchar* ftext = ReadFile(fragShader);

		vertId = glCreateShader(GL_VERTEX_SHADER);
		geomId = glCreateShader(GL_GEOMETRY_SHADER);
		fragId = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertId, 1, (const GLchar**)&vtext, 0);
		glShaderSource(geomId, 1, (const GLchar**)&gtext, 0);
		glShaderSource(fragId, 1, (const GLchar**)&ftext, 0);

		glCompileShader(vertId);
		ValidateShader(vertId, vertShader);
		glCompileShader(geomId);
		ValidateShader(geomId, geomShader);
		glCompileShader(fragId);
		ValidateShader(fragId, fragShader);

		progId = glCreateProgram();
		glAttachShader(progId, vertId);
		glAttachShader(progId, geomId);
		glAttachShader(progId, fragId);
		glLinkProgram(progId);
		ValidateProgram(progId);

		// may not need to be here
		glBindAttribLocation(vertId, 0, "in_Position");
		glBindAttribLocation(vertId, 1, "out_Color");
	}

	static void ValidateShader(GLuint shader, const char* file = 0)
	{
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		GLsizei length = 0;	
		memset((char*)buffer, 0, sizeof(char)*BUFFER_SIZE);

		glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

		if (length > 0)
			cout << "Shader " << shader << "(" << (file ? file:"") << ") compile error." << buffer << endl;
	}

	static void ValidateProgram(GLuint program)
	{
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		GLsizei length = 0;	
		memset((char*)buffer, 0, sizeof(char)*BUFFER_SIZE);

		glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

		if (length > 0)
			cout << "Program " << program << " link error." << buffer << endl;

		glValidateProgram(program);
		int status;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

		if (status == GL_FALSE)
			cout << "Error validating shader\n";
	}

	void Bind()
	{
		glUseProgram(progId);
	}

	void UnBind()
	{
		glUseProgram(0);
	}

private:
	char* ReadFile(char* filename)
	{
		char* text = "";
    
		if (filename != NULL) {
			FILE *file;

			if (fopen_s(&file, filename, "rt") != 0)
				return NULL;
        
			if (file != NULL) {
				fseek(file, 0, SEEK_END);
				int count = ftell(file);
				rewind(file);
            
				if (count > 0) {
					text = (char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
				}
				fclose(file);
			}
		}
		return text;
	}
};

#endif