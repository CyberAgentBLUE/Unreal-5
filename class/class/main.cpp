#include <iostream>   
#include <string>     
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    string name;
    cout << "�г����� �Է��ϼ���: ";
    cin >> name;

    int choice = 0;
    cout << "������ �����ϼ��� (1.���� 2.������ 3.���� 4.�ü�): ";
    cin >> choice;

    Player* p = nullptr;
    switch (choice) {
    case 1: p = new Warrior(name);  break;  // �� �г��� ����
    case 2: p = new Magician(name); break;
    case 3: p = new Thief(name);    break;
    case 4: p = new Archer(name);   break;
    default:
        cout << "�߸��� �����Դϴ�." << endl;
        return 0;
    }

    p->attack();
    delete p;
    return 0;
}
