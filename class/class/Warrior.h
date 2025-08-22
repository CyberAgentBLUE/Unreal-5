#pragma once
#include "Player.h"
#include <string>

class Warrior : public Player {
public:
    explicit Warrior(const std::string& nickname);
    void attack() override;
};
