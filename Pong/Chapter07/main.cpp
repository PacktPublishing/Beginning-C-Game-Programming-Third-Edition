#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Ball.h"
int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    int score = 0;
    int lives = 3;

    // Create a bat at the bottom center of the screen
    Bat bat(1920 / 2, 1080 - 20);
    // We will add a ball in the next chapter
    Ball ball(1920 / 2, 0);
    // Create a Text object called HUD
    Text hud;
    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    hud.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(75);
    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    // Here is our clock for timing everything
    Clock clock;
    while (window.isOpen())
    {
        /*
        Handle the player input
        ****************************
        ****************************
        ****************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }
        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }


        /*
        Update the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        // Update the delta time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);
        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << "  Lives:" << lives;
        hud.setString(ss.str());

        // Handle ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            // reverse the ball direction
            ball.reboundBottom();
            // Remove a life
            lives--;
            // Check for zero lives
            if (lives < 1) {
                // reset the score
                score = 0;
                // reset the lives
                lives = 3;
            }
        }

        // Handle ball hitting sides
        if (ball.getPosition().left < 0 ||
            ball.getPosition().left + ball.getPosition().width> window.getSize().x)
        {
            ball.reboundSides();
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }


        /*
        Draw the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();



    }
    return 0;
}
