#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;


int start(){
    // font
    Font font;
    font.loadFromFile("images/arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Red);

    // end text
    Font f2;
    font.loadFromFile("images/arial.ttf");
    Text endtext;
    endtext.setFont(f2);
    endtext.setCharacterSize(50);
    endtext.setFillColor(Color::Red);
    endtext.setPosition(200.f, 270.f);
    endtext.setString("GAME OVER");
    int k = 1;

    // music

    Music m;
    Music fire;
    fire.openFromFile("sound/laser.wav");
    m.openFromFile("sound/music.wav");
    m.play();

    // window
    RenderWindow window(VideoMode(800, 600), "Space-Shooter");
    window.setFramerateLimit(60);

    // background image
    Texture backgnd;
    backgnd.loadFromFile("images/bk.jpg");
    Sprite background;
    background.setTexture(backgnd);

    // Space ship
    Texture sship;
    sship.loadFromFile("images/ship.png");
    Sprite ship;
    ship.setTexture(sship);
    ship.setPosition(330, 480);

    // bullet
    CircleShape bullet;
    bullet.setRadius(5.f);
    bullet.setFillColor(Color::Blue);
    int time1 = 0;

    // alien
    Texture alienn;
    alienn.loadFromFile("images/alien.png");
    Sprite alien;
    alien.setTexture(alienn);
    alien.setPosition(200.f, 10.f);
    int time2 = 0;

    // Score
    int score = 0;

    vector<Sprite>
        vecmon;
    vecmon.push_back(Sprite(alien));

    vector<CircleShape>
       vecbullet;
    vecbullet.push_back(CircleShape(bullet));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == event.Closed)
                window.close();

        if (Keyboard::isKeyPressed(Keyboard::Left) && ship.getPosition().x > 0)
        {
            ship.move(-8.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && ship.getPosition().x < 680)
        {
            ship.move(8.f, 0.f);
        }

        // bullet release
        if (time1 < 5)
        {
            time1++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && time1 >= 5)
        {
            fire.play();
            bullet.setPosition(ship.getPosition().x + 50, 490);
            vecbullet.push_back(CircleShape(bullet));
            time1 = 0;
        }

        for (size_t i = 0; i < vecbullet.size(); i++)
        {

            vecbullet[i].move(0.f, -10.f);
            if (vecbullet[i].getPosition().y <= 0.f)
                vecbullet.erase(vecbullet.begin() + i);
        }

        // Enemy movement
        if ( time2 < 20)
        {
            time2++;
        }
        if (time2 >= 20)
        {
            alien.setPosition(50 + rand() % 600, -10.f);
            vecmon.push_back(Sprite(alien));
            time2 = 0;
        }

        for (size_t i = 0; i < vecmon.size(); i++)
        {
            vecmon[i].move(0.f, 1.0f);

            if (vecmon[i].getPosition().y > 500.f || vecmon[i].getGlobalBounds().intersects(ship.getGlobalBounds()))
            {
                vecmon.erase(vecmon.begin() + i);
                k--;
            }
        }
        // collision

        for (size_t i = 0; i < vecbullet.size(); i++)
        {
            for (size_t j = 0; j < vecmon.size(); j++)
            {

                if (vecbullet[i].getGlobalBounds().intersects(vecmon[j].getGlobalBounds()))
                {
                    vecmon.erase(vecmon.begin() + j);
                    vecbullet.erase(vecbullet.begin() + i);
                    score++;
                    break;
                }
            }
        }

        // updating the score
        text.setString("SCORE: " + std::to_string(score));

        window.clear();
        window.draw(background);
        window.draw(ship);
        for (size_t i = 0; i < vecbullet.size(); i++)
        {
            window.draw(vecbullet[i]);
        }
        for (size_t i = 0; i < vecmon.size(); i++)
        {
            window.draw(vecmon[i]);
        }
        window.draw(alien);
        window.draw(text);

        if (k <= 0)
        {
            window.clear();
            text.setPosition(280, 200);
            window.draw(text);
            window.draw(endtext);
        }
        window.display();
    }
    return 0;
}


int main(){

    cout<<" \n\n\t****************************************** \n\n \t\t\tSPACE SHOOTER \n\n \t*******************************************\n";
    cout<<" \n\n\t****************************************** \n";
    cout<<" \n\t DIRECTION TO PLAY \n\t SPACEBAR : SHOOT \n\t LEFT ARROW : MOVE LEFT \n\t RIGHT ARROW : MOVE RIGHT";
    cout<<" \n\n\t****************************************** \n";
    int ch;
    cout<<"\n\t Enter Choice\n\t Press 1 : play \n\t Press 2 : exit\n";
    cin>>ch;
    if(ch==1)
        {
      start();
        }
    else
       {
      return 0;
      }
}
