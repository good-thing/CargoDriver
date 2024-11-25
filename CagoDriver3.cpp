#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 화물차 정보를 저장할 구조체
struct Truck {
    double maxLoad;       // 최대 적재 무게
    double costPerLiter;  // 리터당 기름값
};

// 화물 정보를 저장할 구조체
struct Cargo {
    string name;        // 화물 이름
    double weight;      // 화물 무게
    double distance;    // 화물 운송거리
    double reward;      // 운송 시 수령하는 수당
};

double efficiency = 9.0;  // 연비 고정값


// 최적의 화물 조합을 계산하는 함수
void calBestComb(vector<Cargo>& cargos, const Truck& truck, double& maxProfit, vector<Cargo>& bestCombination) {
     maxProfit = 0.0;                    // 최대 수익 초기화
     bestCombination.clear();            // 이전 조합 초기화
    // 모든 조합을 탐색하기 위해 비트마스크를 사용합니다.
    int n = cargos.size(); // n은 입력 받은 화물의 총 개수
    for (int mask = 0; mask < (1 << n); ++mask) { //비트마스크 방식으로 모든 화물의 선택 여부를 나타내 조합 탐색
        //조합으로 선택 한 화물들의 총 무게, 보상, 운송거리
        double totalWeight = 0.0;
        double totalReward = 0.0;
        double totalDistance = 0.0;           
        vector<Cargo> currentCombination; // 선택한 조합의 화물을 목록에 저장
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // i번째 화물이 선택된 경우
                totalWeight += cargos[i].weight;
                totalReward += cargos[i].reward;
                totalDistance += cargos[i].distance;
                currentCombination.push_back(cargos[i]);
            }
        }
        // 최대 적재 무게를 초과하지 않는 경우에만 수익 계산
        if (totalWeight <= truck.maxLoad) {
            
            double oilCost = (totalDistance / efficiency) * truck.costPerLiter; //연비=9
            double profit = totalReward - oilCost;

            // 최대 수익 업데이트
            if (profit > maxProfit) {
                maxProfit = profit;
                bestCombination = currentCombination; // 현재 조합을 최적 조합으로 설정
            }
        }
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

    // 2.화물 정보 입력
    vector<Cargo> cargos;
    string name;
    double weight, distance, reward;
    // 화물의 이름, 무게, 거리, 수당 입력받기
    cout << "화물의 이름, 무게(Kg), 거리(Km), 보수(원)를 입력하세요\n(예시 : 선풍기 10 100 50000) : ";
    while (cin >> name) {
        if (name == "done") break; // 종료 조건
        cin >> weight >> distance >> reward;
        cargos.push_back(Cargo{ name, weight, distance, reward }); // 화물 정보를 벡터에 추가
        cout << "또 다른 화물이 있나요? (없다면 done을 입력): ";
    }
    // 3. 최적의 조합을 선택하는 알고리즘 수행
    double maxProfit = 0.0;
    vector<Cargo> bestCombination;
    calBestComb(cargos, truck, maxProfit, bestCombination);
    // 결과 출력
    cout << "최적의 화물 조합으로 최대 수익: " << maxProfit << "원\n";
    cout << "선택된 화물 목록 (이름, 무게, 거리, 수당):\n";
    for (const auto& cargo : bestCombination) {
        cout << "이름: " << cargo.name << ", 무게: " << cargo.weight <<
            ", 거리: " << cargo.distance << ", 수당: " << cargo.reward << "\n";
    }

    return 0;
}
