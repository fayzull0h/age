#ifndef METADATA
#define METADATA 
#include <cstddef>
#include <string>

class Item;

enum ErrorCode{
  /* Success */
  Success = 200,

  /* Other messages */
  DeleteMe = 300,
  NoMovement = 301,
  DeleteMove = 302,
  
  /* Failures */
  BadRequest = 400,
  InitFailure = 401,
  DrawFailure = 402
};

enum CollisionType {
  PassThrough,
  Stop
};

struct Collision {
  CollisionType ct;
  Item *me;
  Item *other;
};

struct Status {
  std::string status;
  int value;
};

struct Triple {
  int x, y;
  char c;
};

/* State types are:
*/
enum StateType {
  NoChange,
  Items,
  Stats,
  All
};

struct EngineState {
  StateType type;
};

#endif
