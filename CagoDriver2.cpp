#include <iostream>
#include <vector>
#include <string>

//������ �˰���

using namespace std;

struct Cargo {
    string name;
    double weight;
    double distance;
    double reward;
};

struct Truck {
    double maxLoad;
    double costPerLiter;
};

double efficiency = 9.0;

int main() {
    // ȭ���� ���� �Է�
    Truck truck;
    cout << "Ʈ���� �ִ� ���� ����(Kg)�� �Է��ϼ���: ";
    cin >> truck.maxLoad;
    cout << "���ʹ� �⸧��(L�� ��)�� �Է��ϼ���: ";
    cin >> truck.costPerLiter;

    // ȭ�� ���� �Է�
    vector<Cargo> cargos;
    string name;
    double weight, distance, reward;

    while (true) {
        cout << "ȭ���� �̸��� �Է��ϼ��� (�������� 'done' �Է�): ";
        cin >> name;
        if (name == "done") break;

        cout << "ȭ���� ����(Kg)�� �Է��ϼ���: ";
        cin >> weight;
        cout << "ȭ���� �Ÿ�(Km)�� �Է��ϼ���: ";
        cin >> distance;
        cout << "ȭ���� ����(��)�� �Է��ϼ���: ";
        cin >> reward;

        cargos.push_back({ name, weight, distance, reward });
    }

    // ������ ȭ�� ���� ���
    double maxProfit = -1e9; // �ִ� ���� �ʱ�ȭ (������������ ���� ��)
    vector<Cargo> bestCombination;

    // ��� ���� Ȯ�� (��ȿ�������� �ϳ��� ����)
    for (size_t i = 0; i < cargos.size(); ++i) {
        vector<Cargo> currentCombination;
        double totalWeight = 0;
        double totalReward = 0;
        double totalDistance = 0;

        for (size_t j = i; j < cargos.size(); ++j) {
            totalWeight += cargos[j].weight;
            totalReward += cargos[j].reward;
            totalDistance += cargos[j].distance;
            currentCombination.push_back(cargos[j]);

            if (totalWeight > truck.maxLoad) break; // Ʈ���� ���� �Ѱ� �ʰ� �� �ߴ�
            
            double oilCost = (totalDistance / efficiency) * truck.costPerLiter;
            double profit = totalReward - oilCost;

            if (profit > maxProfit) {
                maxProfit = profit;
                bestCombination = currentCombination;
            }
        }
    }

    // ��� ���
    cout << "������ ����:\n";
    for (const auto& cargo : bestCombination) {
        cout << "�̸�: " << cargo.name
            << ", ����: " << cargo.weight
            << ", �Ÿ�: " << cargo.distance
            << ", ����: " << cargo.reward << "\n";
    }
    cout << "�ִ� ����: " << maxProfit << "��\n";

    return 0;
}
