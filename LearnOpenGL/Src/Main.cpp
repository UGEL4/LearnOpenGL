
#include <iostream>
#include "TestModel/TestModel.h"
#include "TestLight/TestLight.h"
#include "DepthTest/DepthTest.h"
#include "TestCubeMap/CubeMapTest.h"
#include "TestShadow/TestShadow.h"

int main(int argc, char** argv)
{
	//测试灯光
	//TestLight::Run();

	//立方体贴图测试
	//CubeMapTest::Run();

	//阴影测试
	//TestShadow::Run();
	TestShadow::PointShadow();

	//测试模型读取
	//TestModel::Run();

	return 0;
}