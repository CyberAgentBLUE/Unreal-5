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
    cout << "닉네임을 입력하세요: ";
    cin >> name;

    int choice = 0;
    cout << "직업을 선택하세요 (1.전사 2.마법사 3.도적 4.궁수): ";
    cin >> choice;

    Player* p = nullptr;
    switch (choice) {
    case 1: p = new Warrior(name);  break;  // ← 닉네임 전달
    case 2: p = new Magician(name); break;
    case 3: p = new Thief(name);    break;
    case 4: p = new Archer(name);   break;
    default:
        cout << "잘못된 선택입니다." << endl;
        return 0;
    }

    p->attack();
    delete p;
    return 0;
}
