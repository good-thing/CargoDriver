#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // 정렬

using namespace std;

/* 화물 정보를 저장할 구조체 */
struct Cargo {
    string name;        // 화물 이름
    double weight;      // 화물 무게
    double distance;    // 차고로부터의 거리
    double reward;      // 운송 시 수령하는 기본 보수
    double rewardPerKg; // 수익/무게 비율
};

/* 화물차 정보를 저장할 구조체 */
struct Truck {
    double maxLoad;       // 최대 적재 무게
    double costPerLiter;  // 리터당 기름값
};

/* 화물의 수익/무게 비율 계산 함수 */
void calculateRewardPerKg(vector<Cargo>& cargos) {
    for (auto& cargo : cargos) {
        cargo.rewardPerKg = cargo.reward / cargo.weight;  // 수익/무게 비율 계산
    }
}

double efficiency = 9.0;  // 연비 고정값


/* 그리디 알고리즘으로 최적의 화물 조합을 계산하는 함수 */
void calBestComb(const vector<Cargo>& cargos, const Truck& truck, double& maxProfit, vector<Cargo>& bestCombination, 
    double& totalReward, double& fuelCost, double& totalDistance, double& totalWeight) {
    vector<Cargo> sortedCargos = cargos;
    calculateRewardPerKg(sortedCargos);  // 수익/무게 비율 계산

    // 수익/무게 비율로 내림차순 정렬
    sort(sortedCargos.begin(), sortedCargos.end(), [](const Cargo& a, const Cargo& b) {
        return a.rewardPerKg > b.rewardPerKg;
        });

    totalWeight = 0.0;
    totalReward = 0.0;
    totalDistance = 0.0;
    bestCombination.clear();

    // 그리디 방식으로 화물 선택
    for (const auto& cargo : sortedCargos) {
        if (totalWeight + cargo.weight <= truck.maxLoad) {  // 적재 무게 초과 확인
            totalWeight += cargo.weight;                    // 총 무게 업데이트
            totalReward += cargo.reward;                    // 총 보수 업데이트
            totalDistance += cargo.distance;                // 총 거리 업데이트
            bestCombination.push_back(cargo);               // 선택한 화물 목록에 추가
        }
    }

    // 연비 계산
    fuelCost = (totalDistance / efficiency) * truck.costPerLiter;  // 연료 비용 계산

    // 최종 수익 계산
    maxProfit = totalReward - fuelCost;
}

// 메인 함수
int main() {
    // 1. 화물차 정보 입력
    Truck truck;
    cout << "현재 리터당 기름값을 입력하세요(L/원): ";
    cin >> truck.costPerLiter;
    cout << "화물차의 최대 적재 무게를 입력하세요(Kg): ";
    cin >> truck.maxLoad;

    // 2. 화물 정보 입력
    vector<Cargo> cargos;
    string name;
    double weight, distance, reward;

    cout << "화물의 이름, 무게(Kg), 거리(Km), 보수(원)를 입력하세요\n(예시 : 선풍기 10 100 50000) : ";
    while (true) {  // 무한 루프 사용
        cin >> name;
        if (name == "done") break;  // "done" 입력 시 루프 종료

        cin >> weight >> distance >> reward;
        cargos.push_back(Cargo{ name, weight, distance, reward, 0.0 });

        cout << "또 다른 화물이 있나요? (없다면 done을 입력): ";
    }

    // 3. 최적의 조합을 선택하는 알고리즘 수행
    double maxProfit = 0.0, totalReward = 0.0, fuelCost = 0.0, totalDistance = 0.0, totalWeight = 0.0;
    vector<Cargo> bestCombination;
    calBestComb(cargos, truck, maxProfit, bestCombination, totalReward, fuelCost, totalDistance, totalWeight);

    // 4. 결과 출력
    cout << "\n최적의 화물 조합으로 최대 수익: " << maxProfit << "원\n";
    cout << "선택된 화물 목록 (이름, 무게, 거리, 기본 보수):\n";
    for (const auto& cargo : bestCombination) {
        cout << "이름: " << cargo.name << ", 무게: " << cargo.weight << "kg, 거리: " << cargo.distance << "km, 기본 보수: " << cargo.reward << "원\n";
    }

    // 디버깅 정보 출력
    cout << "\n[디버깅 정보]\n";
    cout << "총 보수: " << totalReward << "원\n";
    cout << "총 연료 비용: " << fuelCost << "원\n";
    cout << "총 거리: " << totalDistance << "km\n";
    cout << "총 적재 무게: " << totalWeight << "kg\n";

    return 0;
}
