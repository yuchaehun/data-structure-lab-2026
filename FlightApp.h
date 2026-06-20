#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <QPixmap>
#include <vector>
#include <QString>

struct Flight {
    QString flightNum;   
    QString destination; 
    QString time;        
    QString price;       
};

struct Airport {
    QString name; 
    int x, y;     // 900x600 .jpg 지도에 맞춘 정밀 좌표
    std::vector<Flight> flights; 
};

class FlightApp : public QMainWindow {
    Q_OBJECT

private:
    std::vector<Airport> airports;
    QGroupBox *flightPanel;      
    QVBoxLayout *flightLayout;   
    QLabel *statusLabel;         

public:
    FlightApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setFixedSize(1200, 600);
        setWindowTitle("항공권 예매 프로그램 (데이터 구조 프로젝트)");

        initFixedData(); 
        setupUI();       
    }

private:
    void initFixedData() {
        // [수정] world_map.jpg 이미지의 실제 대륙 위치에 맞게 픽셀 미세조정 완료
        
        // 인덱스 0: 인천 (한국)
        Airport icn = {"인천(ICN)", 730, 250, {
            {"KE703", "도쿄(NRT)", "10:00 AM", "350,000원"},
            {"KE681", "호치민(SGN)", "13:30 PM", "420,000원"},
            {"KE017", "로스앤젤레스(LAX)", "14:30 PM", "1,200,000원"},
            {"OZ541", "프랑크푸르트(FRA)", "12:00 PM", "1,450,000원"}
        }};
        
        // 인덱스 1: 도쿄 (일본)
        Airport nrt = {"도쿄(NRT)", 775, 260, {
            {"JL092", "인천(ICN)", "09:00 AM", "330,000원"},
            {"NH112", "시드니(SYD)", "20:00 PM", "950,000원"},
            {"JL062", "로스앤젤레스(LAX)", "17:00 PM", "1,100,000원"}
        }};

        // 인덱스 2: 뉴욕 (미국 동부)
        Airport jfk = {"뉴욕(JFK)", 240, 240, {
            {"DL027", "프랑크푸르트(FRA)", "18:00 PM", "800,000원"},
            {"AA118", "로스앤젤레스(LAX)", "08:00 AM", "450,000원"}
        }};

        // 인덱스 3: 로스앤젤레스 (미국 서부)
        Airport lax = {"LA(LAX)", 130, 260, {
            {"UA803", "도쿄(NRT)", "11:00 AM", "1,150,000원"},
            {"DL442", "뉴욕(JFK)", "22:00 PM", "420,000원"}
        }};

        // 인덱스 4: 프랑크푸르트 (유럽 중앙)
        Airport fra = {"독일(FRA)", 450, 210, {
            {"LH712", "인천(ICN)", "17:30 PM", "1,500,000원"},
            {"LH400", "뉴욕(JFK)", "10:30 AM", "850,000원"}
        }};

        // 인덱스 5: 호치민 (동남아시아)
        Airport sgn = {"호치민(SGN)", 710, 310, {
            {"VN408", "인천(ICN)", "23:45 PM", "380,000원"},
            {"VN773", "시드니(SYD)", "21:00 PM", "600,000원"}
        }};

        // 인덱스 6: 시드니 (호주 동남부)
        Airport syd = {"시드니(SYD)", 800, 460, {
            {"QF021", "도쿄(NRT)", "22:00 PM", "980,000원"},
            {"JQ027", "호치민(SGN)", "15:00 PM", "550,000원"}
        }};

        airports.push_back(icn); // 0
        airports.push_back(nrt); // 1
        airports.push_back(jfk); // 2
        airports.push_back(lax); // 3
        airports.push_back(fra); // 4
        airports.push_back(sgn); // 5
        airports.push_back(syd); // 6
    }

    void setupUI() {
        statusLabel = new QLabel("원하시는 출발 공항을 클릭해주세요.", this);
        statusLabel->setGeometry(20, 530, 860, 50);
        statusLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333; "
                                   "background-color: rgba(255, 255, 255, 220); border-radius: 10px; padding: 10px;");

        flightPanel = new QGroupBox("출발 항공편 목록", this);
        flightPanel->setGeometry(910, 20, 270, 560);
        flightPanel->setStyleSheet("font-size: 14px; font-weight: bold; background-color: #f9f9f9;");
        
        flightLayout = new QVBoxLayout(flightPanel);
        flightLayout->setAlignment(Qt::AlignTop);

        for (size_t i = 0; i < airports.size(); ++i) {
            QPushButton *airportBtn = new QPushButton(airports[i].name, this);
            airportBtn->setGeometry(airports[i].x, airports[i].y, 50, 26);
            
            airportBtn->setStyleSheet("background-color: #2196F3; color: white; "
                                      "border-radius: 5px; font-weight: bold; "
                                      "border: 1px solid white; font-size: 11px;");

            connect(airportBtn, &QPushButton::clicked, this, [this, i]() {
                showFlightsForAirport(i);
            });
        }
    }

    void showFlightsForAirport(int index) {
        QLayoutItem *child;
        while ((child = flightLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        const Airport& selectedAirport = airports[index];
        statusLabel->setText(QString("✈️ %1 출발 항공편이 조회되었습니다.").arg(selectedAirport.name));
        statusLabel->setStyleSheet("font-size: 18px; color: black; font-weight: bold; "
                                   "background-color: rgba(255, 255, 255, 220); border-radius: 10px; padding: 10px;");

        for (const auto& flight : selectedAirport.flights) {
            QString btnText = QString("[%1] %2행\n시간: %3 | 가격: %4")
                                .arg(flight.flightNum, flight.destination, flight.time, flight.price);
            
            QPushButton *flightBtn = new QPushButton(btnText);
            flightBtn->setMinimumHeight(60);
            flightBtn->setStyleSheet("background-color: white; border: 2px solid #ccc; "
                                     "border-radius: 5px; text-align: left; padding: 5px; margin-top: 5px;");

            connect(flightBtn, &QPushButton::clicked, this, [this, flight]() {
                QString successMsg = QString("🎉 [%1] %2행 항공권 예매가 완료되었습니다!").arg(flight.flightNum, flight.destination);
                statusLabel->setText(successMsg);
                statusLabel->setStyleSheet("font-size: 20px; color: #E91E63; font-weight: bold; "
                                           "background-color: rgba(255, 255, 255, 220); border-radius: 10px; padding: 10px;");
            });

            flightLayout->addWidget(flightBtn);
        }
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // [수정] 확장자가 .jpg인 이미지를 불러오도록 변경했습니다.
        painter.drawPixmap(0, 0, 900, 600, QPixmap("./world_map.jpg"));

        painter.setPen(QPen(QColor(100, 100, 100, 180), 2, Qt::DashLine));

        // 0:인천, 1:도쿄, 2:뉴욕, 3:LA, 4:프랑크푸르트, 5:호치민, 6:시드니
        std::vector<std::pair<int, int>> mapRoutes = {
            {0, 1}, // 인천 - 도쿄
            {0, 3}, // 인천 - LA
            {0, 4}, // 인천 - 프랑크푸르트
            {0, 5}, // 인천 - 호치민
            {1, 3}, // 도쿄 - LA
            {1, 6}, // 도쿄 - 시드니
            {2, 3}, // 뉴욕 - LA
            {2, 4}, // 뉴욕 - 프랑크푸르트
            {5, 6}  // 호치민 - 시드니
        };

        for (const auto& route : mapRoutes) {
            int x1 = airports[route.first].x + 25;
            int y1 = airports[route.first].y + 13;
            int x2 = airports[route.second].x + 25;
            int y2 = airports[route.second].y + 13;
            
            painter.drawLine(x1, y1, x2, y2);
        }
    }
};