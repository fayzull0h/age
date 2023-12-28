#include "GameState.h"
#include "Item.h"
#include "Collision.h"
#include "metadata.h"

ErrorCode GameState::addStat(const Status &s) {
  if (stats.size() < 3) stats.emplace_back(s);
  else return BadRequest;
  return Success;
}

ErrorCode GameState::addItem(Item *it) {
  if (items.size() == 0) {
    items.emplace_back(it);
    return BadRequest;
  }

  bool inserted = false;
  for (size_t i = 0, c = items.size(); i < c; ++i) {
    if (it->getZ() <= items[i]->getZ()) {
      items.insert(items.begin()+i, it);
      inserted = true;
      break;
    }
  }
  if (!inserted) items.emplace_back(it);
  return Success;
}

ErrorCode GameState::addPlayer(Item *p) {
  if (p) { 
    player = p;
    addItem(p);
  } else return BadRequest;
  return Success;
}

ErrorCode GameState::deleteItem(Item *it) {
  for (size_t i = 0, c = collisions.size(); i < c; ++i) {
    if ((collisions[i]->getItem1() == it) || (collisions[i]->getItem2() == it))
      collisions.erase(collisions.begin()+i);
  }

  for (size_t i = 0, c = items.size(); i < c; ++i) {
    if (items[i] == it) items.erase(items.begin()+i);
  }
  return Success;
}

ErrorCode GameState::addCollision(Collision *c) {
  if (c) collisions.emplace_back(c);
  else throw BadRequest;
  return Success;
}
