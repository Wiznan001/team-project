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
    cout << "ÇëÊäÈëÉúÈÕÄê·Ý£º"<<endl;
    cin >> birthYear;
    cout << "ÇëÊäÈëÉúÈÕÔÂ·Ý£º"<<endl;
    cin >> birthMonth;
    cout << "ÇëÊäÈëÉúÈÕÈÕÆÚ£º"<<endl;
    cin >> birthDay;
    if (birthMonth < 1 || birthMonth > 12) {
        cout << "´íÎó£¬ÔÂ·Ý±ØÐëÔÚ1-12Ö®¼ä£¡" << endl;
        return 1;
    }
    if (birthDay < 1 || birthDay > 31) {
        cout << "´íÎó£¬ÈÕÆÚ±ØÐëÔÚ1-31Ö®¼ä£¡"<< endl;
        return 1;
    }
    int realAge, lunarAge;
    calculateAges(birthYear, birthMonth, birthDay, realAge, lunarAge);
    cout << "\n²éÑ¯½á¹û" << endl;
    cout << "ÄúµÄÖÜËêÊÇ£º" << realAge << "Ëê" << endl;
    cout << "ÄúµÄÐéËêÊÇ£º" << lunarAge << "Ëê" << endl;
    return 0;
}	
