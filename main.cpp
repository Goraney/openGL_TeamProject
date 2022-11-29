#include "shader.h"
#include "GameFramework.h"

void InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);


GLuint VAO, VBO_position, VBO_color;

// 삼각형 꼭지점 좌표값
const GLfloat triShape[3][3] =
{
	{-0.5,-0.5, 0.0 },
	{ 0.5,-0.5, 0.0 },
	{ 0.0, 0.5, 0.0 }
};

// 삼각형 꼭지점 색상
const GLfloat colors[3][3] =
{
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 }
};

int polygon_mode = 2;


void main(int argc, char** argv)
{
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_STATIC_DRAW);	//--- vertex positions 데이터 입력
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(0);												//--- attribute 인덱스 0번을 사용가능하게 함

	glGenBuffers(1, &VBO_color);												//--- VBO color 객체 생성
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);									//--- vertex colors 저장을 위한 VBO 바인딩
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);		//--- vertex colors 데이터 입력
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(1);												//--- attribute 인덱스 0번을 사용가능하게 함
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
	if (key == '1')
		polygon_mode = 1;
	else if (key == '2')
		polygon_mode = 2;

	glutPostRedisplay();
}