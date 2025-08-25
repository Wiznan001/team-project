#include <iostream>
#include <ctime>
using namespace std;

// 计算年龄并返回结果
void calculateAges(int y, int m, int d, int& real, int& lunar) {
    time_t now = time(0);
    tm* lt = localtime(&now);  // 正确获取本地时间结构体指针
    int cy = 1900 + lt->tm_year;
    int cm = 1 + lt->tm_mon;
    int cd = lt->tm_mday;

    // 计算周岁
    real = cy - y;
    if (cm < m || (cm == m && cd < d)) real--;
    // 计算虚岁
    lunar = real + 1;
}

// 简单验证日期有效性
bool isValid(int y, int m, int d, int cy) {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;
    // 二月特殊处理
    if (m == 2) {
        // 判断闰年
        bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (d > (leap ? 29 : 28)) return false;
    }
    // 小月处理
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;
    // 年份范围
    return y >= 1900 && y <= cy;
}

int main() {
    int y, m, d;
    cout << "请输入生日(年 月 日)：";
    cin >> y >> m >> d;

    // 正确获取当前年份用于验证
    time_t now = time(0);
    tm* lt = localtime(&now);
    int cy = 1900 + lt->tm_year;
    
    if (!isValid(y, m, d, cy)) {
        cerr << "无效的日期格式！" << endl;
        return 1;
    }

    int real, lunar;
    calculateAges(y, m, d, real, lunar);
    cout << "周岁：" << real << "岁，虚岁：" << lunar << "岁" << endl;

    return 0;
}
