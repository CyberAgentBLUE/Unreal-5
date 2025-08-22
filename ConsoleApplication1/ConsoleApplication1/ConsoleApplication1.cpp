#include <iostream>
using namespace std;

int main() {
    // 기준값(고정)
    const int TARGET_HP = 60;
    const int TARGET_MP = 60;
    const int TARGET_ATK = 30;
    const int TARGET_DEF = 30;

    int hp, mp, atk, def;
    int hpPotion = 5, mpPotion = 5;

    // HP, MP 입력 검증 루프
    while (true) {
        cout << "HP와 MP를 입력해주세요: ";
        if (!(cin >> hp >> mp)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요.\n";
            continue;
        }
        if (hp < TARGET_HP || mp < TARGET_MP) {
            cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요.\n";
        }
        else if (hp > TARGET_HP || mp > TARGET_MP) {
            cout << "HP나 MP의 값이 너무 큽니다. 다시 입력해주세요.\n";
        }
        else {
            break; // 정확히 맞으면 통과
        }
    }

    // ATK, DEF 입력 검증 루프 (원하면 유지, 아니면 한 번만 입력받게 바꿔도 됨)
    while (true) {
        cout << "공격력과 방어력을 입력해주세요: ";
        if (!(cin >> atk >> def)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요.\n";
            continue;
        }
        if (atk < TARGET_ATK || def < TARGET_DEF) {
            cout << "공격력이나 방어력의 값이 너무 작습니다. 다시 입력해주세요.\n";
        }
        else if (atk > TARGET_ATK || def > TARGET_DEF) {
            cout << "공격력이나 방어력의 값이 너무 큽니다. 다시 입력해주세요.\n";
        }
        else {
            break;
        }
    }

    // 실제 시작값은 고정(명시적으로 세팅)
    hp = TARGET_HP;
    mp = TARGET_MP;
    atk = TARGET_ATK;
    def = TARGET_DEF;

    cout << "* 시작 스탯은 고정값으로 설정됩니다. (HP 60, MP 60, ATK 30, DEF 30)\n";
    cout << "* 포션이 지급되었습니다. (HP, MP 포션 각 5개)\n";
    cout << "=============================================\n";

    // ===== 스탯 관리 시스템 루프 =====
    while (true) {
        cout << "<스탯 관리 시스템>\n";
        cout << "1. HP 회복\n";
        cout << "2. MP 회복\n";
        cout << "3. HP 강화\n";
        cout << "4. MP 강화\n";
        cout << "5. 공격 스킬 사용 (MP 50 소모)\n";
        cout << "6. 필살기 사용 (현재 MP의 50% 소모)\n";
        cout << "7. 종료\n";
        cout << "번호를 선택해주세요: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "숫자를 입력해주세요.\n";
            cout << "=============================================\n";
            continue;
        }

        switch (choice) {
        case 1: { // HP 회복
            if (hpPotion > 0) {
                hp += 20;
                hpPotion--;
                cout << "* HP가 20 회복되었습니다. 포션이 1개 차감됩니다.\n";
                cout << "현재 HP: " << hp << "\n남은 HP 포션: " << hpPotion << "\n";
            }
            else {
                cout << "HP 포션이 부족합니다!\n";
            }
            break;
        }
        case 2: { // MP 회복
            if (mpPotion > 0) {
                mp += 20;
                mpPotion--;
                cout << "* MP가 20 회복되었습니다. 포션이 1개 차감됩니다.\n";
                cout << "현재 MP: " << mp << "\n남은 MP 포션: " << mpPotion << "\n";
            }
            else {
                cout << "MP 포션이 부족합니다!\n";
            }
            break;
        }
        case 3: { // HP 강화
            hp *= 2;
            cout << "* HP가 2배로 증가되었습니다.\n현재 HP: " << hp << "\n";
            break;
        }
        case 4: { // MP 강화
            mp *= 2;
            cout << "* MP가 2배로 증가되었습니다.\n현재 MP: " << mp << "\n";
            break;
        }
        case 5: { // 공격 스킬 (MP 50 소모)
            if (mp >= 50) {
                mp -= 50;
                cout << "* 스킬을 사용하여 MP가 50 소모되었습니다.\n현재 MP: " << mp << "\n";
            }
            else {
                cout << "MP가 부족합니다!\n";
            }
            break;
        }
        case 6: { // 필살기 (현재 MP 50% 소모)
            if (mp > 0) {
                int cost = mp / 2; // 현재 MP 절반(정수 나눗셈)
                mp -= cost;
                cout << "* 필살기를 사용하여 MP가 " << cost << " 소모되었습니다.\n";
                cout << "현재 MP: " << mp << "\n";
            }
            else {
                cout << "MP가 부족합니다!\n";
            }
            break;
        }
        case 7: { // 종료
            cout << "시스템을 종료합니다.\n";
            return 0;
        }
        default:
            cout << "잘못된 번호입니다.\n";
            break;
        }
        cout << "=============================================\n";
    }
}
