#include <SFML/audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/main.hpp>
#include <SFML/network.hpp>
#include <SFML/system.hpp>
#include <SFML/window.hpp>
#include <math.h>

sf::Sprite circle;
sf::Texture t_circle;

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Sprites Moviendo");
	t_circle.loadFromFile("assets/rcircle.png");
	circle.setTexture(t_circle);
	circle.setPosition(300, 200);

	bool bandera = false;
	sf::Vector2i inicialMousePos;
	sf::Vector2f distancia;

    while (App.isOpen()) {
		sf::Event evt;
		while (App.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed)
				App.close();
			// dectectar si se presiona el boton izquierdo en el sprite
			if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
				inicialMousePos = sf::Mouse::getPosition(App);
				sf::Vector2f spritePos = circle.getPosition();
				
				//capturar el centro del sprite
				sf::Vector2f SpriteCentro;
				float radio = t_circle.getSize().x / 2.0f;
				
				SpriteCentro.x = circle.getPosition().x + radio;
				SpriteCentro.y = circle.getPosition().y + radio;
				float disX = inicialMousePos.x - SpriteCentro.x;
				float disY = inicialMousePos.y - SpriteCentro.y;


                //hipotenusa 2 = lado a + lado b 2 -> hipotenusa = raiz(a2 +b2)
				float hipotenusa = std::sqrt(std::pow(disX,2)) + std::pow(disY,2);

				// Verificar si el puntero toca el sprite pero ademas calcular su distancia 
				if (hipotenusa <= radio) { 
					bandera = true;
					distancia.x = inicialMousePos.x = spritePos.x;
					distancia.y = inicialMousePos.y = spritePos.y;
				}
		
			}

            //detectar si suelta el boton
			if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
				bandera = false;
			}
		}
        //actualizar la posicion del sprite con badera true
		if (bandera) {
			sf::Vector2i actualMousePos = sf::Mouse::getPosition(App);
			circle.setPosition(actualMousePos.x - distancia.x, actualMousePos.y - distancia.y);
		}


		App.clear();
		App.draw(circle);
		App.display();
	}

	return 0;
}



