#include "shader.h"
#include "GameFramework.h"
#include "ObjReader.h"

void InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);

GameFramework gameframework;

GLuint VAO, VBO_position, VBO_normal;

objRead obj;

int polygon_mode = 1;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void main(int argc, char** argv)
{
	obj.loadObj_normalize_center("pyramid.obj");

	gameframework.OnCreate();

	// 윈도우 생성
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example 6");

	// 윈도우 초기화
	glewExperimental = GL_TRUE;
	glewInit();

	//--- 세이더 읽어와서 세이더 프로그램 만들기	
	InitShader("vertex.glsl", "fragment.glsl");
	InitBuffer();

	// 콜백 함수들
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 메인 루프
	glutMainLoop();
}

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);			//--- VAO 객체 생성
	glBindVertexArray(VAO);				//--- 사용할 VAO 바인딩

	glGenBuffers(1, &VBO_position);												//--- VBO position 객체 생성
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);								//--- vertex positions 저장을 위한 VBO 바인딩
	glBufferData(GL_ARRAY_BUFFER, obj.outvertex.size() * sizeof(glm::vec3),&obj.outvertex[0], GL_STATIC_DRAW);	//--- vertex positions 데이터 입력
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(0);												//--- attribute 인덱스 0번을 사용가능하게 함

	glGenBuffers(1, &VBO_normal);												//--- VBO position 객체 생성
	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);								//--- vertex positions 저장을 위한 VBO 바인딩
	glBufferData(GL_ARRAY_BUFFER, obj.outnormal.size() * sizeof(glm::vec3), &obj.outnormal[0], GL_STATIC_DRAW);	//--- vertex positions 데이터 입력
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(0);
}

GLvoid drawScene()
{
	GLfloat rColor = 0.1f, gColor = 0.1f, bColor = 0.1f;

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	if (polygon_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (polygon_mode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgramID);
	
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(gameframework.player->Get_worldTR()));

	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objColor");
	glUniform3f(objColorLocation, 0.8,0.8,0.8);

	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);

	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(viewPosLocation, cameraPos.x,cameraPos.y,cameraPos.z);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, obj.outvertex.size());

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': case 'W': //Advance
		gameframework.player->Translate(glm::vec3(0.0f, 0.0f, -0.5f));
		break;
	case 's': case 'S': //backwards
		gameframework.player->Translate(glm::vec3(0.0f, 0.0f, 0.5f));
		break;
	case 'a': case 'A': //Rotate left
		gameframework.player->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 20);
		break;
	case 'd': case 'D': //Rotate right
		gameframework.player->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), -20);
		break;
	case 'i': case 'I':
		cameraPos[2] -= 0.2;
		cameraDirection[2] -= 0.2;
		break;
	case 'k': case 'K':
		cameraPos[2] += 0.2;
		cameraDirection[2] += 0.2;
		break;
	case 'j': case 'J':
		cameraPos[0] -= 0.2;
		cameraDirection[0] -= 0.2;
		break;
	case 'l': case 'L':
		cameraPos[0] += 0.2;
		cameraDirection[0] += 0.2;
		break;
	case 'n': case 'N':
		cameraPos[1] += 0.2;
		cameraDirection[1] += 0.2;
		break;
	case 'm': case 'M':
		cameraPos[1] -= 0.2;
		cameraDirection[1] -= 0.2;
		break;
	}

	glutPostRedisplay();
}

void Special(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_UP:
		cameraDirection[1] += 0.2;
		break;
	case GLUT_KEY_DOWN:
		cameraDirection[1] -= 0.2;
		break;
	case GLUT_KEY_LEFT:
		cameraDirection[0] -= 0.2;
		break;
	case GLUT_KEY_RIGHT:
		cameraDirection[0] += 0.2;
		break;
	}

	glutPostRedisplay();
}