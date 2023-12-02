#include "engine.hpp"

void Engine::update() {

  if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
    Vector2f thisSectionPosition = snake[0].getPosition();
    Vector2f lastSectionPosition = thisSectionPosition;


    if (!directionQueue.empty()) {

      switch (snakeDirection) {
        case Direction::UP:
          if (directionQueue.front() != Direction::DOWN) {
            snakeDirection = directionQueue.front();
          }
          break;
        case Direction::DOWN:
          if (directionQueue.front() != Direction::UP) {
            snakeDirection = directionQueue.front();
          }
          break;
        case Direction::LEFT:
          if (directionQueue.front() != Direction::RIGHT) {
            snakeDirection = directionQueue.front();
          }
          break;
        case Direction::RIGHT:
          if (directionQueue.front() != Direction::LEFT) {
            snakeDirection = directionQueue.front();
          }
          break;
      }
      directionQueue.pop_front();
    }

    score += snake.size() * (applesEatenTotal + 1);
    scoreText.setString(to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));


    if(sectionsToAdd)
    {
        addSnakeSection() ;
        sectionsToAdd-- ;
    }

    switch (snakeDirection) {
      case Direction::RIGHT:
        snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
        break;
      case Direction::DOWN:
        snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
        break;
      case Direction::LEFT:
        snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
        break;
      case Direction::UP:
        snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
        break;
    }


    for (int s = 1; s < snake.size(); s++) {
      thisSectionPosition = snake[s].getPosition();
      snake[s].setPosition(lastSectionPosition);
      lastSectionPosition = thisSectionPosition;
    }


    for (auto & s : snake) {
      s.update();
    }

    if(snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds()))
    {

        applesEatenThisLevel += 1;
        applesEatenTotal += 1;
        applesEatenText.setString("apples " + to_string(applesEatenTotal));
        FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
        applesEatenText.setPosition(
            Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

        bool beginningNewLevel = false;
        if (applesEatenThisLevel >= 10)
        {
          if (currentLevel < maxLevels)
          {
          beginningNewLevel = true;
          beginNextLevel();
          }
        }


        if (!beginningNewLevel)
        {
          sectionsToAdd += 4;
          speed++;
          moveApple();
        }
    }

     for (int s = 1; s < snake.size(); s++)
    {
         if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds()))
        {
             currentGameState = GameState::GAMEOVER;
        }
    }
    for (auto & w : wallSections)
    {
        if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds()))
        {
            currentGameState = GameState::GAMEOVER;
        }
    }

    timeSinceLastMove = Time::Zero;
  }
}
