#pragma once
#include <cstdio>
#include <cstring>

class Car {
protected:
    int speed = 0;               // in-class 초기화로 C26495 해결
    char name[40] = {};          // 이미 제로 초기화 되어 있음

public:
    int gear = 0;                // in-class 초기화로 C26495 해결

    Car() = default;
    virtual ~Car() = 0;       // 순수 가상 소멸자 선언

    Car(int s, const char* n, int g)
        : speed(s), gear(g) {
        strncpy_s(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    void changeGear(int g = 4) {
        gear = g;
    }

    virtual void speedUp() {
        speed += 5;
    }

    void display() {
        printf("[%s] : 기어=%d단 속도=%dkmph\n", name, gear, speed);
    }

    void whereAmI() {
        printf("객체 주소 = %p\n", this);
    }
};

// 순수 가상 소멸자 정의(필수)
inline Car::~Car() = default;
