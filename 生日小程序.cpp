#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// 星座结构体
struct ZodiacSign {
    string name;
    string dateRange;
    vector<string> fortunes;
};

// 全局星座数据
vector<ZodiacSign> zodiacSigns = {
    {"白羊座", "03-21 到 04-19", {"充满活力的一天", "适合尝试新事物", "注意控制脾气"}},
    {"金牛座", "04-20 到 05-20", {"财运不错", "适合享受美食", "保持耐心"}},
    {"双子座", "05-21 到 06-21", {"沟通顺畅", "学习能力强", "注意专注力"}},
    {"巨蟹座", "06-22 到 07-22", {"家庭和睦", "情感丰富", "注意情绪波动"}},
    {"狮子座", "07-23 到 08-22", {"自信满满", "领导力强", "注意不要太自我"}},
    {"处女座", "08-23 到 09-22", {"细心周到", "工作效率高", "不要过于挑剔"}},
    {"天秤座", "09-23 到 10-23", {"人际关系好", "追求平衡", "果断一些"}},
    {"天蝎座", "10-24 到 10-23", {"直觉敏锐", "深度思考", "不要过于多疑"}},
    {"射手座", "11-23 到 12-21", {"自由奔放", "乐观积极", "注意承诺"}},
    {"摩羯座", "12-22 到 01-19", {"踏实稳重", "事业运佳", "适当放松"}},
    {"水瓶座", "01-20 到 02-18", {"创意无限", "独立思考", "注意实际执行"}},
    {"双鱼座", "02-19 到 03-20", {"浪漫多情", "想象力丰富", "现实一些"}}
};

// 检查是否为闰年
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取月份的天数
int getDaysInMonth(int month, int year) {
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    default:
        return 0;
    }
}

// 检查日期是否有效
bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > getDaysInMonth(month, year)) return false;
    return true;
}

// 计算两个日期之间的天数差
int daysBetweenDates(int y1, int m1, int d1, int y2, int m2, int d2) {
    auto dateToDays = [](int year, int month, int day) {
        int totalDays = day;
        for (int m = 1; m < month; m++) {
            totalDays += getDaysInMonth(m, year);
        }
        for (int y = 0; y < year; y++) {
            totalDays += isLeapYear(y) ? 366 : 365;
        }
        return totalDays;
        };

    return abs(dateToDays(y2, m2, d2) - dateToDays(y1, m1, d1));
}

// 获取当前日期
void getCurrentDate(int& year, int& month, int& day) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

// 根据生日获取星座
string getZodiacSign(int month, int day) {
    if ((month == 3 && day >= 21) || (month == 4 && day <= 19)) return "白羊座";
    if ((month == 4 && day >= 20) || (month == 5 && day <= 20)) return "金牛座";
    if ((month == 5 && day >= 21) || (month == 6 && day <= 21)) return "双子座";
    if ((month == 6 && day >= 22) || (month == 7 && day <= 22)) return "巨蟹座";
    if ((month == 7 && day >= 23) || (month == 8 && day <= 22)) return "狮子座";
    if ((month == 8 && day >= 23) || (month == 9 && day <= 22)) return "处女座";
    if ((month == 9 && day >= 23) || (month == 10 && day <= 23)) return "天秤座";
    if ((month == 10 && day >= 24) || (month == 11 && day <= 22)) return "天蝎座";
    if ((month == 11 && day >= 23) || (month == 12 && day <= 21)) return "射手座";
    if ((month == 12 && day >= 22) || (month == 1 && day <= 19)) return "摩羯座";
    if ((month == 1 && day >= 20) || (month == 2 && day <= 18)) return "水瓶座";
    return "双鱼座";
}

// 获取随机运势
string getRandomFortune(const string& zodiacSign) {
    for (const auto& sign : zodiacSigns) {
        if (sign.name == zodiacSign && !sign.fortunes.empty()) {
            int index = rand() % sign.fortunes.size();
            return sign.fortunes[index];
        }
    }
    return "今天是很棒的一天！";
}

// 显示欢迎界面
void displayWelcome() {
    cout << "==============================================" << endl;
    cout << "           生日星座运势查询系统" << endl;
    cout << "==============================================" << endl;
    cout << endl;
}

// 显示主菜单
void displayMainMenu() {
    cout << "\n请选择功能：" << endl;
    cout << "1. 查询距离下一个生日还有多少天" << endl;
    cout << "2. 查询星座" << endl;
    cout << "3. 查询今日运势并导出" << endl;
    cout << "4. 显示所有星座信息" << endl;
    cout << "5. 退出程序" << endl;
    cout << "请输入选择 (1-5): ";
}

// 显示所有星座信息
void displayAllZodiacInfo() {
    cout << "\n所有星座信息：" << endl;
    cout << "==============================================" << endl;
    for (const auto& sign : zodiacSigns) {
        cout << sign.name << " (" << sign.dateRange << ")" << endl;
    }
    cout << "==============================================" << endl;
}

// 导出运势到文件
void exportFortuneToFile(const string& zodiacSign, const string& fortune,
    int year, int month, int day, int actualAge, int nominalAge) {
    ofstream outFile("今日运势报告.txt");
    if (outFile.is_open()) {
        outFile << "============== 今日运势报告 ==============" << endl;
        outFile << "生成时间: " << year << "-" << month << "-" << day << endl;
        outFile << "星座: " << zodiacSign << endl;
        outFile << "周岁: " << actualAge << "岁" << endl;
        outFile << "虚岁: " << nominalAge << "岁" << endl;
        outFile << "------------------------------------------" << endl;
        outFile << "今日运势: " << fortune << endl;
        outFile << "==========================================" << endl;
        outFile.close();
        cout << "运势报告已导出到 '今日运势报告.txt'" << endl;
    }
    else {
        cout << "无法创建文件！" << endl;
    }
}

int main() {
    srand(time(0)); // 初始化随机数种子

    int birthYear = 0, birthMonth = 0, birthDay = 0;
    int currentYear, currentMonth, currentDay;

    getCurrentDate(currentYear, currentMonth, currentDay);

    displayWelcome();

    // 获取用户生日
    while (true) {
        cout << "请输入您的出生日期 (格式: YYYY MM DD): ";
        cin >> birthYear >> birthMonth >> birthDay;

        if (isValidDate(birthYear, birthMonth, birthDay)) {
            break;
        }
        else {
            cout << "日期无效，请重新输入！" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // 计算年龄（周岁和虚岁）
    int actualAge = currentYear - birthYear;
    int nominalAge = actualAge + 1; // 虚岁

    // 如果今年生日还没过，周岁减1
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        actualAge--;
    }

    string zodiacSign = getZodiacSign(birthMonth, birthDay);

    while (true) {
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            // 计算距离下一个生日的天数
            int nextBirthdayYear = currentYear;
            if (currentMonth > birthMonth || (currentMonth == birthMonth && currentDay >= birthDay)) {
                nextBirthdayYear++;
            }

            int daysToBirthday = daysBetweenDates(currentYear, currentMonth, currentDay,
                nextBirthdayYear, birthMonth, birthDay);

            cout << "\n==============================================" << endl;
            cout << "生日信息查询结果：" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "您的生日: " << birthYear << "-" << birthMonth << "-" << birthDay << endl;
            cout << "距离下一个生日还有: " << daysToBirthday << " 天" << endl;
            cout << "您已经出生了: " << daysBetweenDates(birthYear, birthMonth, birthDay,
                currentYear, currentMonth, currentDay)
                << " 天" << endl;
            cout << "您的周岁: " << actualAge << " 岁" << endl;
            cout << "您的虚岁: " << nominalAge << " 岁" << endl;
            cout << "==============================================" << endl;
            break;
        }

        case 2: {
            cout << "\n==============================================" << endl;
            cout << "星座查询结果：" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "您的星座是: " << zodiacSign << endl;

            // 显示该星座的详细信息
            for (const auto& sign : zodiacSigns) {
                if (sign.name == zodiacSign) {
                    cout << "日期范围: " << sign.dateRange << endl;
                    break;
                }
            }
            cout << "==============================================" << endl;
            break;
        }

        case 3: {
            string fortune = getRandomFortune(zodiacSign);

            cout << "\n==============================================" << endl;
            cout << "今日运势查询结果：" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "星座: " << zodiacSign << endl;
            cout << "今日运势: " << fortune << endl;
            cout << "==============================================" << endl;

            // 导出到文件
            exportFortuneToFile(zodiacSign, fortune, currentYear, currentMonth, currentDay,
                actualAge, nominalAge);
            break;
        }

        case 4: {
            displayAllZodiacInfo();
            break;
        }

        case 5: {
            cout << "感谢使用生日星座运势查询系统，再见！" << endl;
            return 0;
        }

        default: {
            cout << "无效选择，请重新输入！" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        }

        cout << "\n按回车键继续...";
        cin.ignore();
        cin.get();
    }

    return 0;
}