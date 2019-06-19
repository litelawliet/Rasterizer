#include "Rasterizer/Window.h"

int main()
{
	Rasterizer::Window window {1024, 768, "Rasterizer"};
	window.Run();

	return EXIT_SUCCESS;
}
