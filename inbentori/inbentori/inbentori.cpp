// Inventory.h
#pragma once                        // 헤더가 중복 포함되지 않도록 보장 (#include 방지)

// 필요한 표준 라이브러리 헤더 포함
#include <cstddef>   // size_t 타입 제공
#include <stdexcept> // 예외 처리용 out_of_range 등 사용

// 템플릿 클래스 정의 (어떤 타입 T든 저장 가능한 인벤토리)
template <typename T>
class Inventory {
public:
    // (2) 생성자: 기본 인자(capacity = 10)를 사용 → 하나의 생성자로 처리
    explicit Inventory(std::size_t capacity = 10)
        : capacity_(capacity),                     // 수용 가능한 최대 아이템 개수
        size_(0),                                // 현재 저장된 아이템 개수
        items_(capacity_ ? new T[capacity_] : nullptr) {
    }  // capacity만큼 동적 배열 할당

// (4) 소멸자: 동적 할당된 배열을 해제하여 메모리 누수 방지
    ~Inventory() { delete[] items_; }

    // (1) 아이템 추가 함수: capacity를 초과하지 않도록 검사
    bool AddItem(const T& item) {
        if (size_ >= capacity_) return false;   // 이미 가득 찼으면 실패
        items_[size_++] = item;                 // 새 아이템을 배열에 추가하고 size 증가
        return true;                            // 성공 시 true 반환
    }

    // (1) 마지막 아이템 제거 함수
    bool RemoveLastItem() {
        if (size_ == 0) return false;           // 비어있으면 실패
        --size_;                                // 마지막 원소 제거 (소멸자는 자동 호출됨)
        return true;                            // 성공 시 true 반환
    }

    // 현재 저장된 아이템 개수 반환
    std::size_t Size() const { return size_; }

    // 최대 수용 가능 아이템 개수 반환
    std::size_t Capacity() const { return capacity_; }

    // 읽기 전용 접근 연산자 (배열 인덱스처럼 사용 가능)
    const T& operator[](std::size_t idx) const {
        if (idx >= size_) throw std::out_of_range("index");  // 범위 벗어나면 예외 발생
        return items_[idx];                                  // 해당 인덱스 아이템 반환
    }

    // 복사/이동 금지 (깊은 복사 구현 안 했으므로 안전하게 금지)
    Inventory(const Inventory&) = delete;            // 복사 생성자 금지
    Inventory& operator=(const Inventory&) = delete; // 복사 대입 연산자 금지
    Inventory(Inventory&&) = delete;                 // 이동 생성자 금지
    Inventory& operator=(Inventory&&) = delete;      // 이동 대입 연산자 금지

private:
    std::size_t capacity_;  // 인벤토리 수용량
    std::size_t size_;      // 현재 아이템 개수
    T* items_;              // 동적 배열 포인터 (아이템 저장 공간)
};
