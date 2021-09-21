#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

class RandomContainer {
public:
    void Insert(int val) {
        values_pool_.insert(val);
    }

    void Remove(int val) {
        values_pool_.erase(val);
    }

    bool Has(int val) const {
        return values_pool_.count(val) > 0 ? true : false;
    }

    int GetRand() const {
        uniform_int_distribution<int> distr(0, values_pool_.size() - 1);
        int rand_index = distr(engine_);
        auto it = values_pool_.begin();
        std::advance(it, rand_index);
        return *it;
    }

private:
    set<int> values_pool_;
    mutable mt19937 engine_;
};

const std::string test = R"d(10
INSERT 1
INSERT 2
INSERT 3
HAS 2
RAND
RAND
REMOVE 3
HAS 3
RAND
RAND)d";

std::istringstream test_input{test};

int main() {
    RandomContainer container;
    int query_num = 0;
    test_input >> query_num;
    for (int query_id = 0; query_id < query_num; query_id++) {
        string query_type;
        test_input >> query_type;
        if (query_type == "INSERT"s) {
            int value = 0;
            test_input >> value;
            container.Insert(value);
        } else if (query_type == "REMOVE"s) {
            int value = 0;
            test_input >> value;
            container.Remove(value);
        } else if (query_type == "HAS"s) {
            int value = 0;
            test_input >> value;
            if (container.Has(value)) {
                cout << "true"s << endl;
            } else {
                cout << "false"s << endl;
            }
        } else if (query_type == "RAND"s) {
            cout << container.GetRand() << endl;
        }
    }
}

/*
 true
 1
 3
 false
 2
 1
 */
