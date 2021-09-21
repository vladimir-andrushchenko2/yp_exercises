#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);

        if (reachable_lists_.count(start) < 1) {
            return result;
        }

        const set<int>& reachable_stations = reachable_lists_.at(start);

        if (!reachable_stations.empty()) {
            auto it = reachable_stations.lower_bound(finish);

            // если есть прямой экспресс возвращаю 0
            if (*it == finish) {
                return 0;
            }

            // если нужно добраться из 5 в 0 при возможной отправке только в -2
            // lower_bound не найдет числа не меньше 0 и укажет на end
            // поэтому проверяю станцию по адресу меньшую 0 и нахожу -2
            if (it == reachable_stations.end()) {
                result = std::min(result, std::abs(*(--it) - finish));

            // в случае из 4 в -2 с доступной станции из 4 только в 10
            // it указывает на begin, все доступные станции больше нужного адреса
            } else if (it == reachable_stations.begin()) {
                result = std::min(result, std::abs(*it - finish));

            // если it указывает на число большее чем finish
            // проверяю так же число меньшее чем финиш
            } else {
                result = std::min({result,
                    std::abs(*it - finish),
                    std::abs(*(--it) - finish)
                });
            }
        }

        return result;
    }

private:
    unordered_map<int, set<int>> reachable_lists_;
};

/*
const std::string test = R"d(7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100
)d";

std::istringstream test_input{test};
*/

int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD"s) {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO"s) {
            cout << routes.FindNearestFinish(start, finish) << "\n"s;
        }
    }
}
