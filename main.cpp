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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- ī�޶� ��ġ
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float rotate_degree = 0.0f;
float t_x{ 0.0 }, t_y{ 0.0 }, t_z{ 0.0 };

void main(int argc, char** argv)
{
	obj.loadObj_normalize_center("pyramid.obj");

	// ������ ����
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example 6");

	// ������ �ʱ�ȭ
	glewExperimental = GL_TRUE;
	glewInit();

	//--- ���̴� �о�ͼ� ���̴� ���α׷� �����	
	InitShader("vertex.glsl", "fragment.glsl");
	InitBuffer();

	// �ݹ� �Լ���
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ���� ����
	glutMainLoop();
}

void InitBuffer()
{
	glGenVertexArrays(1, &VAO);			//--- VAO ��ü ����
	glBindVertexArray(VAO);				//--- ����� VAO ���ε�

	glGenBuffers(1, &VBO_position);												//--- VBO position ��ü ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);								//--- vertex positions ������ ���� VBO ���ε�
	glBufferData(GL_ARRAY_BUFFER, obj.outvertex.size() * sizeof(glm::vec3),&obj.outvertex[0], GL_STATIC_DRAW);	//--- vertex positions ������ �Է�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glEnableVertexAttribArray(0);												//--- attribute �ε��� 0���� ��밡���ϰ� ��
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

	//--- ������ �𵨸� ��ȯ ��� �����
	//model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f)); //--- model ��Ŀ� �̵� ��ȯ ����
	//--- ���̴� ���α׷����� modelTransform ���� ��ġ ��������
	//unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform");
	//--- modelTransform ������ ��ȯ �� �����ϱ�
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- ������ �ణ �ڷ� �̷���
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- ���� ��ȯ �� ����
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