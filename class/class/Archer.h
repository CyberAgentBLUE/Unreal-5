#pragma once
#include "Player.h"
#include <string>   // ¡ç Ãß°¡

class Archer : public Player {
public:
    explicit Archer(const std::string& nickname);
    void attack() override;
};
