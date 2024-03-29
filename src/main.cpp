#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

#include "Car.hpp"
#include "Circuit.hpp"

#include "Matrix.hpp"
#include "NeuralNetwork.hpp"


#define FPS 61.f
#define NBR_CAR 500


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

    // environnement var
    bool pause(false);
    unsigned int generation(0);

    // Load font and fps label
    sf::Font font;
    if(!font.loadFromFile("./ressources/font.ttf"))
        throw std::runtime_error("Failed to load font");
    sf::Text fpsLabel(std::to_string(FPS), font);
    fpsLabel.setFillColor(sf::Color::Black);

    sf::Text controlLabel("A : Show Ray | S : Solo run of selected car | LeftClic : Select/Unselect car | RightClic : Start a new generation", font);
    controlLabel.setFillColor(sf::Color::Black);
    controlLabel.setPosition(0.f, 975.f);

    // Load Texture de la voiture
    sf::Texture carTexture;
    if(!carTexture.loadFromFile("./ressources/audiLittle.png"))
        throw std::runtime_error("Failed to load car texture");

    // Load circuit
    Circuit circuit("./ressources/circuit.map");
    
    std::vector<Car> cars;
    for(unsigned int i = 0; i < NBR_CAR; i++)
        cars.emplace_back(circuit, carTexture);
    Car* bestCar(nullptr);
    
    sf::Clock clock;
    sf::Event event;
    while(window.isOpen())
    {
        sf::Time dt = clock.restart();
        fpsLabel.setString(std::to_string((int)(1 / dt.asSeconds())));
        
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
                for(Car& i : cars)
                    i.showRay();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                std::vector<Car> carsBuffer;
                carsBuffer.push_back(Car(*bestCar));
                cars.clear();
                cars = carsBuffer;
                bestCar = nullptr;
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                pause = !pause;

            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
                if(bestCar)
                {
                    generation++;
                    std::vector<Car> carsBuffer;
                    carsBuffer.push_back(Car(*bestCar));
                    for(unsigned int i = 0; i < NBR_CAR - 1; i++)
                    {
                        Car carBuffer(*bestCar);
                        carBuffer.mutate();
                        carsBuffer.push_back(carBuffer);
                    }
                    cars.clear();
                    cars = carsBuffer;
                    bestCar = &cars[0];
                    cars[0].select();
                }

            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for(Car& i : cars)
                {
                    if(i.getBox().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        if(bestCar == &i)
                        {
                            bestCar->unselect();
                            bestCar = nullptr;                            
                        }
                        else
                        {
                            if(bestCar)
                                bestCar->unselect();
                            bestCar = &i;
                            bestCar->select();
                            break;
                        }
                    }
                }
            }
        }

        if(!pause)
            for(Car& i : cars)
                i.update(dt.asSeconds());

        window.clear(sf::Color(163, 146, 111));
        
        window.draw(circuit);
        for(Car& i : cars)
            window.draw(i);

        window.draw(fpsLabel);
        window.draw(controlLabel);

        window.display();
    }
}

void foo()
{
    Matrix m(10, 10);
    m.print();
    printf("\n");
    m.mutate(0.1);
    m.print();
}

int main()
{
    srand(time(0));
    
    //neuro();
    mainThread();
    //foo();

    return 0;
}