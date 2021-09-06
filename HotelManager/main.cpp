#include <iostream>

using namespace std;

class HotelManager {
public:
    void Book(???);
    int ComputeClientCount(???);
    int ComputeRoomCount(???);

private:
    ? ? ?
};

int main() {
    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(???);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(???) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(???) << "\n";
            }
        }
    }

    return 0;
}
