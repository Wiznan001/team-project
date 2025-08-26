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

// �����ṹ��
struct ZodiacSign {
    string name;
    string dateRange;
    vector<string> fortunes;
};

// ȫ����������
vector<ZodiacSign> zodiacSigns = {
    {"������", "03-21 �� 04-19", {"����������һ��", "�ʺϳ���������", "ע�����Ƣ��"}},
    {"��ţ��", "04-20 �� 05-20", {"���˲���", "�ʺ�������ʳ", "��������"}},
    {"˫����", "05-21 �� 06-21", {"��ͨ˳��", "ѧϰ����ǿ", "ע��רע��"}},
    {"��з��", "06-22 �� 07-22", {"��ͥ����", "��зḻ", "ע����������"}},
    {"ʨ����", "07-23 �� 08-22", {"��������", "�쵼��ǿ", "ע�ⲻҪ̫����"}},
    {"��Ů��", "08-23 �� 09-22", {"ϸ���ܵ�", "����Ч�ʸ�", "��Ҫ��������"}},
    {"�����", "09-23 �� 10-23", {"�˼ʹ�ϵ��", "׷��ƽ��", "����һЩ"}},
    {"��Ы��", "10-24 �� 10-23", {"ֱ������", "���˼��", "��Ҫ���ڶ���"}},
    {"������", "11-23 �� 12-21", {"���ɱ���", "�ֹۻ���", "ע���ŵ"}},
    {"Ħ����", "12-22 �� 01-19", {"̤ʵ����", "��ҵ�˼�", "�ʵ�����"}},
    {"ˮƿ��", "01-20 �� 02-18", {"��������", "����˼��", "ע��ʵ��ִ��"}},
    {"˫����", "02-19 �� 03-20", {"��������", "�������ḻ", "��ʵһЩ"}}
};

// ����Ƿ�Ϊ����
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// ��ȡ�·ݵ�����
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

// ��������Ƿ���Ч
bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > getDaysInMonth(month, year)) return false;
    return true;
}

// ������������֮���������
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

// ��ȡ��ǰ����
void getCurrentDate(int& year, int& month, int& day) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

// �������ջ�ȡ����
string getZodiacSign(int month, int day) {
    if ((month == 3 && day >= 21) || (month == 4 && day <= 19)) return "������";
    if ((month == 4 && day >= 20) || (month == 5 && day <= 20)) return "��ţ��";
    if ((month == 5 && day >= 21) || (month == 6 && day <= 21)) return "˫����";
    if ((month == 6 && day >= 22) || (month == 7 && day <= 22)) return "��з��";
    if ((month == 7 && day >= 23) || (month == 8 && day <= 22)) return "ʨ����";
    if ((month == 8 && day >= 23) || (month == 9 && day <= 22)) return "��Ů��";
    if ((month == 9 && day >= 23) || (month == 10 && day <= 23)) return "�����";
    if ((month == 10 && day >= 24) || (month == 11 && day <= 22)) return "��Ы��";
    if ((month == 11 && day >= 23) || (month == 12 && day <= 21)) return "������";
    if ((month == 12 && day >= 22) || (month == 1 && day <= 19)) return "Ħ����";
    if ((month == 1 && day >= 20) || (month == 2 && day <= 18)) return "ˮƿ��";
    return "˫����";
}

// ��ȡ�������
string getRandomFortune(const string& zodiacSign) {
    for (const auto& sign : zodiacSigns) {
        if (sign.name == zodiacSign && !sign.fortunes.empty()) {
            int index = rand() % sign.fortunes.size();
            return sign.fortunes[index];
        }
    }
    return "�����Ǻܰ���һ�죡";
}

// ��ʾ��ӭ����
void displayWelcome() {
    cout << "==============================================" << endl;
    cout << "           �����������Ʋ�ѯϵͳ" << endl;
    cout << "==============================================" << endl;
    cout << endl;
}

// ��ʾ���˵�
void displayMainMenu() {
    cout << "\n��ѡ���ܣ�" << endl;
    cout << "1. ��ѯ������һ�����ջ��ж�����" << endl;
    cout << "2. ��ѯ����" << endl;
    cout << "3. ��ѯ�������Ʋ�����" << endl;
    cout << "4. ��ʾ����������Ϣ" << endl;
    cout << "5. �˳�����" << endl;
    cout << "������ѡ�� (1-5): ";
}

// ��ʾ����������Ϣ
void displayAllZodiacInfo() {
    cout << "\n����������Ϣ��" << endl;
    cout << "==============================================" << endl;
    for (const auto& sign : zodiacSigns) {
        cout << sign.name << " (" << sign.dateRange << ")" << endl;
    }
    cout << "==============================================" << endl;
}

// �������Ƶ��ļ�
void exportFortuneToFile(const string& zodiacSign, const string& fortune,
    int year, int month, int day, int actualAge, int nominalAge) {
    ofstream outFile("�������Ʊ���.txt");
    if (outFile.is_open()) {
        outFile << "============== �������Ʊ��� ==============" << endl;
        outFile << "����ʱ��: " << year << "-" << month << "-" << day << endl;
        outFile << "����: " << zodiacSign << endl;
        outFile << "����: " << actualAge << "��" << endl;
        outFile << "����: " << nominalAge << "��" << endl;
        outFile << "------------------------------------------" << endl;
        outFile << "��������: " << fortune << endl;
        outFile << "==========================================" << endl;
        outFile.close();
        cout << "���Ʊ����ѵ����� '�������Ʊ���.txt'" << endl;
    }
    else {
        cout << "�޷������ļ���" << endl;
    }
}

int main() {
    srand(time(0)); // ��ʼ�����������

    int birthYear = 0, birthMonth = 0, birthDay = 0;
    int currentYear, currentMonth, currentDay;

    getCurrentDate(currentYear, currentMonth, currentDay);

    displayWelcome();

    // ��ȡ�û�����
    while (true) {
        cout << "���������ĳ������� (��ʽ: YYYY MM DD): ";
        cin >> birthYear >> birthMonth >> birthDay;

        if (isValidDate(birthYear, birthMonth, birthDay)) {
            break;
        }
        else {
            cout << "������Ч�����������룡" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // �������䣨��������꣩
    int actualAge = currentYear - birthYear;
    int nominalAge = actualAge + 1; // ����

    // ����������ջ�û���������1
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
            // ���������һ�����յ�����
            int nextBirthdayYear = currentYear;
            if (currentMonth > birthMonth || (currentMonth == birthMonth && currentDay >= birthDay)) {
                nextBirthdayYear++;
            }

            int daysToBirthday = daysBetweenDates(currentYear, currentMonth, currentDay,
                nextBirthdayYear, birthMonth, birthDay);

            cout << "\n==============================================" << endl;
            cout << "������Ϣ��ѯ�����" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "��������: " << birthYear << "-" << birthMonth << "-" << birthDay << endl;
            cout << "������һ�����ջ���: " << daysToBirthday << " ��" << endl;
            cout << "���Ѿ�������: " << daysBetweenDates(birthYear, birthMonth, birthDay,
                currentYear, currentMonth, currentDay)
                << " ��" << endl;
            cout << "��������: " << actualAge << " ��" << endl;
            cout << "��������: " << nominalAge << " ��" << endl;
            cout << "==============================================" << endl;
            break;
        }

        case 2: {
            cout << "\n==============================================" << endl;
            cout << "������ѯ�����" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "����������: " << zodiacSign << endl;

            // ��ʾ����������ϸ��Ϣ
            for (const auto& sign : zodiacSigns) {
                if (sign.name == zodiacSign) {
                    cout << "���ڷ�Χ: " << sign.dateRange << endl;
                    break;
                }
            }
            cout << "==============================================" << endl;
            break;
        }

        case 3: {
            string fortune = getRandomFortune(zodiacSign);

            cout << "\n==============================================" << endl;
            cout << "�������Ʋ�ѯ�����" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "����: " << zodiacSign << endl;
            cout << "��������: " << fortune << endl;
            cout << "==============================================" << endl;

            // �������ļ�
            exportFortuneToFile(zodiacSign, fortune, currentYear, currentMonth, currentDay,
                actualAge, nominalAge);
            break;
        }

        case 4: {
            displayAllZodiacInfo();
            break;
        }

        case 5: {
            cout << "��лʹ�������������Ʋ�ѯϵͳ���ټ���" << endl;
            return 0;
        }

        default: {
            cout << "��Чѡ�����������룡" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        }

        cout << "\n���س�������...";
        cin.ignore();
        cin.get();
    }

    return 0;
}