
#include <iostream>
#include "TestModel/TestModel.h"
#include "TestLight/TestLight.h"
#include "DepthTest/DepthTest.h"
#include "TestCubeMap/CubeMapTest.h"
#include "TestShadow/TestShadow.h"

int main(int argc, char** argv)
{
	//TestModel::Run();
	//TestLight::Run();
	//DepthTest::Run();
	CubeMapTest::Run();
	//TestShadow::Run();
	return 0;
}