//This project is created by macOS computer and Clion IDE.
#include <SFML/Graphics.hpp>
#include <iostream> //console Log
#include "Cell.h"   //A class of squares cell.

sf::Event event;
// Using the initialization list ensures that all the members are get a default initialization.
// reference: https://stackoverflow.com/questions/47065791/clion-unintialized-record-type-player

//Navigating View
float Z00M=1.f;
//Initial Width and Height of Screen
const static float VIEW_X = 2000.0f;
const static float VIEW_Y = 1000.0f;
float VPX=0.f;//ViewPositionX
float VPY=0.f;//ViewPositionY
float viewVelocityX = VIEW_X * 3 / 100; //view X movement per a KeyPressed
float viewVelocityY = VIEW_Y * 3 / 100; //view Y movement per a KeyPressed
float viewPositionX=(VIEW_X/2)+(Z00M *VPX*viewVelocityX);
float viewPositionY=(VIEW_Y/2)+(Z00M *VPY*viewVelocityX);
//startPoint = A center of WorldSpace.
float startPointX=VIEW_X/2;
float startPointY=VIEW_Y/2;

//Navigating View Size
float viewRectWight=1.f;   //1.f;   //default,max
float viewRectHight=1.f;    //1.f;   //default,max

//Draw 100 Colorful Squares
int pi, pj, pp;
float ppi,ppj;

//Help & Other Keyboard Instruction
bool bHELP=false;
bool bPERFORMANCE=false;
bool bRESET=false;

int main() {
    //***initial condition***
    sf::RenderWindow window(
    sf::VideoMode((int) VIEW_X, (int) VIEW_Y),
            "View Navigator");
    //sfvMAIN = main view
    sf::View sfvMAIN(sf::Vector2f(0.f, 0.f),sf::Vector2f(VIEW_X, VIEW_Y));

    //sfrMAIN Square is located in the center of world space.
    sf::RectangleShape sfrMAIN(sf::Vector2f(50.f, 50.f));
    sfrMAIN.setPosition(startPointX, startPointY);
    sfrMAIN.setFillColor(sf::Color(240, 20, 120));

    //Initializing Font for HELP and PERFORMANCE Instructions.
    sf::Font font;
    if (!font.loadFromFile(
            "/Users/imac/Library/Fonts/MomcakeBold-WyonA.otf"
            //In order to load font, you have to copy the directory of that font in your computer.
            //fontReference: https://www.fontspace.com/category/basic
    ))
    {
        std::cout<<"Failed to load font.\n";
    }

    while (window.isOpen())
    {
        //*** ResizingView ***
        // reference: https://youtu.be/CpVbMeYryKo
        float windowGetSizeX = (float) window.getSize().x;
        float windowGetSizeY = (float) window.getSize().y;
        if(windowGetSizeX<=VIEW_X)
        {
            float aspectRatio = windowGetSizeY / windowGetSizeX;
            sfvMAIN.setSize(VIEW_X * viewRectWight * Z00M , VIEW_X * aspectRatio * viewRectHight * Z00M );
        }
        else
        {
            float aspectRatio = windowGetSizeX / windowGetSizeY;
            sfvMAIN.setSize(VIEW_Y * viewRectWight * aspectRatio * Z00M , VIEW_Y * viewRectHight * Z00M );
        }
        //*** Panning & Zooming ***
        // Programming Panning & Zooming (by Javidx9)
        // reference: https://youtu.be/ZQ8qtAizis4
        viewVelocityX = (VIEW_X * 3 / 100);
        viewVelocityY = (VIEW_Y * 3 / 100);
        sfvMAIN.setCenter(viewPositionX + (VPX * viewVelocityX), viewPositionY + (VPY * viewVelocityY));

        //Navigating View.
        sfvMAIN.setViewport(sf::FloatRect(0.f, 0.f, viewRectWight, viewRectHight));

        //*** view & window navigator ***
        while (window.pollEvent(event)) {
            switch (event.type) {
                default:
                    //This suppresses the warning, and makes it clear that you don't intend to handle the other event types here.
                    //reference: https://stackoverflow.com/questions/37254496/c-warning-enumeration-value-not-handled-in-switch-wswitch
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                    // Zooming view by mouse.
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.delta >= 1.5) {
                        Z00M /= 1.2f;
                    } else if (event.mouseWheelScroll.delta <= -1.5) {
                        Z00M *= 1.2f;
                    }
                    break;
                    // Navigating view position by keyboards.
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        default:
                            //This suppresses the warning, and makes it clear that you don't intend to handle the other event types here.
                            //reference: https://stackoverflow.com/questions/37254496/c-warning-enumeration-value-not-handled-in-switch-wswitch
                            break;
                        case sf::Keyboard::W:
                        case sf::Keyboard::Up:
                            VPY -= 1;
                            break;
                        case sf::Keyboard::S:
                        case sf::Keyboard::Down:
                            VPY += 1;
                            break;
                        case sf::Keyboard::A:
                        case sf::Keyboard::Left:
                            VPX -= 1;
                            break;
                        case sf::Keyboard::D:
                        case sf::Keyboard::Right:
                            VPX += 1;
                            break;
                        case sf::Keyboard::H:
                            //HELP MANU
                            //reference: https://github.com/HackerPoet/FractalSoundExplorer/blob/main/Main.cpp
                            if(!bHELP){bHELP=true;}
                            else{bHELP=false;}
                            break;
                        case sf::Keyboard::P:
                            //Performance Capacity View
                            if(!bPERFORMANCE){bPERFORMANCE=true;}
                            else{bPERFORMANCE=false;}
                            break;
                        case sf::Keyboard::R:
                            //Reset View
                            if(!bRESET){bRESET=true;}
                            break;
                            //case sf::Keyboard::ETC:
                            //Do other thing
                            //break;
                    }
                case sf::Event::Resized:
                    break;

            }
        }

        //There is 3 views including sfvMAIN, sfvHELP and sfvPERFORMANCE views.
        //Use "setView()" for displaying shapes in multiple view. (reference: https://en.sfml-dev.org/forums/index.php?topic=11526.0)
        //"window.clear();" should be executed before "window.setView(...);" and "window.draw(...);"
        window.clear(sf::Color(0, 0, 0));
        window.setView(sfvMAIN);

        //***Draw 100 Square Cells***
        pp = 0;
        ppi = 0.f;
        ppj = 0.f;
        for (pi = 0; pi < 20; pi++) {
            ppj = 0.f;
            for (pj = 0; pj < 10; pj++){
                Cell cells(ppi * 100.f, ppj * 100.f, 255 - (pj * 21), 255 - (pi * 15), 255 - (pp));
                window.draw(cells.CellWall());
                ppj += 1.f;
            }
            ppi += 1.f;
        }
        //draw a square that is located in the center
        window.draw(sfrMAIN);

        //Help & Other Keyboard Instruction
        if(bHELP)
        {
            sf::View sfvHELP(sf::Vector2f(windowGetSizeX/2, windowGetSizeY/2), sf::Vector2f(windowGetSizeX, windowGetSizeY));
            window.setView(sfvHELP);

            sf::RectangleShape sfrHELP(sf::Vector2f(windowGetSizeX, windowGetSizeY));
            sfrHELP.setPosition(0, 0);
            sfrHELP.setFillColor(sf::Color(0, 0, 0,150));
            window.draw(sfrHELP);

            sf::Text sftHELP;//("Hello SFML", font, 200);
            sftHELP.setFont(font);
            sftHELP.setCharacterSize(24*3);
            sftHELP.setPosition(50,0);
            sftHELP.setFillColor(sf::Color::White);
            sftHELP.setString(
                    "  H - Toggle Help Menu\n"
                    "  P - Toggle Performance Indicator\n"
                    "  R - Reset View\n\n"
                    "  W - Up - Move View Up\n"
                    "  A - Left - Move View Left\n"
                    "  S - Down - Move View Down\n"
                    "  D - Right - Move View Right\n"
                    "  Scroll Wheel - Zoom in and out\n"
            );
            sftHELP.setPosition(20.0f, 20.0f);
            window.draw(sftHELP);
        }
        if(bPERFORMANCE)
        {
            sf::View sfvPERFORMANCE(sf::Vector2f(windowGetSizeX/2, windowGetSizeY/2), sf::Vector2f(windowGetSizeX, windowGetSizeY));
            window.setView(sfvPERFORMANCE);

            sf::RectangleShape sfrPERFORMANCE(sf::Vector2f(windowGetSizeX, 100));
            sfrPERFORMANCE.setPosition(0, windowGetSizeY-100);
            sfrPERFORMANCE.setFillColor(sf::Color(0, 0, 0,255));
            window.draw(sfrPERFORMANCE);

            sf::Text sftPERFORMANCE;//("Hello SFML", font, 200);
            sftPERFORMANCE.setFont(font);
            sftPERFORMANCE.setCharacterSize(24*2);
            sftPERFORMANCE.setPosition(50, windowGetSizeY-100);
            sftPERFORMANCE.setFillColor(sf::Color(225,0,0));
            sftPERFORMANCE.setString("Hello the World");
            window.draw(sftPERFORMANCE);
        }
        if(bRESET)
        {
            VPX=0.f;
            VPY=0.f;
            Z00M=1.f;
            bRESET=false;
        }

        window.display();
    }
}
