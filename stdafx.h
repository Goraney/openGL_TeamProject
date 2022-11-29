#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

// openGL
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

// + ��ǥ�� ��ȯ ������ ��
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

// �⺻���� �͵�
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

#define WIDTH 800
#define HEIGHT 600