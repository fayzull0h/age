#ifndef METADATA
#define METADATA 
#include <cstddef>
#include <string>

enum ErrorCode{
  /* Success */
  Success = 200,

  /* Other messages */
  NoMovement = 300,
  Deleted = 301,
  DeleteOther = 302,
  DeleteMe = 303,
  DeleteBoth = 304,
  Collided = 305,
  LowerWallCollision = 306,
  UpperWallCollision = 307,
  RightWallCollision = 308,
  LeftWallCollision = 309,

  /* Game Logic */
  GameStart = 400,
  GameContinue = 401,
  GameExit = 402,
  GameWon = 403,
  GameLost = 404,
  GameOver = 405,
  
  /* Failures */
  BadRequest = 500,
  InitFailure = 501,
  DrawFailure = 502,
  OutOfRange = 503
};

enum BoardType { Solid, View };

enum CollisionCode {
  FromTop,
  FromRight,
  FromBottom,
  FromLeft,
  PassThrough,
  Bounce,
  Stop
};

struct Status {
  std::string status;
  int value;
};

struct Triple {
  int x, y;
  char c;
};

#endif
