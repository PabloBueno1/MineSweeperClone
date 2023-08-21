#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <ostream>
#include <sstream>
#include<string>
#include<math.h>
#include "Random.h"


using namespace std;

void floodFill(vector<vector<Tile>> &board, int x, int y);
void createBoard(vector<vector<Tile>> &board, int column, int row , int mineCount);
bool checkTiles(vector<vector<Tile>>& board, int column, int row);
void coverMines(vector<vector<Tile>>& board, int column, int row);
int loadTest(vector<vector<Tile>>& board , string filename);
int getRow(vector<vector<Tile>>& board);
int getColumn(vector<vector<Tile>>& board);


int main()
{
    // Open the window from config
    ifstream inFile("boards/config.cfg");
    string lineFromFile;

    int column = 0;
    int row = 0;
    int mineCount = 0;

    if (inFile.is_open()) {
       
       inFile >> column;
       inFile >> row;
       inFile >> mineCount;

    }  

    inFile.close();
    
    int boxesFlagged = 0;
    bool gameWon = false;
    bool gameLost = false;
    bool gameOver = false;
    int height = (row * 32) + 100;
    int width = column * 32;
    int tileCount = column * row;
    int minesRemain = mineCount;
    int flagCount = 0;
    bool testOn = false;
    int configMineCount = mineCount;
    bool revealAll = false;

    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");

    //Load textures
    sf::Sprite tileHide(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite faceHappy(TextureManager::GetTexture("face_happy"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite tileReveal(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite num1(TextureManager::GetTexture("number_1"));
    sf::Sprite num2(TextureManager::GetTexture("number_2"));
    sf::Sprite num3(TextureManager::GetTexture("number_3"));
    sf::Sprite num4(TextureManager::GetTexture("number_4"));
    sf::Sprite num5(TextureManager::GetTexture("number_5"));
    sf::Sprite num6(TextureManager::GetTexture("number_6"));
    sf::Sprite num7(TextureManager::GetTexture("number_7"));
    sf::Sprite num8(TextureManager::GetTexture("number_8"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite facelose(TextureManager::GetTexture("face_lose"));
    sf::Sprite facewin(TextureManager::GetTexture("face_win"));


    vector<vector<Tile>> board;

    createBoard(board, column, row, mineCount);
    



    while (window.isOpen())
    {

        window.clear(sf::Color(255, 255, 255, 255));

        sf::Event event;
        while (window.pollEvent(event))
        {
           
            if (checkTiles(board, column, row)) {
                coverMines(board, column, row);
                minesRemain = 0;
                flagCount = minesRemain;
                gameWon = true;
            }
            if (gameLost || gameWon) {
                gameOver = true;
            }

            if (event.type == sf::Event::Closed)
                window.close();

             else if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {

                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

                    int xPos;
                    int yPos;

                    if (!testOn) {
                        xPos = floor(localPosition.x / 32);
                        yPos = floor(localPosition.y / 32);
                    }
                    else {
                        yPos = floor(localPosition.x / 32);
                        xPos = floor(localPosition.y / 32);
                    }
                    
                    if (xPos < column && yPos < row && yPos < row && !board[xPos][yPos].getFlag() && board[xPos][yPos].getMine() && !gameOver) {
                        gameLost = true;
                        if (!revealAll) {
                            for (int i = 0; i < column; i++) {
                                for (int j = 0; j < row; j++) {
                                    board[i][j].flipReveal();
                                }
                            }
                        }
                    }
                    else if (xPos < column && yPos < row && yPos < row && !board[xPos][yPos].getFlag() && board[xPos][yPos].getNum() == 0 && !board[xPos][yPos].getMine() && !gameOver) {
                        floodFill(board, xPos, yPos);
                    }
                    else if (xPos < column && yPos < row && yPos < row && !board[xPos][yPos].getFlag() && !gameOver) {
                        board[xPos][yPos].setPressed(true);
                    }
                    else if ((localPosition.x > (width / 2) - 32 && localPosition.x < (width / 2) + 32) && (localPosition.y > height - 100 && localPosition.y < height - 36)) {
                        if (testOn) {
                            int temp;
                            temp = row;
                            row = column;
                            column = temp;
                        }
                        mineCount = configMineCount;
                        createBoard(board, column, row, mineCount);
                        gameWon = false;
                        gameLost = false;
                        gameOver = false;
                        testOn = false;
                        revealAll = false;
                        minesRemain = mineCount;
                        flagCount = 0;
                    }
                    else if ((localPosition.x > (width / 2) + 160 && localPosition.x < (width / 2) + 224) && (localPosition.y > height - 100 && localPosition.y < height - 36)) {
                        mineCount = loadTest(board, "testboard1");
                        minesRemain = mineCount;
                        row = getRow(board);
                        column = getColumn(board);
                        gameWon = false;
                        gameLost = false;
                        gameOver = false;
                        revealAll = false;
                        testOn = true;
                        flagCount = 0;
                    }
                    else if ((localPosition.x > (width / 2) + 224 && localPosition.x < (width / 2) + 288) && (localPosition.y > height - 100 && localPosition.y < height - 36)) {
                        mineCount = loadTest(board, "testboard2");
                        minesRemain = mineCount;
                        row = getRow(board);
                        column = getColumn(board);
                        gameWon = false;
                        gameLost = false;
                        gameOver = false;
                        revealAll = false;
                        testOn = true;
                        flagCount = 0;
                    }
                    else if ((localPosition.x > (width / 2) + 288 && localPosition.x < (width / 2) + 352) && (localPosition.y > height - 100 && localPosition.y < height - 36)) {
                        mineCount = loadTest(board, "testboard3");
                        minesRemain = mineCount;
                        row = getRow(board);
                        column = getColumn(board);
                        gameWon = false;
                        gameLost = false;
                        revealAll = false;
                        gameOver = false;
                        testOn = true;
                        flagCount = 0;
                    }
                    else if ((localPosition.x > (width / 2) + 96 && localPosition.x < (width / 2) + 160) && (localPosition.y > height - 100 && localPosition.y < height - 36) && !gameOver) {
                        for (int i = 0; i < column; i++) {
                            for (int j = 0; j < row; j++) {
                                board[i][j].flipReveal();
                            }
                        }
                        revealAll = !revealAll;
                    }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

                    int xPos;
                    int yPos;

                    if (!testOn) {
                        xPos = floor(localPosition.x / 32);
                        yPos = floor(localPosition.y / 32);
                    }
                    else {
                        yPos = floor(localPosition.x / 32);
                        xPos = floor(localPosition.y / 32);
                    }

                    if (xPos < column && yPos < row && yPos < row && !board[xPos][yPos].getPressed() && !board[xPos][yPos].getReveal() && !gameOver) {
                        board[xPos][yPos].flipFlag();
                        if (board[xPos][yPos].getFlag()) {
                            flagCount++;
                    }
                        else if (!board[xPos][yPos].getFlag()) {
                            flagCount--;
                    }
                        else if (board[xPos][yPos].getFlag() && board[xPos][yPos].getMine()) {
                            minesRemain--;
                            flagCount++;

                        }
                        else if (!board[xPos][yPos].getFlag() && board[xPos][yPos].getMine()) {
                            minesRemain++;
                            flagCount--;

                        }
                    }
                }
            }
        }     

        
        // Draw Tile
        for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {
                if (board[i][j].getReveal()) {
                    window.draw(board[i][j].revealed);

                    window.draw(board[i][j].revealAllSprite());

                    if (board[i][j].getFlag()) {
                        window.draw(board[i][j].flagTexture);
                        window.draw(board[i][j].numberMine);
                    }
                }
                else {
                    if (board[i][j].getFlag()) {
                        window.draw(board[i][j].hidden);
                    }
                    if (board[i][j].getPressed()) {
                        window.draw(board[i][j].revealed);
                    }                    
                    window.draw(board[i][j].getSprite());
                }
            }
        }


        // Draw the smiley + debug buttons
        if (gameWon) {
            facewin.setPosition((width / 2) - 32, height - 100);
            window.draw(facewin);
        }
        else if (gameLost) {
            facelose.setPosition((width / 2) - 32, height - 100);
            window.draw(facelose);
        }
        else {
            faceHappy.setPosition((width / 2) - 32, height - 100);
            window.draw(faceHappy);
        }
        
        debug.setPosition((width / 2) + 96, height - 100);
        window.draw(debug);
        test1.setPosition((width / 2) + 160, height - 100);
        window.draw(test1);
        test2.setPosition((width / 2) + 224, height - 100);
        window.draw(test2);
        test3.setPosition((width / 2) + 288, height - 100);
        window.draw(test3);

        // Draw the counter

        int digitsPlace;

        if (flagCount > minesRemain) {
            digitsPlace = flagCount - minesRemain;
            digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
            digits.setPosition(0, height - 100);
            window.draw(digits);
        }
        else {
            digitsPlace = minesRemain - flagCount;
        }

        for (int i = 3; i > 0; i--)
        {
            int temp;
            temp = digitsPlace % 10;
            digits.setTextureRect(sf::IntRect(21*temp, 0, 21, 32));
            digits.setPosition(21*(i), height - 100);
            window.draw(digits);

            digitsPlace = digitsPlace / 10;
        }

        


        window.display();
    }


    TextureManager::Clear();
    return 0;
}

void floodFill(vector<vector<Tile>> &board, int x, int y)
{
    
    if (x < 0 || y < 0 || y > board[0].size() - 1 || x > board.size() - 1 || board[x][y].getFlag()) {
        return;
    }
    if (board[x][y].getNum() != 0 && !board[x][y].getMine()) {
        board[x][y].setPressed(true);
        return;
    }
    if (board[x][y].getPressed()) {
        return;
    }
    else {
        board[x][y].setPressed(true);
    }
    floodFill(board, x, y - 1);
    floodFill(board, x, y + 1);
    floodFill(board, x + 1, y);
    floodFill(board, x - 1, y);
    floodFill(board, x + 1, y - 1);
    floodFill(board, x - 1, y - 1);
    floodFill(board, x + 1, y + 1);
    floodFill(board, x - 1, y + 1);

}

void createBoard(vector<vector<Tile>>& board, int column, int row, int mineCount)
{
    // Clear current board
    
    board.clear();


    // Create all the Tiles first time
    vector<Tile> tiles;
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            Tile temp(i * 32, j * 32);
            tiles.push_back(temp);
        }
        board.push_back(tiles);
        tiles.clear();
    }

    for (int i = 0; i < mineCount; i++)
    {
        int randomX = Random::Int(0, column - 1);
        int randomY = Random::Int(0, row - 1);


        if (!board[randomX][randomY].getMine()) {
            board[randomX][randomY].setMine(true);
        }
        else i--;
    }

    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            int nearby = 0;
            if (i >= 0 && j - 1 >= 0 && i < column && j - 1 < row && board[i][j - 1].getMine()) {
                nearby++;
            }
            if (i >= 0 && j + 1 >= 0 && i < column && j + 1 < row && board[i][j + 1].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j >= 0 && i + 1 < column && j < row && board[i + 1][j].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j >= 0 && i - 1 < column && j < row && board[i - 1][j].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j - 1 >= 0 && i + 1 < column && j - 1 < row && board[i + 1][j - 1].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j - 1 >= 0 && i - 1 < column && j - 1 < row && board[i - 1][j - 1].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j + 1 >= 0 && i + 1 < column && j + 1 < row && board[i + 1][j + 1].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j + 1 >= 0 && i - 1 < column && j + 1 < row && board[i - 1][j + 1].getMine()) {
                nearby++;
            }
            board[i][j].setNum(nearby);
        }
    }
}

bool checkTiles(vector<vector<Tile>>& board, int column, int row)
{
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            if (!board[i][j].getPressed() && !board[i][j].getMine()) {
                return false;
            }
        }
    }
    return true;
}

void coverMines(vector<vector<Tile>>& board, int column, int row)
{
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            if (!board[i][j].getPressed() && board[i][j].getMine()) {
                board[i][j].setFlag(true);
            }
        }
    }
}

int loadTest(vector<vector<Tile>>& board, string filename)
{
    board.clear();
    string completeName = "boards/" + filename + ".brd";
    vector<string> binary;
    int mineCount = 0;

    ifstream inFile(completeName);
    string lineFromFile;

    while (getline(inFile, lineFromFile)) {

        istringstream stream(lineFromFile);
        string temp;

        getline(stream, temp, '\n');
        binary.push_back(temp);
    }

    int column = binary.size();
    int row = binary[0].size();
    vector<Tile> tiles;
    
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            Tile temp(j * 32, i * 32);
            tiles.push_back(temp);

            if (binary[i].at(j) == '1') {
                tiles[j].setMine(true);
                mineCount++;
            }
        }
        board.push_back(tiles);
        tiles.clear();
    }



    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            int nearby = 0;
            if (i >= 0 && j - 1 >= 0 && i < column && j - 1 < row && board[i][j - 1].getMine()) {
                nearby++;
            }
            if (i >= 0 && j + 1 >= 0 && i < column && j + 1 < row && board[i][j + 1].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j >= 0 && i + 1 < column && j < row && board[i + 1][j].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j >= 0 && i - 1 < column && j < row && board[i - 1][j].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j - 1 >= 0 && i + 1 < column && j - 1 < row && board[i + 1][j - 1].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j - 1 >= 0 && i - 1 < column && j - 1 < row && board[i - 1][j - 1].getMine()) {
                nearby++;
            }
            if (i + 1 >= 0 && j + 1 >= 0 && i + 1 < column && j + 1 < row && board[i + 1][j + 1].getMine()) {
                nearby++;
            }
            if (i - 1 >= 0 && j + 1 >= 0 && i - 1 < column && j + 1 < row && board[i - 1][j + 1].getMine()) {
                nearby++;
            }
            board[i][j].setNum(nearby);
        }
    }
    return mineCount;
}

int getRow(vector<vector<Tile>>& board)
{
    return board[0].size();
}

int getColumn(vector<vector<Tile>>& board)
{
    return board.size();
}
