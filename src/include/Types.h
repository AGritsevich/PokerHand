#pragma once
#include <cstdint>

namespace types {
  constexpr auto RANK_START_LINE = __LINE__;
  enum class Rank : uint8_t {
    none = 0,
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
  };
  constexpr auto RANK_COUNT = __LINE__ - RANK_START_LINE - 4;

  constexpr auto SUIT_START_LINE = __LINE__;
  enum class Suit : uint8_t {
    none = 0,
    Hearts,
    Diamonds,
    Clubs,
    Spades
  };
  constexpr auto SUIT_COUNT = __LINE__ - SUIT_START_LINE - 4;
  
  struct Card {
    Rank rank_;
    Suit suit_;

    Card() {
      this->rank_ = Rank::none;
      this->suit_ = Suit::none;
    };

    Card(uint8_t rank, uint8_t suit) {
      this->rank_ = static_cast<Rank>(rank);
      this->suit_ = static_cast<Suit>(suit);
    };
  };

  static constexpr uint8_t DECK_SIZE = RANK_COUNT * SUIT_COUNT;
  static constexpr uint8_t HAND_SIZE = 5u;
  using Hand = Card[HAND_SIZE];
} // namespace types