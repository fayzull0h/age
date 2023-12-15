#ifndef METADATA
#define METADATA 
#include <cstddef>
#include <string>

enum ErrorCode{
  /* Success */
  Success = 200,
  GameWon = 201,

  /* Other messages */
  NoMovement = 300,
  Deleted = 301,
  DeleteOther = 302,
  DeleteMe = 303,
  DeleteBoth = 304,
  Collided = 305,
  
  /* Failures */
  BadRequest = 400,
  InitFailure = 401,
  DrawFailure = 402
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
