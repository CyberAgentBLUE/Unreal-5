#include "Magician.h"
#include <iostream>
using namespace std;

Magician::Magician(const std::string& nickname) {
    job_name = "마법사";
    HP = 60;
    cout << "* " << nickname << " 님이 마법사로 전직하였습니다.\n";
}

void Magician::attack() {
    cout << "* 불볼트를 시전한다!\n";
}
