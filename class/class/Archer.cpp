#include "Archer.h"
#include <iostream>
using namespace std;

Archer::Archer(const std::string& nickname) {
    job_name = "�ü�";
    HP = 75;
    cout << "* " << nickname << " ���� �ü��� �����Ͽ����ϴ�.\n";
}

void Archer::attack() {
    cout << "* ȭ���� �߻��Ѵ�!\n";
}
