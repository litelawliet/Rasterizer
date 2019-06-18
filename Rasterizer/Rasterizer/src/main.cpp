#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::ContextSettings settings;

	settings.majorVersion = 4;
	settings.minorVersion = 5;
	settings.antialiasingLevel = 16;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return EXIT_SUCCESS;
}
