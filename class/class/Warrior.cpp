#include "Warrior.h"
#include <iostream>
using namespace std;

Warrior::Warrior(const std::string& nickname) {
    job_name = "����";
    HP = 80;
    cout << "* " << nickname << " ���� ����� �����Ͽ����ϴ�.\n";
}

void Warrior::attack() {
    cout << "* ����� �ֵθ���!\n";
}
