#include"engine.hpp"

void Engine::input()
{
    Event event{} ;

    while(window.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            window.close() ;
        }
        if(event.type == Event::KeyPressed)
        {
             if (event.key.code == Keyboard::Escape)
             {
                  window.close();
             }

             if (Keyboard::isKeyPressed(Keyboard::Pause))
            {
                  togglePause();
            }

            if(currentGameState == GameState::GAMEOVER)
            {
                if(event.key.code == Keyboard::Enter)
                {
                    startTheGame() ;
                }
            }


             if(event.key.code == Keyboard::Up)
             {
                 addDirection(Direction::UP) ;
             }
             else if(event.key.code == Keyboard::Down)
             {
                 addDirection(Direction::DOWN) ;
             }
             else if(event.key.code == Keyboard::Right)
             {
                 addDirection(Direction::RIGHT) ;
             }
             else if(event.key.code == Keyboard::Left)
             {
                 addDirection(Direction::LEFT) ;
             }
        }
    }
}

void Engine::addDirection(int newDirection)
{
    if(directionQueue.empty())
    {
        directionQueue.emplace_back(newDirection) ;
    }
    else
    {
        if(directionQueue.back() != newDirection)
        {
            directionQueue.emplace_back(newDirection) ;
        }
    }
}
