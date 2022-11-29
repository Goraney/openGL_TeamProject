#pragma once
#include "FileReader.h"

GLuint shaderProgramID;		//--- 세이더 프로그램 이름


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
			std::cerr << "ERROR: " << type << " shader 컴파일 실패\n" << errorLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &result);	// ---세이더가 잘 연결되었는지 체크하기

		if (!result) {
			glGetProgramInfoLog(shader, 512, NULL, errorLog);
			std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		}
	}
}

//--- 버텍스 세이더 객체 만들기
int make_vertexShaders(const char* filename)
{
	int vertexShader;		//--- 버텍스 세이더 객체
	char* vertexSource;

	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	vertexSource = filetoChar(filename);					// 셰이더파일 읽어오기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);			// 셰이더 객체 생성
	glShaderSource(vertexShader, 1, &vertexSource, NULL);		// 셰이더 코드 읽어오기
	glCompileShader(vertexShader);								// 셰이더 컴파일

	CheckCompileError(vertexShader, "vertex");

	return vertexShader;
}

//--- 프래그먼트 세이더 객체 만들기
int make_fragmentShaders(const char* filename)
{
	int fragmentShader;		//--- 프래그먼트 세이더 객체
	char* fragmentSource;

	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetoChar(filename);				// 셰이더파일 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// 셰이더 객체 생성
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);	// 셰이더 코드 읽어오기
	glCompileShader(fragmentShader);							// 셰이더 컴파일

	CheckCompileError(fragmentShader, "fragment");

	return fragmentShader;
}

//--- 세이더 프로그램 만들기
void InitShader(const char* vertex_filename, const char* fragment_filename)
{
	GLuint vertexShader = make_vertexShaders(vertex_filename);			//--- 버텍스 세이더 만들기
	GLuint fragmentShader = make_fragmentShaders(fragment_filename);	//--- 프래그먼트 세이더 만들기

	shaderProgramID = glCreateProgram();			//--- 세이더 프로그램 만들기

	glAttachShader(shaderProgramID, vertexShader);	//--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(shaderProgramID, fragmentShader);//--- 세이더 프로그램에 프래그먼트 세이더 붙이기

	glLinkProgram(shaderProgramID);					//--- 세이더 프로그램 링크하기

	glDeleteShader(vertexShader);					//--- 세이더 객체를 세이더 프로그램에 링크했음으로,
	glDeleteShader(fragmentShader);					//--- 세이더 객체 자체는 삭제 가능

	CheckCompileError(shaderProgramID, "program");

	glUseProgram(shaderProgramID);	//--- 만들어진 세이더 프로그램 사용하기
									//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
									//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
									//--- 사용하기 직전에 호출할 수 있다.
}
