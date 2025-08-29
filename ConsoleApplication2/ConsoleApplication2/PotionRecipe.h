#pragma once
#include <iostream>
#include <string>
#include <vector>

class PotionRecipe {
private:
    std::string name_;
    std::vector<std::string> ingredients_;

public:
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : name_(name), ingredients_(ingredients) {
    }

    const std::string& GetName() const { return name_; }
    const std::vector<std::string>& GetIngredients() const { return ingredients_; }

    void PrintInfo() const {
        std::cout << "레시피 이름: " << name_ << "\n재료: ";
        for (const auto& ing : ingredients_) std::cout << ing << " ";
        std::cout << "\n";
    }
};
