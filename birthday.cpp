#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取某个月的天数
int daysInMonth(int month, int year) {
    switch(month) {
        case 2: return isLeapYear(year) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

// 计算日期对应的儒略日
int toJulianDay(int year, int month, int day) {
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

// 计算两个日期之间的天数差
int daysBetween(int y1, int m1, int d1, int y2, int m2, int d2) {
    int jd1 = toJulianDay(y1, m1, d1);
    int jd2 = toJulianDay(y2, m2, d2);
    return abs(jd2 - jd1);
}

// 查找下一个闰年
int nextLeapYear(int currentYear) {
    int year = currentYear + 1;
    while (!isLeapYear(year)) {
        year++;
    }
    return year;
}

int main() {
    string input;
    int birthYear, birthMonth, birthDay;
    char delimiter;
    
    cout << "🎂 生日计算器 🎂" << endl;
    cout << "请输入您的出生日期 (格式: YYYY-MM-DD 或 MM-DD): ";
    getline(cin, input);
    
    // 解析输入
    stringstream ss(input);
    if (input.find('-') != string::npos && input.length() > 5) {
        // 包含年份的格式
        ss >> birthYear >> delimiter >> birthMonth >> delimiter >> birthDay;
    } else {
        // 不包含年份的格式
        birthYear = 0; 
        ss >> birthMonth >> delimiter >> birthDay;
    }
    
    // 验证日期有效性
    if (birthMonth < 1 || birthMonth > 12 || birthDay < 1 || birthDay > daysInMonth(birthMonth, 2024)) {
        cout << "错误: 无效的日期!" << endl;
        return 1;
    }
    
    // 获取当前日期
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    int currentYear = currentTime->tm_year + 1900;
    int currentMonth = currentTime->tm_mon + 1;
    int currentDay = currentTime->tm_mday;
    
    // 特殊处理2月29日生日
    bool isFeb29 = (birthMonth == 2 && birthDay == 29);
    
    if (birthYear != 0) {
        // 计算已出生天数
        int daysAlive = daysBetween(birthYear, birthMonth, birthDay, currentYear, currentMonth, currentDay);
        cout << "您已经出生了 " << daysAlive << " 天" << endl;
    }
    
    // 计算下一个生日
    int nextBirthdayYear = currentYear;
    
    if (isFeb29) {
        // 对于2月29日生日，找到下一个闰年
        if (currentMonth < 2 || (currentMonth == 2 && currentDay < 29)) {
            if (isLeapYear(currentYear)) {
                nextBirthdayYear = currentYear;
            } else {
                nextBirthdayYear = nextLeapYear(currentYear);
            }
        } else {
            nextBirthdayYear = nextLeapYear(currentYear);
        }
    } else {
        // 对于普通生日
        if (currentMonth > birthMonth || (currentMonth == birthMonth && currentDay > birthDay)) {
            nextBirthdayYear = currentYear + 1;
        } else {
            nextBirthdayYear = currentYear;
        }
    }
    
    // 计算距离下一个生日的天数
    int daysUntilBirthday;
    
    if (isFeb29 && !isLeapYear(nextBirthdayYear)) {
        // 这种情况理论上不应该发生，因为我们已经处理了闰年
        daysUntilBirthday = -1;
    } else {
        daysUntilBirthday = daysBetween(currentYear, currentMonth, currentDay, 
                                      nextBirthdayYear, birthMonth, birthDay);
    }
    
    if (daysUntilBirthday == 0) {
        cout << "🎉 今天是您的生日! 生日快乐! 🎉" << endl;
    } else {
        cout << "距离您下一个生日还有 " << daysUntilBirthday << " 天" << endl;
        if (isFeb29) {
            cout << "注: 您的生日是2月29日，每4年庆祝一次" << endl;
        }
    }
    
    return 0;
}