#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 화물 정보를 저장할 구조체
struct Cargo {
    string name;        // 화물 이름
    double weight;      // 화물 무게
    double distance;    // 차고로부터의 거리
    double reward;      // 운송 시 수령하는 수당
};

// 화물차 정보를 저장할 구조체
struct Truck {
    double maxLoad;       // 최대 적재 무게
    double costPerLiter;  // 리터당 기름값
};

// 화물차의 연비
double efficiency = 9.0;


// 최적의 화물 조합을 계산하는 함수
void calBestComb(const vector<Cargo>& cargos, const Truck& truck, double& maxProfit, vector<Cargo>& bestCombination) {
    maxProfit = 0.0;                    // 최대 수익 초기화
    bestCombination.clear();            // 이전 조합 초기화    
    double totalWeight = 0;             // 화물의 총 무게
    double totalReward = 0;             // 총 수익
    double totalDistance = 0;           // 총 이동 거리
    vector<Cargo> currentCombination;   // 현재 화물 조합


        //
        //
        // 이곳에 최적의 화물 조합을 계산하는 알고리즘을 입력하세요.
        //
        //
       

        // 기름값 계산
    double oilCost = efficiency * truck.costPerLiter;

        // 최종 수익 계산
    double profit = totalReward - oilCost;

        // 최대 수익 갱신
    if (profit > maxProfit) {
        maxProfit = profit;
        bestCombination = currentCombination;  // 최적의 화물 조합 업데이트
    }
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

    // 화물의 이름, 무게, 거리, 수당을 입력받기
    cout << "화물의 이름, 무게(Kg), 거리(Km), 보수(원)를 입력하세요\n(예시 : 선풍기 10 100 50000) : ";
    cin >> name >> weight >> distance >> reward;

    // 화물 정보를 벡터에 추가
    cargos.push_back(Cargo{ name, weight, distance, reward });

    while (true) {

        // 또 다른 화물이 있나요? 물어보기
        cout << "또 다른 화물이 있나요? (없다면 done을 입력) : ";
        cin >> name;

        if (name == "done") {
            break;  // "done" 입력 시 종료
        }

        cin >> weight >> distance >> reward;

        // 화물 정보를 벡터에 추가
        cargos.push_back(Cargo{ name, weight, distance, reward });

    }

    // 3. 최적의 조합을 선택하는 알고리즘 수행
    double maxProfit = 0.0, totalReward = 0.0, fuelCost = 0.0, totalDistance = 0.0, totalWeight = 0.0;
    vector<Cargo> bestCombination;  // 최적의 화물 조합
    calBestComb(cargos, truck, maxProfit, bestCombination);

    // 4. 결과 출력
    cout << "최적의 화물 조합으로 최대 수익: " << maxProfit << "원\n";
    cout << "선택된 화물 목록 (이름, 무게, 거리, 수당):\n";
    for (const auto& cargo : bestCombination) {
        cout << "이름: " << cargo.name << ", 무게: " << cargo.weight << ", 거리: " << cargo.distance << ", 수당: " << cargo.reward << "\n";
    }

    // 디버깅 정보 출력
    cout << "\n[디버깅 정보]\n";
    cout << "총 보수: " << totalReward << "원\n";
    cout << "총 연료 비용: " << fuelCost << "원\n";
    cout << "총 거리: " << totalDistance << "km\n";
    cout << "총 적재 무게: " << totalWeight << "kg\n";

    return 0;
}


