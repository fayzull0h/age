#include "Collision.h"
#include "Item.h"
#include "Rectangle.h"
#include "Single.h"

ErrorCode Collision::checkCollision() {
  Rectangle *r1 = dynamic_cast<Rectangle*>(it1), *r2 = dynamic_cast<Rectangle*>(it2);
  Single *s1 = dynamic_cast<Single*>(it1), *s2 = dynamic_cast<Single*>(it2);

  if (r1 && r2) {
    if ((r1->getY() < r2->getY()+r2->getHeight()) && (r1->getY()+r1->getHeight() > r2->getY())) {
      // r1 hits r2 from left
      if ((r1->getXV() > 0) && (r1->getX()+r1->getWidth()+r1->getXV() >= r2->getX()) && (r1->getX()+r1->getWidth() < r2->getX()))
        return collide(FromLeft);
      // r1 hits r2 from right 
      else if ((r1->getXV() < 0) && (r1->getX()+r1->getXV() <= r2->getX()+r2->getWidth() && (r1->getX() > r2->getX()+r2->getWidth())))
        return collide(FromRight);
    }
    else if ((r1->getX() < r2->getX()+r2->getWidth()) && (r1->getX()+r1->getWidth() > r2->getX())) {
      // r1 hits r2 from the top
      if ((r1->getYV() > 0) && (r1->getY()+r1->getHeight()+r1->getYV() >= r2->getY()) && (r1->getY()+r1->getHeight() < r2->getY()))
        return collide(FromTop);
      // r1 hits r2 from the bottom
      else if ((r1->getYV() < 0) && (r1->getY()+r1->getYV() <= r2->getY()+r2->getHeight() && (r1->getY() > r2->getY()+r2->getHeight())))
        return collide(FromBottom);
    }
  } 
  
  else if (r1 && s2) {
    if ((s2->getY() >= r1->getY()) && (s2->getY() < r1->getY()+r1->getHeight())) {
      // r1 hits s2 from left
      if ((r1->getXV() > 0) && (r1->getX()+r1->getWidth()+r1->getXV() >= s2->getX()) && (r1->getX()+r1->getWidth() < s2->getX()))
        return collide(FromLeft);
      // r1 hits s2 from right
      if ((r1->getXV() < 0) && (r1->getX()+r1->getXV() <= s2->getX()) && (r1->getX() < s2->getX()))
        return collide(FromRight);
    }
    else if ((s2->getX() >= r1->getX()) && (s2->getX() < r1->getX()+r1->getWidth())) {
      // r1 hits s2 from top
      if ((r1->getYV() > 0) && (r1->getY()+r1->getHeight()+r1->getYV() >= s2->getY()) && (r1->getY()+r1->getHeight() < s2->getY()))
        return collide(FromTop);
      // r1 hits s2 from bottom
      if ((r1->getYV() < 0) && (r1->getY()+r1->getYV() <= s2->getY()) && (r1->getY() > s2->getY()))
        return collide(FromBottom);
    }
  } 
  
  else if (s1 && r2) {
    if ((s1->getY() >= r2->getY()) && (s1->getY() < r2->getY()+r2->getHeight())) {
      // s1 hits r2 from left
      if ((s1->getXV() > 0) && (s1->getX()+s1->getXV() >= r2->getX()) && (s1->getX() < r2->getX()))
        return collide(FromLeft);
      // s1 hits r2 from right
      if ((s1->getXV() < 0) && (s1->getX()+s1->getXV() <= r2->getX()+r2->getWidth()) && (s1->getX() > r2->getX()+r2->getWidth()))
        return collide(FromRight);
    }
    else if ((s1->getX() >= r2->getX()) && (s1->getX() < r2->getX()+r2->getWidth())) {
      // s1 hits r2 from the top
      if ((s1->getYV() > 0) && (s1->getY()+s1->getYV() >= r2->getY()) && (s1->getY() < r2->getY()))
        return collide(FromTop);
      // s1 hits r2 from the bottom
      if ((s1->getYV() < 0) && (s1->getY()+s1->getYV() <= r2->getY()+r2->getHeight()) && (s1->getY() > r2->getY()+r2->getHeight()))
        return collide(FromBottom);
    }
  } 
  
  else if (s1 && s2) {
    if (s1->getY() == s2->getY() && s1->getX() == s2->getX()) {
      // s1 hits s2 from left
      if ((s1->getXV() > 0))
        return collide(FromLeft);
      // s1 hits s2 from right
      if ((s1->getXV() < 0))
        return collide(FromRight);
      // s1 hits s2 from the top
      if ((s1->getYV() > 0))
        return collide(FromTop);
      // s1 hits s2 from the bottom
      if ((s1->getYV() < 0))
        return collide(FromBottom);
    }
  }
  return NoMovement;
}

Collision::~Collision() {
  if (it1) it1 = nullptr;
  if (it2) it2 = nullptr;
}

ErrorCode BounceCollision::collide(CollisionCode code) {
  switch(code) {
    case FromLeft:
      it1->reverseXV();
      if (it2->getXV() < 0) it2->stopXV();
      return Success;
    case FromRight:
      it1->reverseXV();
      if (it2->getXV() > 0) it2->stopXV();
      return Success;
    case FromTop:
      it1->reverseYV();
      if (it2->getYV() < 0) it2->stopXV();
      break;
    case FromBottom:
      it1->reverseYV();
      if (it2->getYV() > 0) it2->stopXV();
      break;
    default:
      return NoMovement;
  }
  return Collided;
}

ErrorCode DestroyCollision::collide(CollisionCode code) {
  switch(code) {
    case FromLeft:
      it1->reverseXV();
      if (it2->getXV() < 0) it2->stopXV();
      return Success;
    case FromRight:
      it1->reverseXV();
      if (it2->getXV() > 0) it2->stopXV();
      return Success;
    case FromTop:
      it1->reverseYV();
      if (it2->getYV() < 0) it2->stopXV();
      break;
    case FromBottom:
      it1->reverseYV();
      if (it2->getYV() > 0) it2->stopXV();
      break;
    default:
      return NoMovement;
  }
  return DeleteOther;
}

ErrorCode StopCollision::collide(CollisionCode code) {
  it1->stopXV();
  it2->stopXV();
  it1->stopYV();
  it2->stopYV();
  return Collided;
}

ErrorCode WinCollision::collide(CollisionCode code) {
  return GameWon;
}

