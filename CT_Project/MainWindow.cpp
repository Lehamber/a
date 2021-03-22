#include "MainWindow.h"
#include <Qvector3D>
#include <iostream>
#include <QStackedWidget>
#include <QByteArray>
#include <QDialog>



const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MainWindow::~MainWindow() {
	// ���շ�����ڴ�ռ�
	delete pointCloudWidget;
	delete stlWidget;
	delete stackedWidget;

	delete pointCloudWidgetDemo;
	delete stlWidgetDemo;
	delete stackedWidgetDemo;
}
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// ��ʼ��ָ�����
	pointCloudWidgetDemo = NULL;
	stlWidgetDemo = NULL;
	stackedWidgetDemo = NULL;

	pointCloudWidget = NULL;
	stlWidget = NULL;
	stackedWidget = NULL;

	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // ��ֹ��󻯰�ť
	setFixedSize(this->width(), this->height());   // ��ֹ�϶����ڴ�С
	setWindowTitle("DCM�ļ�������");// ���ô�������

	// ����ť���Ӳۺ���
	//connect(ui.openButton, &QPushButton::clicked, this, &MainWindow::openAndGenerate);
	connect(ui.switchButton, &QPushButton::clicked, this, &MainWindow::switchView);
	connect(ui.viewGenButton, &QPushButton::clicked, this, &MainWindow::viewAfterGenerate);
	connect(ui.clearButton, &QPushButton::clicked, this, &MainWindow::clearTextEdit);

	// ����demo�������ݲ���ʾ
	PointCloud pointCloud1;
	pointCloud1.read("testModel\\bunny.txt");
	vector<GLfloat>  pointData1;
	for (int i = 0; i < pointCloud1.pointData.size(); i++)//�����еĵ����ݷ��� ������ ������
	{
		pointData1.push_back(pointCloud1.pointData[i].x());
		pointData1.push_back(pointCloud1.pointData[i].y());
		pointData1.push_back(pointCloud1.pointData[i].z());
	}
	//����������ʾ���ڣ�1 Ҫ��ʾ�ĵ����ļ�
	pointCloudWidgetDemo = new MyGLWidget(this, pointData1, 1);
	pointCloudWidgetDemo->show();

	// ����demostl���ݲ���ʾ
	ReadSTLFile readSTLFile;
	readSTLFile.ReadFile("w0w285090.stl");
	PointCloud pointCloud2;
	vector<QVector3D> tempPointList = readSTLFile.getPointList();
	vector<QVector3D> tempVectorList = readSTLFile.getVectorList();
	pointCloud2.handlePointDate(tempPointList);//���� ���� �������еĵ�ӳ�䵽 ����Ϊ 0��0,0��  �߳�Ϊ1 �� ��������

	vector<GLfloat>  pointData2;
	for (int i = 0; i < pointCloud2.pointData.size(); i++)//�����еĵ����ݷ��� ������ ������
	{
		int j = i / 3;
		pointData2.push_back(pointCloud2.pointData[i].x());
		pointData2.push_back(pointCloud2.pointData[i].y());
		pointData2.push_back(pointCloud2.pointData[i].z());

		// װ���������� ͬһ������Ƭ�� ʹ�� ��ͬ�ķ�����
		pointData2.push_back(tempVectorList[j].x());
		pointData2.push_back(tempVectorList[j].y());
		pointData2.push_back(tempVectorList[j].z());
	}
	// ����stl��ʾ����  2 ����Ҫ��ʾ��stl�ļ�
	stlWidgetDemo = new MyGLWidget(this, pointData2, 2);
	stlWidgetDemo->show();

	stackedWidgetDemo = new QStackedWidget(this);
	stackedWidgetDemo->addWidget(stlWidgetDemo);//����� ��0ҳ����ʾ��ʱ��Ҳ��������ʾ����ҳ��
	stackedWidgetDemo->addWidget(pointCloudWidgetDemo);//����� ��1ҳ
	stackedWidgetDemo->move(this->width() / 4, 0);
	stackedWidgetDemo->resize(this->width() * 4 / 5, this->height());
	stackedWidgetDemo->show();
	switchViewFlag = 2;
}
void MainWindow::switchView()
{
	if (NULL == stackedWidget) {// ���Ϊ�� ��ô˵�� ��δ���� Ҫ��ʾ���ļ������Ծ��л� demo����
		if (2 == switchViewFlag)
		{
			stackedWidgetDemo->setCurrentIndex(1);//���� �������ڵ�ҳ��
			switchViewFlag = 1;
		}
		else
		{
			stackedWidgetDemo->setCurrentIndex(0);//���� stl���ڵ�ҳ��
			switchViewFlag = 2;
		}
	}
	else {// stl�͵����ļ��Ѿ����ɣ� ���Ծ��л����ɴ���
		if (2 == switchViewFlag)
		{
			stackedWidget->setCurrentIndex(1);//���� �������ڵ�ҳ��
			switchViewFlag = 1;
		}
		else
		{
			stackedWidget->setCurrentIndex(0);//���� stl���ڵ�ҳ��
			switchViewFlag = 2;
		}
	}
}

void MainWindow::viewAfterGenerate() {
	bool a = false;
	bool b = false;
	a = viewPointData(); // ��ʾ�������ļ� ��ʾ�ɹ� ����true ���� ����false
	b = viewStlData(); // ��ʾ��stl�ļ� ��ʾ�ɹ� ����true ���� ����false
	if (false == a || false == b)
	{
		ui.textEdit->append("�����ļ� ���� stl�ļ� δ����    ");
		QMessageBox::about(this, "����", "�����ļ� ���� stl�ļ� δ����   ");
		return;
	}

	stackedWidget = new QStackedWidget(this);
	stackedWidget->addWidget(stlWidget);
	stackedWidget->addWidget(pointCloudWidget);

	stackedWidget->move(this->width() / 4, 0);
	stackedWidget->resize(this->width() * 4 / 5, this->height());
	stackedWidget->show();
	stlWidget->show();
	pointCloudWidget->show();
	switchViewFlag = 2;
}
void MainWindow::clearTextEdit()// ��� �ı�������
{
	ui.textEdit->clear();
}
bool MainWindow::viewPointData()
{
	PointCloud pointCloud;

	if (false == pointCloud.read("BOLUS.txt"))//���� ���� �������еĵ�ӳ�䵽 ����Ϊ 0��0,0��  �߳�Ϊ1 �� ��������
	{
		return false;
	}
	vector<GLfloat>  pointData;
	for (int i = 0; i < pointCloud.pointData.size(); i++)//�����еĵ����ݷ��� ������ ������
	{
		pointData.push_back(pointCloud.pointData[i].x());
		pointData.push_back(pointCloud.pointData[i].y());
		pointData.push_back(pointCloud.pointData[i].z());
	}
	static bool isFirst1 = true;
	if (true == isFirst1) {
		pointCloudWidget = new MyGLWidget(this, pointData, 1);// 1����Ҫ��ʾ �����ļ� 
		isFirst1 = false;
	}
	else
	{
		/*pointCloudWidget->close();
		delete pointCloudWidget;*/  // �����ⲽ ��֪��Ϊɶ ��������ǲ��ӵ� ���ŵ�����������࣬�����ռ�úܶ���ڴ棬 �������Է��֣�
		// ֻҪ���ǹ���İѣ���ʾ�����ɰ�ť ��� ��ʮ�� �������ٴεĻ�������һ�㲻���ĺܿ��������� �������Ĳ��Ǻܺã����߿��Խ����Ż���
		pointCloudWidget = new MyGLWidget(this, pointData, 1);// 1����Ҫ��ʾ �����ļ� 
	}
	return true;
}
bool MainWindow::viewStlData() {

	ReadSTLFile readSTLFile;
	if (false == readSTLFile.ReadFile("complete.stl"))// ��exeͬĿ¼�� �������ɵ�stl�ļ� complete.stl
	{
		return false;
	}
	PointCloud pointCloud;
	vector<QVector3D> tempPointList = readSTLFile.getPointList();//��ȡ���еĵ�
	vector<QVector3D> tempVectorList = readSTLFile.getVectorList(); // ��ȡ��������Ƭ�������
	pointCloud.handlePointDate(tempPointList);//���� ���� �������еĵ�ӳ�䵽 ����Ϊ 0��0,0��  �߳�Ϊ1 �� ��������

	vector<GLfloat>  pointData;
	for (int i = 0; i < pointCloud.pointData.size(); i++)//�����еĵ����ݷ��� ������ ������
	{
		int j = i / 3;
		pointData.push_back(pointCloud.pointData[i].x());
		pointData.push_back(pointCloud.pointData[i].y());
		pointData.push_back(pointCloud.pointData[i].z());

		// װ���������� ͬһ������Ƭ�� ʹ�� ��ͬ�ķ�����
		pointData.push_back(tempVectorList[j].x());
		pointData.push_back(tempVectorList[j].y());
		pointData.push_back(tempVectorList[j].z());
	}
	static bool isFirst2 = true;
	if (true == isFirst2) {
		stlWidget = new MyGLWidget(this, pointData, 2);// 2����Ҫ��ʾ stl�ļ� 
		isFirst2 = false;
	}
	else
	{
		//stlWidget->close();
		//delete stlWidget; // �����ⲽ ��֪��Ϊɶ ��������ǲ��ӵ� ���ŵ�����������࣬�����ռ�úܶ���ڴ棬 �������Է��֣�
		// ֻҪ���ǹ���İѣ���ʾ�����ɰ�ť ��� ��ʮ�� �������ٴεĻ�������һ�㲻���ĺܿ��������� �������Ĳ��Ǻܺã����߿��Խ����Ż���
		stlWidget = new MyGLWidget(this, pointData, 2);// 2����Ҫ��ʾ stl�ļ� 
	}
	return true;
}


