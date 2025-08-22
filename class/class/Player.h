#pragma once
#include <string>

class Player {
protected:
    std::string job_name;
    int HP = 0;

public:
    virtual void attack() = 0;
    virtual ~Player() = default;
};
