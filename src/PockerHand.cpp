#include "Log.hpp"
#include "PockerHand.h"

PockerHand::PockerHand() {
  enabled_ = true;
}

void PockerHand::disable() {
  if (thread_->joinable()) {
    thread_->join();
  }
}

bool PockerHand::isFlash(const types::Hand& one) {
  using namespace types;
  
  for (auto i = 1; i < (sizeof(one) / sizeof(Card)); i++) {
    if (one[0].suit_ != one[i].suit_) 
      return false;
  }
  return true;
}

int32_t compare(const void* a, const void* b) { 
  return (*(int8_t*)a - *(int8_t*)b); 
}

bool PockerHand::isStraight(types::Hand one) {
  using namespace types;

  std::qsort(one, sizeof(Hand) / sizeof(Card), sizeof(Card), compare);

  for (auto i = 1; i < (sizeof(one) / sizeof(Card)); i++) {
    if (one[i-1].rank_ != static_cast<Rank>(static_cast<uint8_t>(one[i].rank_) + 1))
      return false;
  }
  return true;
}

void PockerHand::proceed(std::string message) {
  using namespace types;
  Hand some_hand = parse(message);

  if (isStraight()) {
    log::lg << "Straight";
  }
}