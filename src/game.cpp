#include "game.h"
#include <SDL2/SDL.h>
#include <iostream>

bool Game::Initialize() {
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#ifdef __linux__
  std::string glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
#endif
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI);
  mWindow =
      SDL_CreateWindow("pong cpp", 0, 0, WINDOW_W, WINDOW_H, window_flags);
  SDL_SetWindowMinimumSize(mWindow, 500, 480);
  SDL_GLContext gl_context = SDL_GL_CreateContext(mWindow);

  if (!gl_context) {
    SDL_Log("Failed to create GL Context: %s", SDL_GetError());
    return false;
  }
  SDL_GL_SetSwapInterval(1);
  SDL_GL_MakeCurrent(mWindow, gl_context);
  if (!mWindow) {
    SDL_Log("Faild to create window: %s", SDL_GetError());
    return false;
  }
  mRenderer = SDL_CreateRenderer(
      mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!mRenderer) {
    SDL_Log("Failed to create Renderer: %s", SDL_GetError());
  }
  glViewport(0, 0, WINDOW_W, WINDOW_H);

  return true;
}

void Game::UpdateGame() {
  // wait for 16ms to elaps for next frame
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    ;
  // delta time is the diff in ticks from last frame
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
  // clamp max delta time
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }
  mTicksCount = SDL_GetTicks();
  mBall.pos.x += mBall.vel.x * deltaTime;
  mBall.pos.y += mBall.vel.y * deltaTime;
  if (mPaddle.move != 0) {
    mPaddle.pos.y += mPaddle.move * 300.0f * deltaTime;
    // Clamp paddle to screen
    if (mPaddle.pos.y < (mPaddle.height / 2.0f + THICKNESS)) {
      mPaddle.pos.y = mPaddle.height / 2.0f + THICKNESS;
    } else if (mPaddle.pos.y > (WINDOW_H - mPaddle.width)) {
      mPaddle.pos.y = WINDOW_H - mPaddle.width;
    }
  }
}

void Game::RenderOutput() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  // SDL_SetRenderDrawColor(mRenderer, 90, 90, 90, 255);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  SDL_Rect top_wall{0, 0, WINDOW_W, THICKNESS};
  SDL_Rect bottom_wall{0, WINDOW_H - THICKNESS, WINDOW_W, THICKNESS};
  SDL_Rect right_wall{WINDOW_W - THICKNESS, 0, THICKNESS, WINDOW_H};
  SDL_Rect ball{static_cast<int>((mBall.pos.x + THICKNESS)),
                static_cast<int>((mBall.pos.y - THICKNESS)), mBall.height,
                mBall.width};
  SDL_Rect paddle{static_cast<int>((mPaddle.pos.x + THICKNESS)),
                  static_cast<int>((mPaddle.pos.y - THICKNESS)), mPaddle.height,
                  mPaddle.width};

  SDL_RenderFillRect(mRenderer, &top_wall);
  SDL_RenderFillRect(mRenderer, &bottom_wall);
  SDL_RenderFillRect(mRenderer, &right_wall);
  SDL_RenderFillRect(mRenderer, &paddle);
  SDL_RenderFillRect(mRenderer, &ball);
  // Pointless RGB based on ball's velocity
  glClearColor(abs(((float)(mBall.vel.x / 1000.0f + 0.2f) + (float)(mBall.vel.y / 1000.0f))), abs(mBall.vel.x / 1000.0f), abs(mBall.vel.y / 1000.0f), 1.0f);
  SDL_RenderPresent(mRenderer);
}