#pragma once
#include "Player.h"
#include <string>   // ← 추가

class Thief : public Player {
public:
    explicit Thief(const std::string& nickname);  // ← 헤더 선언과
    void attack() override;                        //    cpp 구현을 100% 일치
};
