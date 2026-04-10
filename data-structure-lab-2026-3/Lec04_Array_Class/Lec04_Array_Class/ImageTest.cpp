#include <iostream>
#include "image_utils.h"

// 헤더에 선언된 함수 구현
int getMaxBrightness(const Image2D& img) {
    int max_val = 0;
    
    // std::array는 범위 기반 for문을 지원하므로 코드가 매우 간결해집니다.
    for (const auto& row : img) {
        for (int pixel : row) {
            if (pixel > max_val) {
                max_val = pixel;
            }
        }
    }
    
    return max_val;
}

int main() {
    // 기존 C배열 데이터를 std::array 구조에 맞게 초기화 (중괄호가 한 겹 더 들어감에 주의)
    Image2D image = {{
      {  10,  30,  55,  80, 120, 160, 200, 230},
      {  20,  45,  70, 100, 140, 180, 220, 210},
      {  35,  60,  90, 130, 170, 210, 240, 190},
      {  50,  80, 115, 150, 190, 230, 255, 170},
      {  40,  65, 100, 140, 175, 215, 235, 150},
      {  25,  50,  80, 115, 155, 195, 210, 130},
      {  15,  35,  60,  90, 130, 165, 185, 110},
      {   5,  20,  40,  70, 105, 140, 160,  90}
    }};

    int max_brightness = getMaxBrightness(image);

 
    std::cout << "최대 화소 밝기: " << max_brightness << std::endl;

    return 0;
}