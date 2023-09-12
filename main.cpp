#include "src/game.cpp"
#include "src/input.h"
#include "src/physics.h"

#include <iostream>
#include <memory>



void Game::RunLoop() {
  while (mIsRunning) {
    ProccessInput();
    UpdateGame();
    CheckCollision();
    RenderOutput();
  }
}

int main() {
  std::srand(static_cast<unsigned int>(time(nullptr)));
  WINDOW_H = 768;
  WINDOW_W = 1024;
  THICKNESS = 20;
  Game game;

  bool success = game.Initialize();
  if (success) {
    std::cout << "Launching Game" << std::endl;
    game.RunLoop();
  }
  return 0;
}
