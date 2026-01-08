#define _CRT_SECURE_NO_WARNINGS
#include "photo.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

// Names array definition
char names[20][100] = {
    "차은우",
    "이재욱",
    "손종원",
    "서강준",
    "조규성",
    "로운",
    "사쿠야",
    "원빈",
    "장원영",
    "윈터",
    "민주",
    "고윤정",
    "김연아",
    "한소희",
    "김소혜",
    "김지원"
};

void printphoto(int photo_no)
{
    char path[256];
    sprintf(path, "imgs/%d.txt", photo_no);
    std::ifstream fp(path);
    if (!fp.is_open())
    {
        std::cout << "파일 열기 실패" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(fp, line))
    {
        std::cout << line << std::endl;
    }
    fp.close();
}