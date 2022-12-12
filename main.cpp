#include "shader.h"
#include "GameFramework.h"
#include "ObjReader.h"

void InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);


GLuint VAO, VBO_position, VBO_color;

objRead obj;

int polygon_mode = 1;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float rotate_degree = 0.0f;
float t_x{ 0.0 }, t_y{ 0.0 }, t_z{ 0.0 };

void main(int argc, char** argv)
{
	obj.loadObj_normalize_center("pyramid.obj");

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
}

GLvoid drawScene()
{
	GLfloat rColor = 1.0f, gColor = 1.0f, bColor = 1.0f;

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	if (polygon_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (polygon_mode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgramID);
	//glm::mat4 model = glm::mat4(1.0f);

	//--- 적용할 모델링 변환 행렬 만들기
	//model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f)); //--- model 행렬에 이동 변환 적용
	//--- 세이더 프로그램에서 modelTransform 변수 위치 가져오기
	//unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	//--- modelTransform 변수에 변환 값 적용하기
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Sc = glm::mat4(1.0f);
	glm::mat4 Tr = glm::mat4(1.0f);

	Ry = glm::rotate(Ry, glm::radians(rotate_degree), glm::vec3(0.0, 1.0, 0.0));
	Tr = glm::translate(Tr, glm::vec3(t_x, t_y, t_z));
	Sc = glm::scale(Sc, glm::vec3(1.0, 1.0, 1.0));

	TR = Tr * Ry;
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
		break;
	case 's': case 'S': //backwards
		break;
	case 'a': case 'A': //Rotate left
		break;
	case 'd': case 'D': //Rotate right
		break;
	}

	glutPostRedisplay();
}