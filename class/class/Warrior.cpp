#include "Warrior.h"
#include <iostream>
using namespace std;

Warrior::Warrior(const std::string& nickname) {
    job_name = "전사";
    HP = 80;
    cout << "* " << nickname << " 님이 전사로 전직하였습니다.\n";
}

void Warrior::attack() {
    cout << "* 장검을 휘두른다!\n";
}
