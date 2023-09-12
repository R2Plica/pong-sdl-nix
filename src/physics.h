#ifndef SRC_PHYSICS_H_
#define SRC_PHYSICS_H_
#include "game.h"
void Game::CheckCollision() {
  float distance = abs(((mPaddle.pos.y - mBall.pos.y) * 2) +
                       ((mPaddle.pos.x - mBall.pos.x) * 2));
  //// COLLIDE WITH PADDLE
  if (abs(distance - mPaddle.width) <= mPaddle.width && mBall.vel.x < 0.0f &&
      mBall.pos.x <= THICKNESS + mPaddle.pos.x && mBall.pos.x >= 0.0f) {
    if (mPaddle.move < 0) {
      if (mBall.vel.y >= 0.0f) {
        mBall.vel.x *= -1.5f;
        mBall.vel.y *= -0.5f;
      } else {
        mBall.vel.y *= 1.5f;
        mBall.vel.x *= -1.5f;
      }
    } else if (mPaddle.move > 0) {
      if (mBall.vel.y <= 0.0f) {
        mBall.vel.x *= -1.5f;
        mBall.vel.y *= -0.5f;
      } else {
        mBall.vel.y *= 1.5f;
        mBall.vel.x *= -1.5f;
      }
    } else {
      mBall.vel.x *= -0.8f;
    }
  }

  // //// Collide with top wall
  if (mBall.pos.y <= THICKNESS && mBall.vel.y < 0.0f) {
    mBall.vel.y *= -1.0f;
  }
  //// Collide with Right wall
  if (mBall.pos.x >= WINDOW_W - THICKNESS && mBall.vel.x > 0.0f) {
    mBall.vel.x *= -1.0f;
  }
  // //DEBUG:
  // Collide with Left wall
  // if (mBall.pos.x <= 0.0f + THICKNESS && mBall.vel.x < 0.0f) {
  //   mBall.vel.x *= -1.0f;
  // }

  ///// Collide with bottom wall
  if (mBall.pos.y >= WINDOW_H - THICKNESS && mBall.vel.y > 0.0f) {
    mBall.vel.y *= -1.0f;
  }

  // TODO: add a keybind to perform the reset of the ball
  //
  //   // RESET BALL when missed;
  if (mBall.pos.x < -100.0f) {
    mBall.pos.x = WINDOW_W / 2;
    mBall.pos.y = WINDOW_H / 2;
    mBall.vel.x = 180.0f;
  }
  // Ball moving too slow
  if (mBall.vel.x <= 230.0f && mBall.vel.x >= -230.0f ) {
    mBall.vel.x *= 1.10f;
  }
  // Ball moving too fast
  if (mBall.vel.x >= 900.0f || mBall.vel.x <= -900.0f) {
    mBall.vel.x *=0.2f;
  }
}

#endif
