#include "Inventory.h"
#include "AlchemyWorkshop.h"
#include <string>
#include <iostream>

// 테스트용 아이템 타입 (Inventory<T>가 출력에 쓰는 PrintInfo 보유)
struct Item {
    std::string name;
    int price;
    void PrintInfo() const {
        std::cout << "[이름: " << name << ", 가격: " << price << "G]\n";
    }
};

int main() {
    // 1) 인벤토리 테스트
    Inventory<Item> inv(3);
    inv.AddItem({ "힐링 포션", 50 });
    inv.AddItem({ "마나 포션", 70 });
    std::cout << "=== 현재 인벤토리 ===\n";
    inv.PrintAllItems();

    inv.RemoveLastItem();
    std::cout << "=== 삭제 후 인벤토리 ===\n";
    inv.PrintAllItems();

    std::cout << "\n============================\n";

    // 2) 연금술 작업장 테스트
    AlchemyWorkshop workshop;
    workshop.addRecipe("힐링 포션", { "허브", "물" });
    workshop.addRecipe("마나 포션", { "마력풀", "물" });
    workshop.addRecipe("해독제", { "허브", "해독초" });

    std::cout << "=== 전체 레시피 ===\n";
    workshop.displayAllRecipes();

    std::cout << "\n=== 이름 검색: 마나 포션 ===\n";
    if (auto* r = workshop.searchRecipeByName("마나 포션")) r->PrintInfo();

    std::cout << "\n=== 재료 검색: 허브 ===\n";
    for (auto* r : workshop.searchRecipeByIngredient("허브")) r->PrintInfo();

    return 0;
}
