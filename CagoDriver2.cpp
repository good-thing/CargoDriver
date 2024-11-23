#include <iostream>
#include <vector>
#include <string>

//영범이 알고리즘

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
    // 화물차 정보 입력
    Truck truck;
    cout << "트럭의 최대 적재 무게(Kg)를 입력하세요: ";
    cin >> truck.maxLoad;
    cout << "리터당 기름값(L당 원)을 입력하세요: ";
    cin >> truck.costPerLiter;

    // 화물 정보 입력
    vector<Cargo> cargos;
    string name;
    double weight, distance, reward;

    while (true) {
        cout << "화물의 이름을 입력하세요 (끝내려면 'done' 입력): ";
        cin >> name;
        if (name == "done") break;

        cout << "화물의 무게(Kg)를 입력하세요: ";
        cin >> weight;
        cout << "화물의 거리(Km)를 입력하세요: ";
        cin >> distance;
        cout << "화물의 보수(원)를 입력하세요: ";
        cin >> reward;

        cargos.push_back({ name, weight, distance, reward });
    }

    // 최적의 화물 조합 계산
    double maxProfit = -1e9; // 최대 수익 초기화 (비현실적으로 낮은 값)
    vector<Cargo> bestCombination;

    // 모든 조합 확인 (비효율적으로 하나씩 선택)
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

            if (totalWeight > truck.maxLoad) break; // 트럭의 적재 한계 초과 시 중단
            
            double oilCost = (totalDistance / efficiency) * truck.costPerLiter;
            double profit = totalReward - oilCost;

            if (profit > maxProfit) {
                maxProfit = profit;
                bestCombination = currentCombination;
            }
        }
    }

    // 결과 출력
    cout << "최적의 조합:\n";
    for (const auto& cargo : bestCombination) {
        cout << "이름: " << cargo.name
            << ", 무게: " << cargo.weight
            << ", 거리: " << cargo.distance
            << ", 보수: " << cargo.reward << "\n";
    }
    cout << "최대 수익: " << maxProfit << "원\n";

    return 0;
}
