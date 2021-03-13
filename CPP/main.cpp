#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

#define TEST
//#define SUBMIT

// 服务器结构体定义
struct serverNode {
    int cpuA, cpuB;         // 节点A和B的CPU核心数量和内存大小
    int mermoryA, mermoryB; 
    int purCost, powerCost; // 硬件成本和每日能耗成本

    serverNode():cpuA(0), cpuB(0), mermoryA(0), mermoryB(0), purCost(0), powerCost(0) {}
    
    // 有参构造函数
    serverNode(int cpuNum, int mermorySize, int inputPurCost, int inputPowerCost) {
        cpuA = cpuB = cpuNum / 2;
        mermoryA = mermoryB = mermorySize / 2;
        purCost = inputPurCost;
        powerCost = inputPowerCost;
    }

    // 打印服务器节点信息
    void serverPrint() {
        cout << cpuA << " " << cpuB << " " << mermoryA << " " << mermoryB << " " << purCost << " " << powerCost << endl;
    }
};

// 虚拟机结构体定义
struct vmNode {
    int cpuVM;              // 需要CPU核心数量
    int mermoryVM;          // 需要内存大小
    int isDoubleNode;      // 是否双节点部署

    vmNode() : cpuVM(0), mermoryVM(0), isDoubleNode(0) {}

    vmNode(int cpuNum, int mermorySize, int isDouble) {
        cpuVM = cpuNum; 
        mermoryVM = mermorySize;        
        isDoubleNode = isDouble;
    }

    void vmPirnt() {
        cout << cpuVM << " " << mermoryVM << " " << isDoubleNode << endl;
    }
};

// 存储服务器型号对应的信息<key:型号，value:服务器node>
unordered_map<string, serverNode> serverMap;

// 存储虚拟机型号对应的信息<key:型号，value:虚拟机node>
unordered_map<string, vmNode> vmMap;

// 存储用户请求的创建和删除
vector<vector<string> > requestList;

// 计算总成本 = 硬件购买成本 + 每日能耗成本
long long totalCost, sumPurCost, sumPowerCost;

// 输入服务器型号对应的信息
void inputServerInfo(string serverType, string cpuNum, string mermorySize, string inputPurCost, string inputPowerCost) {
    string temp_serverType  = serverType.substr(1, serverType.find(',') - 1);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',')));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',')));
    int temp_inputPurCost = stoi(inputPurCost.substr(0, inputPurCost.find(',')));
    int temp_inputPowerCost = stoi(inputPowerCost.substr(0, inputPowerCost.find(')')));
    serverMap[temp_serverType] = serverNode(temp_cpuNum, temp_mermorySize, temp_inputPurCost, temp_inputPowerCost);
}

// 输入虚拟机型号对应的信息
void inputVMInfo(string vmType, string cpuNum, string mermorySize, string isDouble) {
    string temp_vmType = vmType.substr(1, vmType.find(',') - 1);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',')));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',')));
    int temp_isDouble = isDouble[0] - '0';
    vmMap[temp_vmType] = vmNode(temp_cpuNum, temp_mermorySize, temp_isDouble);
}

// 储存输入用户创建请求
void inputRequest(string operate, string vmType, string vmID) {
    string temp_operate = operate.substr(1, operate.find(',') - 1);
    string  temp_vmType = vmType.substr(0, vmType.find(','));
    string temp_vmID = vmID.substr(0, vmID.find(')'));
    requestList.push_back({temp_operate, temp_vmType, temp_vmID});
}

// 储存输入用户删除请求
void inputRequest(string operate, string vmID) {
    string temp_operate = operate.substr(1, operate.find(',') - 1);
    string temp_vmID = vmID.substr(0, vmID.find(')'));
    requestList.push_back({temp_operate, temp_vmID});
}

int main() {
    
    auto start_time = system_clock::now();

    // 加速cin的输入输出流
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 练习赛重定向到文件输入
#ifdef TEST

    const string filePath1 = "CPP/train_data/training-1.txt";
    const string filePath2 = "CPP/train_data/training-2.txt";
    freopen(filePath1.c_str(), "r", stdin);

#endif
    
    // 读取服务器输入
    int serverNum;
    string serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost;
    cin >> serverNum;

    for(int i = 0; i < serverNum; i++) {
        cin >> serverType >> cpuNum >> mermorySize >> inputPurCost >> inputPowerCost;
        inputServerInfo(serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost);
    }

    cin.get();
    
    // 读取虚拟机输入
    int vmNum; 
    string vmType, isDouble;
    cin >> vmNum;

    for(int i = 0; i < vmNum; i++) {
        cin >> vmType >> cpuNum >> mermorySize >> isDouble;
        inputVMInfo(vmType, cpuNum, mermorySize, isDouble);
    }
    
    // 读取用户请求
    int dayNum, reqNum;
    string operate, vmID;
    cin >> dayNum;

    for(int day = 0; day < dayNum; day++) {
        cin >> reqNum;
        for(int req = 0; req < reqNum; req++) {
            cin >> operate;
            if(operate.substr(1, 3) == "add"){
                cin >> vmType >> vmID;
                inputRequest(operate, vmType, vmID);
            }
            else if (operate.substr(1, 3) == "del") {
                cin >> vmID;
                inputRequest(operate, vmID);
            }
        }
    }

    // 练习赛重定向到文件输出中间数据
#ifdef TEST

    const string outputPath1 = "CPP/temp_data/temp_output.txt";
    freopen(outputPath1.c_str(), "w", stdout);

    // 输出是否成功存储好输入的数据
    for(auto [type, node] : serverMap) {
        cout << type << " ";
        node.serverPrint();
    }
    for(auto [type, node] : vmMap) {
        cout << type << " ";
        node.vmPirnt();
    }

    for(auto reqs : requestList) {
        for(auto req : reqs) {
            cout << req << " ";
        }
        cout << endl;
    }
#endif

/*
    // 练习赛重定向到文件输出最终结果
#ifdef TEST

    const string outputPath2 = "CPP/final_output.txt";
    freopen(outputPath2.c_str(), "w", stdout);

#endif
*/
    // 计算程序所用时间
    auto end_time = system_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "用时 " << double(duration.count()) * microseconds::period::num / microseconds::period::den << " s" << endl;
    return 0;
}
