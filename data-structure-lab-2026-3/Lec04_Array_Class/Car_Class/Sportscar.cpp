#include "Car.h" // 자동차 클래스 헤더파일 포함

// 스포츠카 클래스 (자식 클래스)
class SportsCar : public Car
{
public:
    bool bTurbo; // 터보 장치 ON/OFF

    // 자식 클래스의 생성자 (부모 클래스의 생성자 호출)
    SportsCar(int s, const char* n, int g, bool turbo) : Car(s, n, g) {
        bTurbo = turbo;
    }

    void setTurbo(bool bTur) { bTurbo = bTur; }

    // 부모 클래스의 메서드 오버라이딩(재정의)
    void speedUp() override {
        if (bTurbo) speed += 20; // protected라 접근 가능!
        else Car::speedUp();
    }
};

// 프로그램 실행을 위한 main 함수
int main() {
    // SportsCar 객체 생성
    SportsCar myCar(100, "Ferrari", 3, true);

    myCar.display(); // 초기 상태 출력

    // 가속 테스트 (터보 ON 상태)
    myCar.speedUp();
    printf("터보 가속 후:\n");
    myCar.display();

    // 터보 끄고 가속 테스트
    myCar.setTurbo(false);
    myCar.speedUp();
    printf("터보 끄고 일반 가속 후:\n");
    myCar.display();

    myCar.whereAmI();

    return 0;
}