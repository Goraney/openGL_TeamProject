#pragma once
#include "stdafx.h"

//--- �ؽ�Ʈ �о� ���ڿ��� �����ϴ� �Լ�
char* filetoChar(const char* filename)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(filename, "rb");

	if (!fptr)
		return NULL;

	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	cout << length << endl;

	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);

	fclose(fptr);

	buf[length] = 0;

	return buf;
}

//--- �ؽ�Ʈ �о� string�� �����ϴ� �Լ�
string filetoString(const char* filename)
{
	string str;
	ifstream read_file;
	stringstream stream;

	read_file.open(filename);

	stream << read_file.rdbuf();

	read_file.close();

	str = stream.str();

	return str;
}
