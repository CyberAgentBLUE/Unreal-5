#pragma once
#include "Player.h"
#include <string>   // �� �߰�

class Thief : public Player {
public:
    explicit Thief(const std::string& nickname);  // �� ��� �����
    void attack() override;                        //    cpp ������ 100% ��ġ
};
