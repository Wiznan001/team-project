#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// 函数声明
double calculateCurrentForTopology1(double V, double R1, double R2, double R3, double R4);
double calculateCurrentForTopology2(double V, double R1, double R2, double R3, double R4);
void printResults(double V, double R1, double R2, double R3, double R4, double I);

int main() {
    cout << "=== 通用电流计算器 ===" << endl;
    cout << "请选择电路拓扑结构:" << endl;
    cout << "1. 拓扑结构1 (R1和R2串联，R3和R4串联，然后并联)" << endl;
    cout << "2. 拓扑结构2 (R1和R2并联，R3和R4并联，然后串联)" << endl;

    int choice;
    while (true) {
        cout << "请输入选择(1或2): ";
        cin >> choice;

        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "无效输入，请重新输入1或2。" << endl;
        }
        else {
            break;
        }
    }

    double V, R1, R2, R3, R4;

    cout << "\n请输入电压值V(伏特): ";
    while (!(cin >> V) || V <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效输入，请输入一个正数: ";
    }

    cout << "请输入电阻R1的阻值(欧姆): ";
    while (!(cin >> R1) || R1 <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效输入，请输入一个正数: ";
    }

    cout << "请输入电阻R2的阻值(欧姆): ";
    while (!(cin >> R2) || R2 <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效输入，请输入一个正数: ";
    }

    cout << "请输入电阻R3的阻值(欧姆): ";
    while (!(cin >> R3) || R3 <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效输入，请输入一个正数: ";
    }

    cout << "请输入电阻R4的阻值(欧姆): ";
    while (!(cin >> R4) || R4 <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "无效输入，请输入一个正数: ";
    }

    double I;
    if (choice == 1) {
        I = calculateCurrentForTopology1(V, R1, R2, R3, R4);
    }
    else {
        I = calculateCurrentForTopology2(V, R1, R2, R3, R4);
    }

    printResults(V, R1, R2, R3, R4, I);

    // 附加功能：计算功率
    double totalResistance;
    if (choice == 1) {
        double R_series1 = R1 + R2;
        double R_series2 = R3 + R4;
        totalResistance = (R_series1 * R_series2) / (R_series1 + R_series2);
    }
    else {
        double R_parallel1 = (R1 * R2) / (R1 + R2);
        double R_parallel2 = (R3 * R4) / (R3 + R4);
        totalResistance = R_parallel1 + R_parallel2;
    }
    double power = V * V / totalResistance;
    cout << "\n附加信息:" << endl;
    cout << "电路总电阻: " << fixed << setprecision(3) << totalResistance << " 欧姆" << endl;
    cout << "电路总功率: " << fixed << setprecision(3) << power << " 瓦特" << endl;

    return 0;
}

// 拓扑结构1计算函数 (R1和R2串联，R3和R4串联，然后并联)
double calculateCurrentForTopology1(double V, double R1, double R2, double R3, double R4) {
    double R_series1 = R1 + R2;
    double R_series2 = R3 + R4;
    double R_total = (R_series1 * R_series2) / (R_series1 + R_series2);
    return V / R_total;
}

// 拓扑结构2计算函数 (R1和R2并联，R3和R4并联，然后串联)
double calculateCurrentForTopology2(double V, double R1, double R2, double R3, double R4) {
    double R_parallel1 = (R1 * R2) / (R1 + R2);
    double R_parallel2 = (R3 * R4) / (R3 + R4);
    double R_total = R_parallel1 + R_parallel2;
    return V / R_total;
}

// 打印结果函数
void printResults(double V, double R1, double R2, double R3, double R4, double I) {
    cout << "\n=== 计算结果 ===" << endl;
    cout << "输入参数:" << endl;
    cout << "电压 V: " << fixed << setprecision(3) << V << " V" << endl;
    cout << "电阻 R1: " << fixed << setprecision(3) << R1 << " Ω" << endl;
    cout << "电阻 R2: " << fixed << setprecision(3) << R2 << " Ω" << endl;
    cout << "电阻 R3: " << fixed << setprecision(3) << R3 << " Ω" << endl;
    cout << "电阻 R4: " << fixed << setprecision(3) << R4 << " Ω" << endl;
    cout << "\n计算得到的电流 I: " << fixed << setprecision(3) << I << " A" << endl;
}
