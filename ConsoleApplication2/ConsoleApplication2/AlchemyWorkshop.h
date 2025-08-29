#pragma once
#include "PotionRecipe.h"
#include <vector>
#include <string>
#include <iostream>

class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes_;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes_.emplace_back(name, ingredients);
    }

    void displayAllRecipes() const {
        if (recipes_.empty()) {
            std::cout << "(레시피 없음)\n";
            return;
        }
        for (const auto& r : recipes_) r.PrintInfo();
    }

    // 이름(정확 일치) 검색
    PotionRecipe* searchRecipeByName(const std::string& name) {
        for (auto& r : recipes_) if (r.GetName() == name) return &r;
        return nullptr;
    }

    // 재료 포함 검색
    std::vector<PotionRecipe*> searchRecipeByIngredient(const std::string& ingredient) {
        std::vector<PotionRecipe*> result;
        for (auto& r : recipes_) {
            for (const auto& ing : r.GetIngredients()) {
                if (ing == ingredient) { result.push_back(&r); break; }
            }
        }
        return result;
    }
};
