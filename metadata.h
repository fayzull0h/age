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
  
  /* Failures */
  BadRequest = 400,
  InitFailure = 401,
  DrawFailure = 402
};

enum CollisionCode {
  FromTop,
  FromRight,
  FromBottom,
  FromLeft,
  PassThrough,
  Bounce,
  Stop,
  DeleteMe,
  DeleteOther,
  DeleteBoth
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
