#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
    return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;

    vector<Person> result(count);
    for (Person& p : result) {
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
    }

    return result;
}

int main() {
    const vector<Person> people = []{
    auto people = ReadPeople(cin);

    sort(people.begin(), people.end(),
        [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    });

    return people;
    }();
    
    for (string command; cin >> command;) {
        if (command == "AGE"s) {
            int adult_age;
            cin >> adult_age;

            auto adult_begin = lower_bound(people.begin(), people.end(), adult_age,
                [](const Person& lhs, int age) {
                return lhs.age < age;
            });

            cout << "There are "s << distance(adult_begin, people.end()) << " adult people for maturity age "s
                 << adult_age << '\n';
        } else if (command == "WEALTHY"s) {
            int count;
            cin >> count;

            auto people_copy = people;

            auto head = Head(people_copy, count);

            partial_sort(head.begin(), head.end(), people_copy.end(),
                [](const Person& lhs, const Person& rhs) {
                return lhs.income > rhs.income;
            });

            int total_income = accumulate(head.begin(), head.end(), 0, [](int cur, const Person& p) {
                return p.income + cur;
            });

            cout << "Top-"s << count << " people have total income "s << total_income << '\n';
        } else if (command == "POPULAR_NAME"s) {
            char gender;
            cin >> gender;

            auto people_copy = people;

            IteratorRange range{people_copy.begin(), partition(people_copy.begin(), people_copy.end(),
                                [gender](const Person& p) {
                                    return p.is_male == (gender == 'M');
                                })};

            if (range.begin() == range.end()) {
                cout << "No people of gender "s << gender << '\n';
            } else {
                sort(range.begin(), range.end(),
                    [](const Person& lhs, const Person& rhs) {
                    return lhs.name < rhs.name;
                });
                const string* most_popular_name = &range.begin()->name;
                int count = 1;
                for (auto i = range.begin(); i != range.end();) {
                    auto same_name_end = find_if_not(i, range.end(),
                        [i](const Person& p) {
                        return p.name == i->name;
                    });
                    auto cur_name_count = distance(i, same_name_end);
                    if (cur_name_count > count) {
                        count = cur_name_count;
                        most_popular_name = &i->name;
                    }
                    i = same_name_end;
                }
                cout << "Most popular name among people of gender "s << gender << " is "s << *most_popular_name << '\n';
            }
        }
    }
}
