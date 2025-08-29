#pragma once
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::out_of_range
#include <iostream>     // std::cout

template <typename T>
class Inventory {
public:
    explicit Inventory(std::size_t capacity = 10)
        : capacity_(capacity > 0 ? capacity : 1),
        size_(0),
        items_(new T[capacity_]) {
    }

    ~Inventory() {
        delete[] items_;
        items_ = nullptr;
    }

    bool AddItem(const T& item) {
        if (size_ >= capacity_) {
            std::cout << "�κ��丮�� �� á���ϴ�!\n";
            return false;
        }
        items_[size_++] = item;
        return true;
    }

    bool RemoveLastItem() {
        if (size_ == 0) {
            std::cout << "�κ��丮�� ����ֽ��ϴ�.\n";
            return false;
        }
        --size_;
        return true;
    }

    std::size_t Size() const { return size_; }
    std::size_t Capacity() const { return capacity_; }

    const T& operator[](std::size_t idx) const {
        if (idx >= size_) throw std::out_of_range("index");
        return items_[idx];
    }
    T& operator[](std::size_t idx) {
        if (idx >= size_) throw std::out_of_range("index");
        return items_[idx];
    }

    // ��ü ������ ��� (T�� PrintInfo() const�� ������ ��)
    void PrintAllItems() const {
        if (size_ == 0) {
            std::cout << "(�������)\n";
            return;
        }
        for (std::size_t i = 0; i < size_; ++i) {
            items_[i].PrintInfo();
        }
    }

    // ���� ����(�ʿ� �� ���� ���� ����)
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    // �̵� ���(����)
    Inventory(Inventory&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), items_(other.items_) {
        other.capacity_ = 0; other.size_ = 0; other.items_ = nullptr;
    }
    Inventory& operator=(Inventory&& other) noexcept {
        if (this != &other) {
            delete[] items_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            items_ = other.items_;
            other.capacity_ = 0; other.size_ = 0; other.items_ = nullptr;
        }
        return *this;
    }

private:
    std::size_t capacity_;
    std::size_t size_;
    T* items_;
};
