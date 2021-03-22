#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <QVector3D>
using namespace std;

class PointCloud
{
public:
	PointCloud();
	~PointCloud();
	
	QVector3D maxCoordinate;//��������
	QVector3D minCoordinate;//��С�����
	vector<QVector3D> pointData;//������
	
	float getFactor();
public:
	bool read(const char* path);//���ļ��ж�ȡ�������� �������� ӳ�䵽 -1.0 -- 1.0 �ķ�Χ֮��
	void handlePointDate(vector<QVector3D> data);// ��񻯵������ݣ� ӳ�䵽 -1.0 -- 1.0 �ķ�Χ֮��
	void getMaxCoordinate();// �ֱ����� x y z �����ֵ ��ϳ�һ���㣻
	void getMinCoordinate();//  �ֱ���� x y z ����Сֵ ��ϳ�һ����
	void getCenterPoint(QVector3D &vec); // ��ȡ���ĵ�
	  
};

