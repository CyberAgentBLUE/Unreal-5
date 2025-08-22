#include "Thief.h"
#include <iostream>
using namespace std;

Thief::Thief(const std::string& nickname) {   // ← 헤더와 동일한 시그니처
    job_name = "도적";
    HP = 70;
    cout << "* " << nickname << " 님이 도적으로 전직하였습니다.\n";
}

void Thief::attack() {
    cout << "* 단검으로 빠르게 베어낸다!\n";
}
