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
        cout << cpuA << " " << cpuB << " " << mermoryA << " " << mermoryB << " " << purCost << " " << powerCost << endl;
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

// �洢�������ͺŶ�Ӧ����Ϣ<key:�ͺţ�value:������node>
unordered_map<string, serverNode> serverMap;

// �洢������ͺŶ�Ӧ����Ϣ<key:�ͺţ�value:�����node>
unordered_map<string, vmNode> vmMap;

// �洢�û�����Ĵ�����ɾ��
vector<vector<string> > requestList;

// �����ܳɱ� = Ӳ������ɱ� + ÿ���ܺĳɱ�
long long totalCost, sumPurCost, sumPowerCost;

// ����������ͺŶ�Ӧ����Ϣ
void inputServerInfo(string serverType, string cpuNum, string mermorySize, string inputPurCost, string inputPowerCost) {
    string temp_serverType  = serverType.substr(1, serverType.find(',') - 1);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',')));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',')));
    int temp_inputPurCost = stoi(inputPurCost.substr(0, inputPurCost.find(',')));
    int temp_inputPowerCost = stoi(inputPowerCost.substr(0, inputPowerCost.find(')')));
    serverMap[temp_serverType] = serverNode(temp_cpuNum, temp_mermorySize, temp_inputPurCost, temp_inputPowerCost);
}

// ����������ͺŶ�Ӧ����Ϣ
void inputVMInfo(string vmType, string cpuNum, string mermorySize, string isDouble) {
    string temp_vmType = vmType.substr(1, vmType.find(',') - 1);
    int temp_cpuNum = stoi(cpuNum.substr(0, cpuNum.find(',')));
    int temp_mermorySize = stoi(mermorySize.substr(0, mermorySize.find(',')));
    int temp_isDouble = isDouble[0] - '0';
    vmMap[temp_vmType] = vmNode(temp_cpuNum, temp_mermorySize, temp_isDouble);
}

// ���������û���������
void inputRequest(string operate, string vmType, string vmID) {
    string temp_operate = operate.substr(1, operate.find(',') - 1);
    string  temp_vmType = vmType.substr(0, vmType.find(','));
    string temp_vmID = vmID.substr(0, vmID.find(')'));
    requestList.push_back({temp_operate, temp_vmType, temp_vmID});
}

// ���������û�ɾ������
void inputRequest(string operate, string vmID) {
    string temp_operate = operate.substr(1, operate.find(',') - 1);
    string temp_vmID = vmID.substr(0, vmID.find(')'));
    requestList.push_back({temp_operate, temp_vmID});
}

int main() {
    
    auto start_time = system_clock::now();

    // ����cin�����������
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ��ϰ���ض����ļ�����
#ifdef TEST

    const string filePath1 = "CPP/train_data/training-1.txt";
    const string filePath2 = "CPP/train_data/training-2.txt";
    freopen(filePath1.c_str(), "r", stdin);

#endif
    
    // ��ȡ����������
    int serverNum;
    string serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost;
    cin >> serverNum;

    for(int i = 0; i < serverNum; i++) {
        cin >> serverType >> cpuNum >> mermorySize >> inputPurCost >> inputPowerCost;
        inputServerInfo(serverType, cpuNum, mermorySize, inputPurCost, inputPowerCost);
    }

    cin.get();
    
    // ��ȡ���������
    int vmNum; 
    string vmType, isDouble;
    cin >> vmNum;

    for(int i = 0; i < vmNum; i++) {
        cin >> vmType >> cpuNum >> mermorySize >> isDouble;
        inputVMInfo(vmType, cpuNum, mermorySize, isDouble);
    }
    
    // ��ȡ�û�����
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

    // ��ϰ���ض����ļ�����м�����
#ifdef TEST

    const string outputPath1 = "CPP/temp_data/temp_output.txt";
    freopen(outputPath1.c_str(), "w", stdout);

    // ����Ƿ�ɹ��洢�����������
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
    // ��ϰ���ض����ļ�������ս��
#ifdef TEST

    const string outputPath2 = "CPP/final_output.txt";
    freopen(outputPath2.c_str(), "w", stdout);

#endif
*/
    // �����������ʱ��
    auto end_time = system_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "��ʱ " << double(duration.count()) * microseconds::period::num / microseconds::period::den << " s" << endl;
    return 0;
}
