
#include <iostream>
#include "TestModel/TestModel.h"
#include "TestLight/TestLight.h"
#include "DepthTest/DepthTest.h"
#include "TestCubeMap/CubeMapTest.h"
#include "TestShadow/TestShadow.h"

int main(int argc, char** argv)
{
	//���Եƹ�
	//TestLight::Run();

	//��������ͼ����
	//CubeMapTest::Run();

	//��Ӱ����
	//TestShadow::Run();
	TestShadow::PointShadow();

	//����ģ�Ͷ�ȡ
	//TestModel::Run();

	return 0;
}