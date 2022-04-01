#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef SFMLWASDVIEWNAVIGATOR_CELL_H
#define SFMLWASDVIEWNAVIGATOR_CELL_H
class Cell{
public:
    float posX;
    float posY;
    int redd;
    int greenn;
    int bluee;
    Cell(float PosX,float PosY,int Redd, int Greenn, int Bluee)
    {
        posX=PosX;
        posY=PosY;
        redd=Redd;
        greenn=Greenn;
        bluee=Bluee;
    }
    sf::RectangleShape CellWall() const
    {
        sf::RectangleShape sqcell(sf::Vector2f(90.f,  90.f));
        sqcell.setPosition(posX,posY);
        sqcell.setFillColor(sf::Color(redd,greenn,bluee));
        return sqcell;
    }
};
#endif //SFMLWASDVIEWNAVIGATOR_CELL_H

//What is Header File.h? : https://youtu.be/9RJTQmK0YPI && https://stackoverflow.com/questions/1945846/what-should-go-into-an-h-file
/*
 * The simplest question to ask yourself to determine what belongs where is
 * "if I change this, will I have to change code in other files to make things compile again?"
 * If the answer is "yes" it probably belongs in the header file;
 * if the answer is "no" it probably belongs in the code file.
*/
//Is it a bad idea to define classes in header files in C++? : https://www.quora.com/Is-it-a-bad-idea-to-define-classes-in-header-files-in-C++
//convey.h = class && initial_function