// 215FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
#include <vector>

using namespace std;
using namespace sf;
using namespace sfp;

RenderWindow window(VideoMode(1000, 800), "Kaitlyn's Game of Life");

const int gridX = 20;
const int gridY = 20;
const int screenX = window.getSize().x;
const int screenY = window.getSize().y;

int cellSize = (window.getSize().x) / min(gridX, gridY);
int cellBorder = 2;

RectangleShape cell[gridX][gridY];
int currentStep[gridX][gridY];
int nextStep[gridX][gridY];

bool randomNumber() {

    int g = rand() % 100;
    return (g > 30);
}

void startGrid() {

    for (int x = 0; x < gridX; x++) {

        for (int y = 0; y < gridY; y++) {

            currentStep[x][y] = 0;
            nextStep[x][y] = 0;

            cell[x][y].setSize(Vector2f(cellSize - cellBorder, cellSize - cellBorder));
            cell[x][y].setFillColor(Color(255, 0, 255));
            cell[x][y].setPosition(Vector2f(cellSize * x, cellSize * y));
        }
    }
}

void randomizeGrid() {

    for (int x = 0; x < gridX; x++) {

        for (int y = 0; y < gridY; y++) {

            if (randomNumber()) {

                currentStep[x][y] = 0; 
            }
            else {

                currentStep[x][y] = 1; 
            }
        }
    }
}

void advanceGrid() {

    int alive;

    for (int x = 0; x < gridX; x++) {

        for (int y = 0; y < gridY; y++) {

            alive = 0;

            for (int i = -1; i <= 1; i++) {

                for (int j = -1; j <= 1; j++) {

                    if (i == 0 and j == 0) {
                        continue;
                    }

                    int neighborX = (x + i + gridX) % gridX;
                    int neighborY = (y + j + gridY) % gridY;

                    if (currentStep[neighborX][neighborY] == 1) {

                        alive++;
                    }

                }
            }

            if (alive < 2 || alive > 3) {
                nextStep[x][y] = 0;
            }
            else if (alive == 3) {
                nextStep[x][y] = 1;
            }
            else {
                nextStep[x][y] = currentStep[x][y];
            }
        }
    }

    memcpy(currentStep, nextStep, sizeof(currentStep));
}

int main() {
    Event event;

    startGrid();
    randomizeGrid();

    while (window.isOpen()) {
 
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                
                if (event.key.code == Keyboard::Escape) {

                    window.close();
                }
                else if (event.key.code == Keyboard::R) {

                    randomizeGrid();
                }
                else if (event.key.code == Keyboard::Space) {

                    advanceGrid();
                }
            }

        }

        window.clear();

        for (int x = 0; x < gridX; x++) {

            for (int y = 0; y < gridY; y++) {

                if (currentStep[x][y] == 0) {

                    cell[x][y].setFillColor(Color(255, 255, 255));
                }
                else {

                    cell[x][y].setFillColor(Color(255, 184, 222));
                }

                window.draw(cell[x][y]);
            }
        }

        window.display();
    }
}
