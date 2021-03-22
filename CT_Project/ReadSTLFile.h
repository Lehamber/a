#pragma once
#include <vector>
#include <QVector3D>

using namespace std;

class ReadSTLFile
{
public:
	bool ReadFile(const char *cfilename);
	int NumTri();
	vector<QVector3D> getPointList();
	vector<QVector3D> getVectorList();
private:
	vector<QVector3D> pointList;
	vector<QVector3D> vectorList;

	unsigned int unTriangles;
	char* memwriter;

	bool ReadASCII(const char *cfilename);// ����ascii����ʽ�� stl�ļ�   ����Ŀ���������ɵ��Ƕ�����stl���������������û���õ�
	bool ReadBinary(const char *cfilename);// ��������Ƶ�stl�ļ�

	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
};