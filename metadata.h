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
  VerticalWallCollision = 306,
  HorizontalWallCollision = 307,
  Resize = 308,

  /* Game Logic */
  GameStart = 400,
  GameContinue = 401,
  GameExit = 402,
  GameWon = 403,
  GameLost = 404,
  
  /* Failures */
  BadRequest = 500,
  InitFailure = 501,
  DrawFailure = 502
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
