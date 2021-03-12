#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

#define TEST
//#define SUBMIT

// �������ṹ�嶨��
struct serverNode {
    int cpuA, cpuB;         // �ڵ�A��B��CPU�����������ڴ��С
    int mermoryA, mermoryB; 
    int purCost, powerCost; // Ӳ���ɱ���ÿ���ܺĳɱ�

    serverNode():cpuA(0), cpuB(0), mermoryA(0), mermoryB(0), purCost(0), powerCost(0) {}
    
    // �вι��캯��
    serverNode(int cpuNum, int mermorySize, int inputPurCost, int inputPowerCost) {
        cpuA = cpuB = cpuNum / 2;
        mermoryA = mermoryB = mermorySize / 2;
        purCost = inputPurCost;
        powerCost = inputPowerCost;
    }

    // ��ӡ�������ڵ���Ϣ
    void serverPrint() {
        cout << cpuA << " " << cpuB << " " << mermoryA << " " << mermoryB << " " << purCost << powerCost << endl;
    }
};

// ������ṹ�嶨��
struct vmNode {
    int cpuVM;              // ��ҪCPU��������
    int mermoryVM;          // ��Ҫ�ڴ��С
    int isDoubleNode;      // �Ƿ�˫�ڵ㲿��

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

// �洢�������ͺŶ�Ӧ����Ϣ
unordered_map<string, serverNode> serverMap;

// �洢������ͺŶ�Ӧ����Ϣ
unordered_map<string, vmNode> vmMap;

// �洢�û�����Ĵ�����ɾ��
vector<vector<string> > requestList;

// �����ܳɱ� = Ӳ������ɱ� + ÿ���ܺĳɱ�
long long totalCost, sumPurCost, sumPowerCost;

// ����������ͺŶ�Ӧ����Ϣ
void inputServerInfo(string serverType, string cpuNum, string mermorySize, string inputPurCost, string inputPowerCost) {
    string temp_serverType  = serverType.substr(1, serverType.find(',') - 2);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',') - 1));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',') - 1));
    int temp_inputPurCost = stoi(inputPurCost.substr(0, inputPurCost.find(',') - 1));
    int temp_inputPowerCost = stoi(inputPowerCost.substr(0, inputPowerCost.find(')') - 1));
    serverMap[temp_serverType] = serverNode(temp_cpuNum, temp_mermorySize, temp_inputPurCost, temp_inputPowerCost);
}

// ����������ͺŶ�Ӧ����Ϣ
void inputVMInfo(string vmType, string cpuNum, string mermorySize, string isDouble) {
    string temp_vmType = vmType.substr(1, vmType.find(',') - 2);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',') - 1));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',' - 1)));
    int temp_isDouble = isDouble[0] - '0';
    vmMap[temp_vmType] = vmNode(temp_cpuNum, temp_mermorySize, temp_isDouble);
}

// �����û����󴢴�
void inputRequest(string operate, string vmType, string vmID) {
    string temp_operate = operate.substr(1, operate.find(',') - 2);
    string  temp_vmType = vmType.substr(0, vmType.find(',') - 1);
    string temp_vmID = vmID.substr(0, vmID.find(',') - 1);
    requestList.push_back({temp_operate, temp_vmType, temp_vmID});
}
int main() {
    
    auto start_time = system_clock::now();

    // ����Cin�����������
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    // ��ϰ���ض����ļ�����
#ifdef TEST
    const string filePath1 = "train_data/trianing-1.txt";
    const string filePath2 = "train_data/trianing-2.txt";
    freopen(filePath1.c_str(), "r", stdin);
#endif

    // ��ȡ����������
    int serverNum;
    string serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost;
    cin >> serverNum;

    cin.get();
    for(int i = 0; i < serverNum; i++) {
        cin >> serverType >> cpuNum >> mermorySize >> inputPurCost >> inputPowerCost;
        inputServerInfo(serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost);
    }
    
    // ��ȡ���������
    int vmNum; 
    string vmType, isDouble;
    cin >> vmNum;
    cin.get();
    for(int i = 0; i < vmNum; i++) {
        cin >> vmType >> cpuNum >> mermorySize >> isDouble;
        inputVMInfo(vmType, cpuNum, mermorySize, isDouble);
    }
    
    // ��ȡ�û�����
    int dayNum, reqNum;
    string operate, vmID;
    cin >> dayNum;
    cin.get();
    for(int day = 0; day < dayNum; day++) {
        cin >> reqNum;
        cin.get();
        for(int req = 0; req < reqNum; req++) {
            cin >> operate >> vmType >> vmID;
            inputRequest(operate, vmType, vmID);
        }
    }

#ifdef TEST
    fclose(stdin);
    const string outputPath = "temp_data/temp_output.txt";
    freopen(outputPath.c_str(), "w", stdout);
    for(auto [type, node] : serverMap) {
        cout << type;
        node.serverPrint();
    }
    for(auto [type, node] : vmMap) {
        cout << type;
        node.vmPirnt();
    }

    for(auto reqs : requestList) {
        for(auto req : reqs) {
            cout << req << " ";
        }
        cout << endl;
    }
#endif

    // �����������ʱ��
    auto end_time = system_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "��ʱ " << double(duration.count()) * microseconds::period::num / microseconds::period::den << " s" << endl;
    return 0;
}

//ע��freopen��ʱ�������ã����컻��C++���������