#include "Engine.h"
#include "Single.h"
#include "GameBoard.h"
#include "metadata.h"
#include "PeriodicMovement.h"
#include "Rectangle.h"
#include "Item.h"

#include <iostream>

int main() { 
  Engine e = Engine();
  Status s1{"Lives", 10};
  Rectangle<Full> fr{1, 1, 0, 3, 4, '#'}; 
  Rectangle<Hollow> hr{1, 18, 0, 4, 6, 'H'};

  PeriodicMovement frmove(0, 1, 0, 0);
  fr.setMovement(frmove);
  hr.setMovement(frmove);

  GameBoard gb = GameBoard();
  e.addGameBoard(&gb);
  e.addItem(&fr);
  e.addItem(&hr);
  e.addStat(s1);
  fr.draw(gb.getBoard());
  wrefresh(gb.getBoard());
  e.go();
}
