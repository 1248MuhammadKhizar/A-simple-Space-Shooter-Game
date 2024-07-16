#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Animation.h"

using namespace std;
using namespace sf;

int main()
{
    int score = 0;
    bool bulletActive = false;
    int life = 0;
    RenderWindow window(VideoMode(1280, 720), "Space Shooter", Style::Close | Style::Resize);
    RectangleShape craft(Vector2f(100.0f, 100.0f));

    RectangleShape Enemy1(Vector2f(50.0f, 50.0f));
    RectangleShape Enemy2(Vector2f(50.0f, 50.0f));
    RectangleShape Enemy3(Vector2f(50.0f, 50.0f));
    RectangleShape Bullets(Vector2f(40.0f, 40.0f));

    Enemy1.setFillColor(Color::White);
    Enemy2.setFillColor(Color::White);
    Enemy3.setFillColor(Color::White);

    craft.setPosition(575.0f, 510.0f);
    Enemy1.setPosition(575.0f, -90.0f);
    Enemy2.setPosition(980.0f, -110.0f);
    Enemy3.setPosition(1150.0f, -150.0f);

    Texture craft_texture;
    Texture Enemy1_t;
    Texture Enemy2_t;
    Texture Enemy3_t;
    Texture Background_texture;
    Texture Bullet_texture;

    Background_texture.loadFromFile("backg.png");
    craft_texture.loadFromFile("Shoop.png");
    Enemy1_t.loadFromFile("monster.png");
    Enemy2_t.loadFromFile("monster.png");
    Enemy3_t.loadFromFile("monster.png");
    Bullet_texture.loadFromFile("bullet.png");

    craft.setTexture(&craft_texture);
    Enemy1.setTexture(&Enemy1_t);
    Enemy2.setTexture(&Enemy2_t);
    Enemy3.setTexture(&Enemy3_t);
    Bullets.setTexture(&Bullet_texture);


    Font fnt;
    fnt.loadFromFile("arial.ttf");
    Text animated_text(to_string(score), fnt, 50);
    animated_text.setFillColor(Color::Green);
    animated_text.setPosition(600.0f,100.0f);


    Font fnt1;
    fnt1.loadFromFile("arial.ttf");
    Text animated_text1("Score:", fnt1, 50);
    animated_text1.setFillColor(Color::Green);
    animated_text1.setPosition(450.0f, 100.0f);


    while (window.isOpen())
    {
        Enemy1.move(0.0f, 0.3f);
        Enemy2.move(0.0f, 0.3f);
        Enemy3.move(0.0f, 0.3f);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::Resized)
            {
                cout << "Window Resized: " << window.getSize().x << "x" << window.getSize().y << endl;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        // Movement Controls
        if (Keyboard::isKeyPressed(Keyboard::W) && craft.getPosition().y > 0)
            craft.move(0.0f, -0.4f);
        if (Keyboard::isKeyPressed(Keyboard::A) && craft.getPosition().x > 0)
            craft.move(-0.4f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::D) && craft.getPosition().x < window.getSize().x - craft.getSize().x)
            craft.move(0.4f, 0.0f);
        if (Keyboard::isKeyPressed(Keyboard::S) && craft.getPosition().y < window.getSize().y - craft.getSize().y)
            craft.move(0.0f, 0.4f);

        
       if (!bulletActive)
        {
            bulletActive = true;
            Bullets.setPosition(craft.getPosition().x + (craft.getSize().x / 2) - (Bullets.getSize().x / 2),
            craft.getPosition().y - Bullets.getSize().y);
       }

        
        if (bulletActive)
        {
            Bullets.move(0.0f, -0.8f);
            
            if (Bullets.getPosition().y <=50.0f)
            {
                bulletActive = false; 
            }
        }

        
        srand(static_cast<unsigned>(time(0)));
        if (Enemy1.getPosition().y > window.getSize().y)
            Enemy1.setPosition(rand() % 1220 + 1, rand() % 200 - 300);
        if (Enemy2.getPosition().y > window.getSize().y)
            Enemy2.setPosition(rand() % 1000 + 1, rand() % 200 - 320);
        if (Enemy3.getPosition().y > window.getSize().y)
            Enemy3.setPosition(rand() % 1100 + 1, rand() % 200 - 350);

        // Collision Check
        FloatRect craft_bound = craft.getGlobalBounds();
        FloatRect Enemy_bound1 = Enemy1.getGlobalBounds();
        FloatRect Enemy_bound2 = Enemy2.getGlobalBounds();
        FloatRect Enemy_bound3 = Enemy3.getGlobalBounds();
        FloatRect Bullet_bound = Bullets.getGlobalBounds();
        if (craft_bound.intersects(Enemy_bound1) ||
            craft_bound.intersects(Enemy_bound2) ||
            craft_bound.intersects(Enemy_bound3))
        {
            life++;
            if (life >= 3)
            {
                window.close();
                cout << "Game Over!" << endl;
            }
        }

           if (Bullet_bound.intersects(Enemy_bound1))
        {
               Enemy1.setPosition(rand() % 1220 + 1, rand() % 200 - 300);
               score += 5;
        }
           else if (Bullet_bound.intersects(Enemy_bound2))
           {
               Enemy2.setPosition(rand() % 1220 + 1, rand() % 200 - 300);
               score += 5;
           }
           else if (Bullet_bound.intersects(Enemy_bound3))
           {
               Enemy3.setPosition(rand() % 1220 + 1, rand() % 200 - 300);
               score += 5;
           }
           animated_text.setString(to_string(score));
          
        // Drawing
        window.clear();
        window.draw(Enemy1);
        window.draw(Enemy2);
        window.draw(Enemy3);
        window.draw(craft);
        window.draw(Bullets);
        window.draw(animated_text1);
        window.draw(animated_text);
        
        window.display();
    }

   
}
