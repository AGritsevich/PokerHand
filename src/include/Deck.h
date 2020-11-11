#pragma once 

#include <vector>
#include <deque>

#include "Types.h"


class Deck {
public:
  Deck();
  ~Deck() {};

  void shuffle();

private:
  Deck(const Deck&) {};
  std::deque<types::Card> get_new();
  void clear();

  std::vector<types::Card> deck_;
};