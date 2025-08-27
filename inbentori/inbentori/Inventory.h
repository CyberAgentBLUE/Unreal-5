#pragma once
#include <cstddef>    // size_t
#include <stdexcept>  // std::out_of_range

// 템플릿 인벤토리 클래스
template <typename T>
class Inventory {
public:
    // [필수] 기본 인자(Default Argument)를 사용한 생성자
    explicit Inventory(std::size_t capacity = 10)
        : capacity_(capacity),
        size_(0),
        items_(capacity_ ? new T[capacity_] : nullptr) {
    }

    // [필수] 동적 메모리 해제
    ~Inventory() { delete[] items_; }

    // [필수] 아이템 추가 (capacity를 넘으면 실패)
    bool AddItem(const T& item) {
        if (size_ >= capacity_) return false;   // 꽉 찼으면 실패
        items_[size_++] = item;                 // 기존 데이터 보존 + 뒤에 추가
        return true;
    }

    // [필수] 마지막 아이템 제거 (비어있으면 실패)
    bool RemoveLastItem() {
        if (size_ == 0) return false;   // 비어있으면 실패
        --size_;                        // size만 줄이면 T의 소멸자가 호출됨
        return true;
    }

    // 현재 크기 반환
    std::size_t Size() const { return size_; }

    // 수용량 반환
    std::size_t Capacity() const { return capacity_; }

    // 읽기 전용 접근 연산자
    const T& operator[](std::size_t idx) const {
        if (idx >= size_) throw std::out_of_range("index");
        return items_[idx];
    }

    // 복사/이동 금지 (깊은 복사 미구현)
    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory(Inventory&&) = delete;
    Inventory& operator=(Inventory&&) = delete;

private:
    std::size_t capacity_;  // 최대 크기
    std::size_t size_;      // 현재 크기
    T* items_;              // 동적 배열
};
