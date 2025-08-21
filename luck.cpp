#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// 获取星座名称
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

// 生成运势描述
string generateLuckDescription(const string& sign) {
    vector<string> luckLevels = {"大吉", "吉", "中吉", "小吉", "平", "小凶", "凶"};
    vector<string> descriptions = {
        "今日运势极佳，适合主动出击，易获意外收获。",
        "人际关系和谐，工作效率提升，可把握合作机会。",
        "整体平稳向好，细节处多用心，能避免小失误。",
        "有小惊喜出现，保持积极心态，做事更顺利。",
        "运势平淡，宜稳守待变，避免冲动决策。",
        "需注意沟通方式，易生小摩擦，耐心应对可化解。",
        "建议以静制动，减少冒险行为，保持心态平和。"
    };
    vector<string> luckyColors = {"红色", "黄色", "绿色", "蓝色", "紫色", "白色", "粉色"};
    
    srand(time(0));
    string luck = luckLevels[rand() % luckLevels.size()];
    string desc = descriptions[rand() % descriptions.size()];
    string color = luckyColors[rand() % luckyColors.size()];
    int num = rand() % 9 + 1;
    
    // 获取当前日期
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date = to_string(1900 + ltm->tm_year) + "年" + 
                 to_string(1 + ltm->tm_mon) + "月" + 
                 to_string(ltm->tm_mday) + "日";
    
    string result = date + " " + sign + "运势查询结果\n";
    result += "整体运势：" + luck + "\n";
    result += "运势描述：" + desc + "\n";
    result += "幸运颜色：" + color + "\n";
    result += "幸运数字：" + to_string(num) + "\n";
    return result;
}

// 导出至文件
bool exportToFile(const string& content, const string& filename = "今日星座运势.txt") {
    ofstream outFile(filename, ios::out);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << content;
    outFile.close();
    return true;
}

int main() {
    cout << "=== 星座运势查询工具 ===" << endl;
    
    // 输入生日
    int month, day;
    cout << "请输入您的生日（月 日，用空格分隔）：";
    cin >> month >> day;
    
    // 验证日期合法性
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "日期输入不合法！" << endl;
        return 1;
    }
    
    // 获取星座并生成运势
    string sign = getZodiacSign(month, day);
    cout << "\n您的星座是：" << sign << endl;
    
    string luckContent = generateLuckDescription(sign);
    cout << "\n--- 今日运势 ---\n" << luckContent << endl;
    
    // 导出文件
    char choice;
    cout << "是否将结果导出至文件？(y/n)：";
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        if (exportToFile(luckContent)) {
            cout << "运势已成功导出至 今日星座运势.txt" << endl;
        } else {
            cout << "文件导出失败！" << endl;
        }
    } else {
        cout << "已取消导出，感谢使用！" << endl;
    }
    
    return 0;
}
