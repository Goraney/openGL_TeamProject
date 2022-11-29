#pragma once
#include "FileReader.h"

GLuint shaderProgramID;		//--- ���̴� ���α׷� �̸�


void CheckCompileError(unsigned int shader, string type);
int make_vertexShaders(const char* filename);
int make_fragmentShaders(const char* filename);
void InitShader(const char* vertex_filename, const char* fragment_filename);


void CheckCompileError(unsigned int shader, string type)
{
	GLint result;
	GLchar errorLog[512];

	if (type != "program")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			glGetShaderInfoLog(shader, 512, NULL, errorLog);
			std::cerr << "ERROR: " << type << " shader ������ ����\n" << errorLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &result);	// ---���̴��� �� ����Ǿ����� üũ�ϱ�

		if (!result) {
			glGetProgramInfoLog(shader, 512, NULL, errorLog);
			std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		}
	}
}

//--- ���ؽ� ���̴� ��ü �����
int make_vertexShaders(const char* filename)
{
	int vertexShader;		//--- ���ؽ� ���̴� ��ü
	char* vertexSource;

	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	vertexSource = filetoChar(filename);					// ���̴����� �о����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);			// ���̴� ��ü ����
	glShaderSource(vertexShader, 1, &vertexSource, NULL);		// ���̴� �ڵ� �о����
	glCompileShader(vertexShader);								// ���̴� ������

	CheckCompileError(vertexShader, "vertex");

	return vertexShader;
}

//--- �����׸�Ʈ ���̴� ��ü �����
int make_fragmentShaders(const char* filename)
{
	int fragmentShader;		//--- �����׸�Ʈ ���̴� ��ü
	char* fragmentSource;

	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetoChar(filename);				// ���̴����� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// ���̴� ��ü ����
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);	// ���̴� �ڵ� �о����
	glCompileShader(fragmentShader);							// ���̴� ������

	CheckCompileError(fragmentShader, "fragment");

	return fragmentShader;
}

//--- ���̴� ���α׷� �����
void InitShader(const char* vertex_filename, const char* fragment_filename)
{
	GLuint vertexShader = make_vertexShaders(vertex_filename);			//--- ���ؽ� ���̴� �����
	GLuint fragmentShader = make_fragmentShaders(fragment_filename);	//--- �����׸�Ʈ ���̴� �����

	shaderProgramID = glCreateProgram();			//--- ���̴� ���α׷� �����

	glAttachShader(shaderProgramID, vertexShader);	//--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�
	glAttachShader(shaderProgramID, fragmentShader);//--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�

	glLinkProgram(shaderProgramID);					//--- ���̴� ���α׷� ��ũ�ϱ�

	glDeleteShader(vertexShader);					//--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������,
	glDeleteShader(fragmentShader);					//--- ���̴� ��ü ��ü�� ���� ����

	CheckCompileError(shaderProgramID, "program");

	glUseProgram(shaderProgramID);	//--- ������� ���̴� ���α׷� ����ϱ�
									//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
									//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
									//--- ����ϱ� ������ ȣ���� �� �ִ�.
}
