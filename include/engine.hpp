#ifndef ENGINE_HPP
#define ENGINE_HPP

#include"SnakeSection.hpp"
#include"apple.hpp"
#include"Wall.hpp"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<vector>
#include<deque>
#include<fstream>


using namespace sf ;
using namespace std ;

class Engine
{
    private:

        Vector2f  resolution ;
        RenderWindow  window ;
        const unsigned int FPS = 60 ;
        static const Time TimePerFrame ;
        vector<SnakeSection> snake ;
        int snakeDirection ;
        int speed ;
        int sectionsToAdd ;

        int applesEatenThisLevel ;
        int applesEatenTotal ;
        unsigned long long int score ;


        Apple apple ;

        vector<Wall> wallSections ;

        int currentLevel ;
        int maxLevels ;
        vector<String> levels ;

        Font mainFont ;
        Text titleText ;
        Text applesEatenText ;
        Text currentLevelText ;
        Text scoreText ;
        Text gameOverText;
        Text pressEnterText;

        Time timeSinceLastMove ;
        int currentGameState ;
        int lastGameState ;
        deque<int> directionQueue ;

    public:

        enum Direction {UP , DOWN , LEFT , RIGHT} ;
        enum GameState {RUNNING , PAUSED , GAMEOVER};

        Engine() ;

        void input() ;

        void addDirection(int newDirection) ;

        void update() ;

        void draw() ;

        static void setupText(Text *textItem, const Font &font, const String &value, int size, Color colour);

        void newSnake() ;

        void addSnakeSection() ;

        void moveApple() ;

        void checkLevelFiles() ;

        void loadLevel(int levelNumber) ;

        void beginNextLevel() ;

        void startTheGame() ;

        void togglePause();

        void run() ;

};

#endif // ENGINE_HPP
