#include "Player.hpp"
#include "Serializer/Serializer.hpp"
#include <iostream>

Player::Player() : Life("undefined", 10, 10)
{
}

Player::Player(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana)
{
}

Player::~Player() {
    
}

void Player::load(Serializer &s)
{
    Life::load(s);
    s.load(inventory);
}

void Player::save(Serializer &s) const
{
    Life::save(s);
    s.save(inventory);
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

void Player::heal(int64_t value) {
    hp+=value;
    if(hp>hpmax) if(value < 0) hp = 0; else hp = hpmax;

}
