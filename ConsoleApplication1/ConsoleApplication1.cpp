#include <SFML/Graphics.hpp>
#include <string>


#define scale           1

#define radius			15.f*scale
#define screеnWidth		600*scale
#define screenHeight	800*scale
#define playerWidth		50*scale
#define baseVelocityY	0.1*scale
#define playerVelocity  10*scale


void Reset_Ball(sf::CircleShape &ball, float *velocity)
{
    ball.setPosition(sf::Vector2f(screеnWidth / 2, screenHeight / 2));
    ball.setFillColor(sf::Color::Green);

    velocity[1] = (velocity[1] < 0) ? baseVelocityY: -baseVelocityY;
    velocity[0] = baseVelocityY/2;

    ball.setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
}


int main()
{
    bool reseted = true, bounced = false;
    float velocity[] = { baseVelocityY/2, baseVelocityY };
    int scoreSecond = 0, scoreFirst = 0;

    sf::RenderWindow window(sf::VideoMode(screеnWidth, screenHeight), "MOYA IGRA");

    std::string scoreStringFirst = "Score: " + std::to_string(scoreFirst);
    std::string scoreStringSecond = "Score: " + std::to_string(scoreSecond);

    sf::CircleShape ballShape(radius);
    Reset_Ball(ballShape, velocity);


    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text textScoreSecond;
    textScoreSecond.setFont(font);
    textScoreSecond.setString(scoreStringSecond);
    textScoreSecond.setCharacterSize(20*scale);
    textScoreSecond.setPosition(25, 5);

    sf::Text textScoreFirst;
    textScoreFirst.setFont(font);
    textScoreFirst.setString(scoreStringFirst);
    textScoreFirst.setCharacterSize(20*scale);
    textScoreFirst.setPosition(25, screenHeight - 50);

    sf::RectangleShape PlayerFirst(sf::Vector2f(playerWidth, 20));
    PlayerFirst.setPosition(sf::Vector2f(300, screenHeight - 70));
    PlayerFirst.setFillColor(sf::Color::Red);

    sf::RectangleShape PlayerSecond(sf::Vector2f(playerWidth, 20));
    PlayerSecond.setPosition(sf::Vector2f(300, 50));
    PlayerSecond.setFillColor(sf::Color::Blue);


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            {
                if (!(PlayerSecond.getPosition().x <= 0))
                   // PlayerSecond.setPosition(PlayerSecond.getPosition().x - playerVelocity, PlayerSecond.getPosition().y);
                    PlayerSecond.move(-playerVelocity, 0);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                if (!(PlayerSecond.getPosition().x + playerWidth >= screеnWidth))
                    //PlayerSecond.setPosition(PlayerSecond.getPosition().x + playerVelocity, PlayerSecond.getPosition().y);
                    PlayerSecond.move(playerVelocity, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                if (!(PlayerFirst.getPosition().x <= 0))
                   // PlayerFirst.setPosition(PlayerFirst.getPosition().x - playerVelocity, PlayerFirst.getPosition().y);
                    PlayerFirst.move(-playerVelocity, 0);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if (!(PlayerFirst.getPosition().x + playerWidth >= screеnWidth))
                    //PlayerFirst.setPosition(PlayerFirst.getPosition().x + playerVelocity, PlayerFirst.getPosition().y);
                    PlayerFirst.move(playerVelocity, 0);
            }


            if (event.type == sf::Event::KeyPressed)
            {

                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                }
            }

        }

        window.clear();




        if ( (ballShape.getPosition().y >= screenHeight - 2 * radius - 25) )
        {
            Reset_Ball(ballShape, velocity);
            window.draw(ballShape);
            reseted = true;
            scoreSecond++;
            scoreStringSecond = "Score: " + std::to_string(scoreSecond);
        }

        if ((ballShape.getPosition().y <= 25))
        {
            Reset_Ball(ballShape, velocity);
            window.draw(ballShape);
            reseted = true;
            scoreFirst++;
            scoreStringFirst = "Score: " + std::to_string(scoreFirst);
        }

        if ( (ballShape.getGlobalBounds().intersects(PlayerFirst.getGlobalBounds())) && (!bounced) )
        {
            velocity[1] *= 1.1;
            velocity[1] = -velocity[1];
            velocity[0] *= 1.1;
            ballShape.setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
            bounced = true;

        }

        if ( (ballShape.getGlobalBounds().intersects(PlayerSecond.getGlobalBounds())) && (!bounced))
        {
            velocity[1] *= 1.1;
            velocity[1] = -velocity[1];
            velocity[0] *= 1.1;
            ballShape.setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
            bounced = true;
        }


        if ( (ballShape.getPosition().x <= 0) || (ballShape.getPosition().x >= screеnWidth - 2 * radius) )
        {
            velocity[0] = -velocity[0];
            ballShape.setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
        }


        ballShape.setPosition(ballShape.getPosition().x + velocity[0], ballShape.getPosition().y + velocity[1]);


        textScoreFirst.setString(scoreStringFirst);
        textScoreSecond.setString(scoreStringSecond);
        window.draw(PlayerSecond);
        window.draw(textScoreFirst);
        window.draw(textScoreSecond);
        window.draw(PlayerFirst);
        window.draw(ballShape);

        window.display();

        if (reseted)
        {
            sf::sleep(sf::seconds(1));
            reseted = false;
        }

        if (bounced && (!(ballShape.getGlobalBounds().intersects(PlayerFirst.getGlobalBounds())) && !(ballShape.getGlobalBounds().intersects(PlayerSecond.getGlobalBounds()))))
        {
            bounced = false;
        }
    }

    return 0;
}