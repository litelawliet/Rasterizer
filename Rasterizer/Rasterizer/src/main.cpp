#include "Rasterizer/Window.h"

int main()
{
	Rasterizer::Window window {1600, 900, "Rasterizer"};

	Rasterizer::Managers::Scene::GetInstance()->AddEntity("../rsc/models/standard_car.fbx");
	
	window.Run();

	return EXIT_SUCCESS;
}
