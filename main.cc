#include "Engine.h"
#include "Single.h"
#include "GameBoard.h"
#include "metadata.h"
#include "PeriodicMovement.h"
#include "Rectangle.h"

#include <iostream>

int main() { 
  Engine e = Engine();
  Status s1{"Lives", 10};
  FullRectangle fr{1, 1, 0, 3, 4, '#'}; 

  PeriodicMovement frmove(4, 1, 1, 0);
  fr.setMovement(&frmove);

  GameBoard gb = GameBoard();
  e.addGameBoard(&gb);
  e.addItem(&fr);
  e.addStat(s1);
  e.go();
}
