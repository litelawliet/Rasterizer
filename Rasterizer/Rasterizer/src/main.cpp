#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rasterizer/Window.h"

/*void renderingThread(sf::Window* window)
{
	window->setActive(true);


	while (window->isOpen())
	{

		window->display();
	}
}*/

int main()
{
	/*sf::ContextSettings settings;

	settings.majorVersion = 4;
	settings.minorVersion = 5;
	settings.antialiasingLevel = 16;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	const sf::Uint32 width = 800;
	const sf::Uint32 height = 600;
	const sf::Uint32 pixelBits = 4;

	sf::RenderWindow window(sf::VideoMode(width, height), "Rasterizer", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	// Array of pixel in form of RGBA (one pixel is 4 continuous byte)
	sf::Uint8* pixelArray = new sf::Uint8[width * height * pixelBits];

	for (sf::Uint32 x = 0; x < width; ++x)
	{
		for (sf::Uint32 y = 0; y < height; ++y)
		{
			pixelArray[4 * (x * height + y)] = 0;
			pixelArray[4 * (x * height + y) + 1] = 0;
			pixelArray[4 * (x * height + y) + 2] = 0;
			pixelArray[4 * (x * height + y) + 3] = 255;
		}
	}

	// Create an image out of the pixel array
	sf::Image image;
	image.create(width, height, pixelArray);

	// Modify the image itself using setPixel
	image.setPixel(400, 300, sf::Color::White);

	// Make up a texture out from the modified image
	sf::Texture texture;
	texture.loadFromImage(image);

	// Change the sprite texture (need a sprite to be drawn using sf::RenderWindow)
	sf::Sprite renderingImage;
	renderingImage.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			default: continue;
			}
		}

		window.clear();
		window.draw(renderingImage);
		window.display();
	}
	window.setActive(false);

	sf::Thread thread(&renderingThread, &window);
	thread.launch();

	// la boucle d'évènements/logique/etc.
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;

			default: continue;
			}
		}
	}

	delete[] pixelArray;*/

	Rasterizer::Window window {800, 600, "Rasterizer"};
	window.Run();

	return EXIT_SUCCESS;
}
