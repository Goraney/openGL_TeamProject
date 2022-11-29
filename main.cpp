#include "shader.h"
#include "GameFramework.h"

void InitBuffer();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);


GLuint VAO, VBO_position, VBO_color;

// �ﰢ�� ������ ��ǥ��
const GLfloat triShape[3][3] =
{
	{-0.5,-0.5, 0.0 },
	{ 0.5,-0.5, 0.0 },
	{ 0.0, 0.5, 0.0 }
};

// �ﰢ�� ������ ����
const GLfloat colors[3][3] =
{
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 }
};

int polygon_mode = 2;


void main(int argc, char** argv)
{
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(triShape), triShape, GL_STATIC_DRAW);	//--- vertex positions ������ �Է�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glEnableVertexAttribArray(0);												//--- attribute �ε��� 0���� ��밡���ϰ� ��

	glGenBuffers(1, &VBO_color);												//--- VBO color ��ü ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);									//--- vertex colors ������ ���� VBO ���ε�
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);		//--- vertex colors ������ �Է�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glEnableVertexAttribArray(1);												//--- attribute �ε��� 0���� ��밡���ϰ� ��
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