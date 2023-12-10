#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstddef>
#include <vector>
#include <metadata.h>

class Item;

class GameState {
  std::vector<Item *> items;
 public:
  ErrorCode addItem(Item *i) { 
    items.emplace_back(i);
    return ErrorCode::Success;
  }

  ErrorCode 
  
};

#endif
