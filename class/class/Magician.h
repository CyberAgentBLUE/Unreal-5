#pragma once
#include "Player.h"
#include <string>

class Magician : public Player {
public:
    explicit Magician(const std::string& nickname);
    void attack() override;
};
