#include "Thief.h"
#include <iostream>
using namespace std;

Thief::Thief(const std::string& nickname) {   // �� ����� ������ �ñ״�ó
    job_name = "����";
    HP = 70;
    cout << "* " << nickname << " ���� �������� �����Ͽ����ϴ�.\n";
}

void Thief::attack() {
    cout << "* �ܰ����� ������ �����!\n";
}
