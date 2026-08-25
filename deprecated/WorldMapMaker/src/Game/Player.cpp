#include "Player.hpp"
#include <iostream>

Player::Player() : Life("undefined", 10, 10)
{
}

Player::Player(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana)
{
}

void Player::load(Serializer &s)
{
    Life::load(s);
}

void Player::save(Serializer &s) const
{
    Life::save(s);
}

TypeEntity Player::type() {
    return TypeEntity::_Player;
}
void Player::process(long double delta, uint64_t tick)
{
}

void Player::render(long double delta, uint64_t tick)
{
}

void Player::debug_print()
{
    std::cout << "player" << std::endl;
    Life::debug_print();
}
