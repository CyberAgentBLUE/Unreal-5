#include "Magician.h"
#include <iostream>
using namespace std;

Magician::Magician(const std::string& nickname) {
    job_name = "������";
    HP = 60;
    cout << "* " << nickname << " ���� ������� �����Ͽ����ϴ�.\n";
}

void Magician::attack() {
    cout << "* �Һ�Ʈ�� �����Ѵ�!\n";
}
