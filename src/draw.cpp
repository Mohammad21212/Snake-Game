#include "engine.hpp"

void Engine::draw() {
  window.clear(Color::Black);

  for (auto & w : wallSections) {
  window.draw(w.getShape());
  }
  window.draw(apple.getSprite());

  for (auto & s : snake) {
  window.draw(s.getShape());
}
  window.draw(titleText) ;
  window.draw(currentLevelText);
  window.draw(applesEatenText);
  window.draw(scoreText);

  if (currentGameState == GameState::GAMEOVER)
    {
       window.draw(gameOverText);
       window.draw(pressEnterText);
    }

  window.display() ;
}


