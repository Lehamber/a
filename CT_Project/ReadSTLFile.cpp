#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include"ReadSTLFile.h"
#include <sstream>    

using namespace std;

bool ReadSTLFile::ReadFile(const char *cfilename)
{
	FILE * pFile;
	long lSize;
	char* buffer;
	size_t result;

	/* ��Ҫһ��byte��©�ض��������ļ���ֻ�ܲ��ö����Ʒ�ʽ�� */
	fopen_s(&pFile, cfilename, "rb");
	if (pFile == NULL)
	{
		return false;
	}

	/* ��ȡ�ļ���С */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* �����ڴ�洢�����ļ� */
	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		exit(2);
	}

	/* ���ļ�������buffer�� */
	result = fread(buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}


	/* ������ʾ���ر��ļ����ͷ��ڴ� */
	fclose(pFile);

	ios::sync_with_stdio(false);

	//������жϸ�ʽ�Ĵ���  ���Ʋ�̫�ԣ������Ƕ����Ƶ��ļ���������ֱ��ʹ���� ��ascii��ķ�ʽ�� ����ֱ���ö����ƶ���

	//if (buffer[79] != '\0')//�жϸ�ʽ   
	//{
	//	ReadASCII(buffer);
	//}
	//else
	//{
	//	ReadBinary(buffer);
	//}
	//���� ���� �ĳ�������stl�� �����Ƶ�������������Ͳ����ж��ˣ�ֱ��ֻ�ö����Ƶķ�ʽ������
	ReadBinary(buffer);
	ios::sync_with_stdio(true);

	free(buffer);
	return true;
}

bool ReadSTLFile::ReadASCII(const char *buffer)
{
	unTriangles = 0;
	float x, y, z;
	int i;
	string name, useless;
	stringstream ss(buffer);
	ss >> name >> name;
	ss.get();
	do {
		ss >> useless;
		if (useless != "facet")
			break;
		getline(ss, useless);
		getline(ss, useless);
		for (i = 0; i < 3; i++)
		{
			ss >> useless >> x >> y >> z;
			pointList.push_back(QVector3D(x, y, z));
		}
		unTriangles++;
		getline(ss, useless);
		getline(ss, useless);
		getline(ss, useless);
	} while (1);
	return true;
}

bool ReadSTLFile::ReadBinary(const char *buffer)
{
	const char* p = buffer;
	char name[80];
	int i, j;
	memcpy(name, p, 80);
	p += 80;
	unTriangles = cpyint(p);

	const char *tempP;
	for (i = 0; i < unTriangles; i++)
	{
		vectorList.push_back(QVector3D(cpyfloat(p), cpyfloat(p), cpyfloat(p)));//��ȡ ����Ƭ���������Ϣ
		for (j = 0; j < 3; j++)//��ȡ������
		{
			pointList.push_back(QVector3D(cpyfloat(p), cpyfloat(p), cpyfloat(p)));
		}
		p += 2;//����β����־
	}
	return true;
}

int ReadSTLFile::NumTri()
{
	return unTriangles;
}

vector<QVector3D> ReadSTLFile::getPointList()// ��ȡ������
{
	return pointList;
}
vector<QVector3D> ReadSTLFile::getVectorList()// ��ȡ����Ƭ�� ��������
{
	return vectorList;
}

int ReadSTLFile::cpyint(const char*& p)
{
	int cpy;
	char byte[4];
	for (int i = 0; i < 4; i++)
	{
		byte[i] = *p;
		p++;
	}
	cpy = *(int*)byte;
	//memwriter = (char*)&cpy;
	//memcpy(memwriter, p, 4);
	//p += 4;
	return cpy;
}
float ReadSTLFile::cpyfloat(const char*& p)
{
	float cpy;
	char byte[4];
	for (int i = 0; i < 4; i++)
	{
		byte[i] = *p;
		p++;
	}
	cpy = *(float*)byte;
	/*memwriter = (char*)&cpy;
	memcpy(memwriter, p, 4);
	p += 4;*/
	return cpy;
}
