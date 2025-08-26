#include <iostream>
#include <ctime>
using namespace std;
void calculateAges(int birthYear, int birthMonth, int birthDay, int& realAge, int& lunarAge) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;  
    int currentMonth = 1 + ltm->tm_mon;     
    int currentDay = ltm->tm_mday;
    realAge = currentYear - birthYear;
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        realAge--;
    }
    lunarAge = realAge + 1;
}
int main() {
    int birthYear, birthMonth, birthDay;
    cout << "������������ݣ�"<<endl;
    cin >> birthYear;
    cout << "�����������·ݣ�"<<endl;
    cin >> birthMonth;
    cout << "�������������ڣ�"<<endl;
    cin >> birthDay;
    if (birthMonth < 1 || birthMonth > 12) {
        cout << "�����·ݱ�����1-12֮�䣡" << endl;
        return 1;
    }
    if (birthDay < 1 || birthDay > 31) {
        cout << "�������ڱ�����1-31֮�䣡"<< endl;
        return 1;
    }
    int realAge, lunarAge;
    calculateAges(birthYear, birthMonth, birthDay, realAge, lunarAge);
    cout << "\n��ѯ���" << endl;
    cout << "���������ǣ�" << realAge << "��" << endl;
    cout << "���������ǣ�" << lunarAge << "��" << endl;
    return 0;
}	

