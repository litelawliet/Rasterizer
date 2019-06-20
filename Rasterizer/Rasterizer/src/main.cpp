#include "Rasterizer/Window.h"
#include "Rasterizer/Resources/Model.h"

int main()
{
	Rasterizer::Window window {1024, 768, "Rasterizer"};
	
	Rasterizer::Resources::Model car("../rsc/models/standard_car.fbx");
	
	window.Run();


	return EXIT_SUCCESS;
}
