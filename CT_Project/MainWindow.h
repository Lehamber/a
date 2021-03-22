#pragma once
#pragma execution_character_set("utf-8")//display chinese words, ������仰��qt �Ͳ���������ʾ ����

#include <QtWidgets/QWidget>
#include <QtWidgets>
#include "ui_MainWindow.h"
#include "MyGLWidget.h"
#include "PointCloud.h"
#include <Qvector3D>
#include "ReadSTLFile.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
public slots:
	//void openAndGenerate();// ��dcm�ļ� �������� stl�ļ��͵����ļ�
	bool viewPointData();//��ʾ����
	bool viewStlData();//��ʾstl�ļ�
	void switchView();// �л���ʾ���ӿ�
	void viewAfterGenerate();
	void clearTextEdit();
	//int ReadData(const char* str, vector<float> &data);

private:
	Ui::MainWindowClass ui;

	MyGLWidget *pointCloudWidgetDemo;
	MyGLWidget *stlWidgetDemo;
	QStackedWidget *stackedWidgetDemo;

	MyGLWidget *pointCloudWidget;
	MyGLWidget *stlWidget;
	QStackedWidget *stackedWidget;


	// ����װ ���ƴ��� �� stl���ڵ�����

	int switchViewFlag;
};
