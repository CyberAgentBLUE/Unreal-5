#include <iostream>
#include <string>
#include "Inventory.h"

int main() {
    // int 타입 인벤토리
    Inventory<int> invInt(3);
    std::cout << invInt.AddItem(10) << "\n"; // 1
    std::cout << invInt.AddItem(20) << "\n"; // 1
    std::cout << invInt.AddItem(30) << "\n"; // 1
    std::cout << invInt.AddItem(40) << "\n"; // 0 (capacity 초과)
    std::cout << invInt.Size() << "/" << invInt.Capacity() << "\n"; // 3/3
    std::cout << invInt.RemoveLastItem() << "\n"; // 1
    std::cout << invInt.Size() << "\n";           // 2

    // string 타입 인벤토리 (템플릿의 장점: 타입 재사용)
    Inventory<std::string> invStr(2);
    invStr.AddItem("Potion");
    invStr.AddItem("Elixir");
    std::cout << invStr[0] << ", " << invStr[1] << "\n";

    return 0;
}
