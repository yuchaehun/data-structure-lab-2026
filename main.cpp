#include <QApplication>
#include "FlightApp.h" // UI 클래스 헤더 포함

int main(int argc, char *argv[]) {
    // 1. Qt 어플리케이션 객체 생성 (프로세스 초기화)
    QApplication app(argc, argv);

    // 2. 우리가 만든 메인 윈도우 객체(클래스) 생성
    FlightApp window;

    // 3. 창을 화면에 띄움
    window.show();

    // 4. 이벤트 루프 실행 (사용자 클릭 대기 상태 돌입)
    return app.exec();
}