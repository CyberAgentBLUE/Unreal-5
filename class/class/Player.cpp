class Player {
public:
    virtual void attack() = 0; // 순수 가상 함수
    virtual ~Player() {}       // 가상 소멸자
};
