#include <SFML/Graphics.hpp>

void pollEvents(sf::RenderWindow& window);
sf::Texture cycle(sf::RenderTexture& texture, sf::ContextSettings& set);

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Sierpinski's Triangle", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(1);
	sf::RenderTexture finalTexture;
	int len = window.getSize().x;
	if (len > window.getSize().y) {
		len = window.getSize().y;
	}
	sf::View view;
	view = window.getView();
	view.move(-(float)window.getSize().x / 4, 0.0f);
	window.setView(view);
	finalTexture.create(len, len, settings);
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f((float)finalTexture.getSize().x / 2, 0.0f));
	triangle.setPoint(1, sf::Vector2f((float)finalTexture.getSize().x, (float)finalTexture.getSize().y));
	triangle.setPoint(2, sf::Vector2f(0.0f, (float)finalTexture.getSize().y));
	triangle.setFillColor(sf::Color::Red);
	triangle.setPosition(0.0f, 0.0f);
	finalTexture.clear(sf::Color::Black);
	finalTexture.draw(triangle);
	finalTexture.display();
	while (window.isOpen()) {
		pollEvents(window);
		window.clear(sf::Color::Black);
		sf::Texture temp = cycle(finalTexture, settings);
		finalTexture.clear(sf::Color::Black);
		finalTexture.draw(sf::Sprite(temp));
		finalTexture.display();
		window.draw(sf::Sprite(finalTexture.getTexture()));
		window.display();
	}

	return 0;
}

void pollEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0.0f, 0.0f, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		} else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			} else if (event.key.code == sf::Keyboard::Space) {
				//may add a way to advance through cycles
			}
		}
	}
}

sf::Texture cycle(sf::RenderTexture& texture, sf::ContextSettings& set) {
	sf::RenderTexture outputTexture;
	outputTexture.create(texture.getSize().x, texture.getSize().y, set);
	outputTexture.clear(sf::Color::Black);
	sf::Sprite textureSprite = sf::Sprite(texture.getTexture());
	textureSprite.setScale(0.5f, 0.5f);
	
	textureSprite.setPosition((float)texture.getSize().x / 4, 0.0f);
	outputTexture.draw(textureSprite);
	textureSprite.setPosition(0, (float)texture.getSize().y / 2);
	outputTexture.draw(textureSprite);
	textureSprite.setPosition((float)texture.getSize().x / 2, texture.getSize().y / 2);
	outputTexture.draw(textureSprite);

	outputTexture.display();
	return outputTexture.getTexture();
}