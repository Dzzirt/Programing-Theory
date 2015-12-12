#include "application.h"
#include <string>


namespace {
const char BUTTON_EXAMPLE_LABEL[] = "\nPress\n  Me";
const sf::Vector2f BUTTON_EXAMPLE_POS = sf::Vector2f(350, 250);
const char WINDOW_TITLE_SUFFIX[] = " times pressed";

}


SApplication::SApplication()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Check Box")
{
	assets.Init();
	window.setFramerateLimit(DEFAULT_FPS);
	buttonExample.Init(assets, BUTTON_EXAMPLE_LABEL);
	buttonExample.SetPosition(BUTTON_EXAMPLE_POS);
	buttonExample.handler = [&](bool checked) {
		if (checked) {
			window.setTitle("Checked");
		}
		else {
			window.setTitle("Unchecked");
		}
	};
	
}

void SApplication::Exec()
{
    while (window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event))
        {
					buttonExample.OnEvent(event);

            switch (event.type)
			{
			case sf::Event::Closed:
                window.close();
                break;
			default:
				break;
            }
		}
		window.clear(sf::Color::White);
		buttonExample.Draw(window);
        window.display();
	}
}
