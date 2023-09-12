#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#include <iostream>
// // TODO: change this code to something better :(
int WINDOW_H = 500;
int WINDOW_W = 500;
int THICKNESS = 20;

struct G_Vector {
  int x;
  int y;
  G_Vector() : x(0), y(0) {}
  G_Vector(int a, int b) : x(a), y(b) {}
};
struct Paddle {
  G_Vector pos;
  int height;
  int width;
  int move;
  Paddle(int x, int y, int w, int h, int mov) {
    pos.x = x;
    pos.y = y;
    height = h;
    width = w;
    move = mov;
  }
  Paddle() : pos(0, WINDOW_H / 2), height(10), width(150), move(0) {}
};

struct Ball {
  G_Vector pos;
  G_Vector vel;
  int height;
  int width;
  Ball()
      : pos(WINDOW_W / 2, WINDOW_H / 2),
        vel(((float)(rand() % 200) + 210.0f), -(float)(rand() % 200) + 210.0f),
        height(10), width(10) {}
};
class Game {
public:
  bool Initialize();
  void RunLoop();
  void CheckCollision();
  void Shutdown();
  ~Game() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
  }

private:
  void ProccessInput();
  void UpdateGame();
  void RenderOutput();
  Ball mBall;
  Paddle mPaddle;
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  bool mIsRunning = true;
  uint32_t mTicksCount = 0;
};

#endif
