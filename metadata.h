#ifndef METADATA
#define METADATA 
#include <cstddef>
#include <string>

enum class ErrorCode{
  /* Success */
  Success = 0,
  
  /* Failures */
  BadRequest = 400,
  NoMovement = 401

};

struct Info {
  int x, y, z;
};

struct Status {
  std::string status;
  int value;
};

/* State types are:
*/
enum class StateType {
  NoChange,
  Items,
  Stats,
  All
};

struct State {
  StateType type;
};

#endif
