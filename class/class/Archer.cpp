#include "Archer.h"
#include <iostream>
using namespace std;

Archer::Archer(const std::string& nickname) {
    job_name = "궁수";
    HP = 75;
    cout << "* " << nickname << " 님이 궁수로 전직하였습니다.\n";
}

void Archer::attack() {
    cout << "* 화살을 발사한다!\n";
}
