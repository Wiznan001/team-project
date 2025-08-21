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
