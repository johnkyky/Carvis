#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

#include "Car.hpp"
#include "Circuit.hpp"

#include "Matrix.hpp"
#include "NeuralNetwork.hpp"


#define FPS 60.f
#define NBR_CAR 1


void neuro()
{
    NeuralNetwork n(6, 3, 10, 2);
    Matrix input(1, 6);
    input.set(0, 0, 30);
    input.set(0, 1, -3.5);
    input.set(0, 2, 12);
    input.set(0, 3, 2.4);
    input.set(0, 4, 10.6);
    input.set(0, 5, 4.9);
    n.forward(input);
}

void mainThread()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "Carvis");
    window.setFramerateLimit(FPS);

    sf::Texture carTexture;
    carTexture.loadFromFile("./asset/audiLittle.png");

    Circuit circuit("./asset/circuit.map");
    
    std::vector<Car> cars;
    for(unsigned int i = 0; i < NBR_CAR; i++)
        cars.emplace_back(circuit, carTexture);
    
    sf::Clock clock;
    sf::Event event;
    while(window.isOpen())
    {
        sf::Time dt = clock.restart();
        //printf("%f\n", 1 / dt.asSeconds());
        
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                for(Car& i : cars)
                    i.showRay();

            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                for(Car& i : cars)
                {
                    if(i.getBox().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        printf("marque\n");
                        break;
                    }
                }
        }

        for(Car& i : cars)
            i.update(dt.asSeconds());

        window.clear(sf::Color(163, 146, 111));
        
        window.draw(circuit);
        for(Car& i : cars)
            window.draw(i);

        window.display();
    }
}


int main()
{
    srand(time(0));
    
    //neuro();
    mainThread();

    return 0;
}