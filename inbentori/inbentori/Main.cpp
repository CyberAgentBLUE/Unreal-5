#include <iostream>
#include <string>
#include "Inventory.h"

int main() {
    // int Ÿ�� �κ��丮
    Inventory<int> invInt(3);
    std::cout << invInt.AddItem(10) << "\n"; // 1
    std::cout << invInt.AddItem(20) << "\n"; // 1
    std::cout << invInt.AddItem(30) << "\n"; // 1
    std::cout << invInt.AddItem(40) << "\n"; // 0 (capacity �ʰ�)
    std::cout << invInt.Size() << "/" << invInt.Capacity() << "\n"; // 3/3
    std::cout << invInt.RemoveLastItem() << "\n"; // 1
    std::cout << invInt.Size() << "\n";           // 2

    // string Ÿ�� �κ��丮 (���ø��� ����: Ÿ�� ����)
    Inventory<std::string> invStr(2);
    invStr.AddItem("Potion");
    invStr.AddItem("Elixir");
    std::cout << invStr[0] << ", " << invStr[1] << "\n";

    return 0;
}
