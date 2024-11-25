#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ȭ���� ������ ������ ����ü
struct Truck {
    double maxLoad;       // �ִ� ���� ����
    double costPerLiter;  // ���ʹ� �⸧��
};

// ȭ�� ������ ������ ����ü
struct Cargo {
    string name;        // ȭ�� �̸�
    double weight;      // ȭ�� ����
    double distance;    // ȭ�� ��۰Ÿ�
    double reward;      // ��� �� �����ϴ� ����
};

double efficiency = 9.0;  // ���� ������


// ������ ȭ�� ������ ����ϴ� �Լ�
void calBestComb(vector<Cargo>& cargos, const Truck& truck, double& maxProfit, vector<Cargo>& bestCombination) {
     maxProfit = 0.0;                    // �ִ� ���� �ʱ�ȭ
     bestCombination.clear();            // ���� ���� �ʱ�ȭ
    // ��� ������ Ž���ϱ� ���� ��Ʈ����ũ�� ����մϴ�.
    int n = cargos.size(); // n�� �Է� ���� ȭ���� �� ����
    for (int mask = 0; mask < (1 << n); ++mask) { //��Ʈ����ũ ������� ��� ȭ���� ���� ���θ� ��Ÿ�� ���� Ž��
        //�������� ���� �� ȭ������ �� ����, ����, ��۰Ÿ�
        double totalWeight = 0.0;
        double totalReward = 0.0;
        double totalDistance = 0.0;           
        vector<Cargo> currentCombination; // ������ ������ ȭ���� ��Ͽ� ����
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // i��° ȭ���� ���õ� ���
                totalWeight += cargos[i].weight;
                totalReward += cargos[i].reward;
                totalDistance += cargos[i].distance;
                currentCombination.push_back(cargos[i]);
            }
        }
        // �ִ� ���� ���Ը� �ʰ����� �ʴ� ��쿡�� ���� ���
        if (totalWeight <= truck.maxLoad) {
            
            double oilCost = (totalDistance / efficiency) * truck.costPerLiter; //����=9
            double profit = totalReward - oilCost;

            // �ִ� ���� ������Ʈ
            if (profit > maxProfit) {
                maxProfit = profit;
                bestCombination = currentCombination; // ���� ������ ���� �������� ����
            }
        }
    }
}

// ���� �Լ�
int main() {
    // 1. ȭ���� ���� �Է�
    Truck truck;
    cout << "���� ���ʹ� �⸧���� �Է��ϼ���(L/��): ";
    cin >> truck.costPerLiter;
    cout << "ȭ������ �ִ� ���� ���Ը� �Է��ϼ���(Kg): ";
    cin >> truck.maxLoad;

    // 2.ȭ�� ���� �Է�
    vector<Cargo> cargos;
    string name;
    double weight, distance, reward;
    // ȭ���� �̸�, ����, �Ÿ�, ���� �Է¹ޱ�
    cout << "ȭ���� �̸�, ����(Kg), �Ÿ�(Km), ����(��)�� �Է��ϼ���\n(���� : ��ǳ�� 10 100 50000) : ";
    while (cin >> name) {
        if (name == "done") break; // ���� ����
        cin >> weight >> distance >> reward;
        cargos.push_back(Cargo{ name, weight, distance, reward }); // ȭ�� ������ ���Ϳ� �߰�
        cout << "�� �ٸ� ȭ���� �ֳ���? (���ٸ� done�� �Է�): ";
    }
    // 3. ������ ������ �����ϴ� �˰��� ����
    double maxProfit = 0.0;
    vector<Cargo> bestCombination;
    calBestComb(cargos, truck, maxProfit, bestCombination);
    // ��� ���
    cout << "������ ȭ�� �������� �ִ� ����: " << maxProfit << "��\n";
    cout << "���õ� ȭ�� ��� (�̸�, ����, �Ÿ�, ����):\n";
    for (const auto& cargo : bestCombination) {
        cout << "�̸�: " << cargo.name << ", ����: " << cargo.weight <<
            ", �Ÿ�: " << cargo.distance << ", ����: " << cargo.reward << "\n";
    }

    return 0;
}
