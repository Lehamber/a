#include "shaderProgram.h"

shaderProgram::shaderProgram(const char* vPath, const char* fPath)
{
	vertexPath = vPath;
	fragmentPath = fPath;
	init();
}

void shaderProgram::setShader(const char* vPath, const char* fPath)
{
	vertexPath = vPath;
	fragmentPath = fPath;
	init();
}

void shaderProgram::init()
{
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{	//����ɫ���ļ� 
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		stringstream vShaderStream;
		stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FIEL_NOT_SUCCESSFULLY_READ" << endl;
	}
	// ���������ɫ������ ת���� ��׼����ɫ��������ʽ
	const char * vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	//���� ������ɫ�� �� Ƭ����ɫ��
	QOpenGLShader verShader(QOpenGLShader::Vertex);
	QOpenGLShader fraShader(QOpenGLShader::Fragment);

	verShader.compileSourceCode(vShaderCode);
	fraShader.compileSourceCode(fShaderCode);

	ID = new QOpenGLShaderProgram();
	ID->addShader(&verShader);
	ID->addShader(&fraShader);
	ID->link();//  ����

}

void shaderProgram::use()
{
	ID->bind();// ������ɫ�� �󶨵���ǰ��opengl������ ֮ǰ�󶨵Ķ���ʧЧ
}
void shaderProgram::setUniformMat4(const char *name, const QMatrix4x4 trans) const
{
	ID->setUniformValue(name, trans);
}
void shaderProgram::setUniformFloat(const char *name, const GLfloat value) const
{
	ID->setUniformValue(name, value);
}
void shaderProgram::setUniformInt(const char *name, const int value) const
{
	ID->setUniformValue(name, value);
}
void shaderProgram::setUniformVec4(const char *name, const QVector4D value) const
{
	ID->setUniformValue(name, value);
}
void shaderProgram::setUniformVec3(const char *name, const QVector3D value) const
{
	ID->setUniformValue(name, value);
}
