#pragma once
#include <cstddef>    // size_t
#include <stdexcept>  // std::out_of_range

// ���ø� �κ��丮 Ŭ����
template <typename T>
class Inventory {
public:
    // [�ʼ�] �⺻ ����(Default Argument)�� ����� ������
    explicit Inventory(std::size_t capacity = 10)
        : capacity_(capacity),
        size_(0),
        items_(capacity_ ? new T[capacity_] : nullptr) {
    }

    // [�ʼ�] ���� �޸� ����
    ~Inventory() { delete[] items_; }

    // [�ʼ�] ������ �߰� (capacity�� ������ ����)
    bool AddItem(const T& item) {
        if (size_ >= capacity_) return false;   // �� á���� ����
        items_[size_++] = item;                 // ���� ������ ���� + �ڿ� �߰�
        return true;
    }

    // [�ʼ�] ������ ������ ���� (��������� ����)
    bool RemoveLastItem() {
        if (size_ == 0) return false;   // ��������� ����
        --size_;                        // size�� ���̸� T�� �Ҹ��ڰ� ȣ���
        return true;
    }

    // ���� ũ�� ��ȯ
    std::size_t Size() const { return size_; }

    // ���뷮 ��ȯ
    std::size_t Capacity() const { return capacity_; }

    // �б� ���� ���� ������
    const T& operator[](std::size_t idx) const {
        if (idx >= size_) throw std::out_of_range("index");
        return items_[idx];
    }

    // ����/�̵� ���� (���� ���� �̱���)
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&&) = delete;
    Inventory& operator=(Inventory&&) = delete;

private:
    std::size_t capacity_;  // �ִ� ũ��
    std::size_t size_;      // ���� ũ��
    T* items_;              // ���� �迭
};
