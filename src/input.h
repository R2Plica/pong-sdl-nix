#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

#include "game.h"

void Game::ProccessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    case SDL_WINDOWEVENT:
      switch (event.window.event) {
      case SDL_WINDOWEVENT_RESIZED:
        WINDOW_W = event.window.data1;
        WINDOW_H = event.window.data2;
        glViewport(0, 0, WINDOW_W, WINDOW_H);
        break;
      }
      break;
    }
    const static Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
      mIsRunning = false;
    }
    // POLL PADDLE EVENTS

    mPaddle.move = 0;
    if (state[SDL_SCANCODE_W]) {
      mPaddle.move -= 2;
    }
    if (state[SDL_SCANCODE_S]) {
      mPaddle.move += 2;
    }
  }
}

#endif
