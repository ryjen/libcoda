#include <iostream>
#include <random>

#include <seamwork/studies/yahtzee_randomness.hpp>

namespace sw = seamwork::studies::yahtzee;

void print(const sw::hand& hand)
{
    for (std::size_t index = 0; index < sw::dice_per_hand; ++index) {
        if (index != 0) {
            std::cout << ' ';
        }
        std::cout << sw::value(hand[index]);
        if (hand.is_held(index)) {
            std::cout << '*';
        }
    }
    std::cout << '\n';
}

int main()
{
    std::random_device entropy;
    sw::uniform_face_source source{std::mt19937{entropy()}};

    auto hand = sw::initial_roll(source);
    print(hand);

    hand = hand.with_hold(0).with_hold(2);
    hand = sw::reroll(hand, source);
    print(hand);
}
