#include <iostream>
//#include <array>
#include <map>
#include <string>
#include <vector>
#include <cassert>

using namespace std::string_literals;

int main() {
    int n_requests;
    std::cin >> n_requests;

//    std::array<int, 100'000> user_id_to_page_he_reached;
//    std::array<double, 1000> n_users_reached_page;
    std::map<int, int> id_to_page;
    std::vector<int> n_users_reached_page(1000);

    std::string request_type;
    for (int i = 0; i < n_requests; ++i) {
        std::cin >> request_type;
        if ("CHEER"s == request_type) {
            int user_id;
            std::cin >> user_id;

            if (id_to_page.count(user_id) == 0) {
                std::cout << 0 << std::endl;
                continue;
            }

            int page_user_is_on = id_to_page[user_id];

            // -1 to exclude current user
            double users_reached_page = n_users_reached_page[page_user_is_on] - 1;
            double all_users = id_to_page.size() - 1;

            if (all_users <= 0) {
                std::cout << 1 << std::endl;
                continue;
            }

            double share_of_users_that_reached_page_excluding_cheered_person =  users_reached_page / all_users;



            std::cout << 1 - share_of_users_that_reached_page_excluding_cheered_person << std::endl;

        } else if ("READ"s == request_type) {
            int id, page;
            std::cin >> id >> page;

            const int previously_reached_page = id_to_page[id];

            assert(page >= previously_reached_page);

            id_to_page[id] = page;

            int read_pages_end = page + 1;
            for (int i = previously_reached_page + 1; i < read_pages_end; ++i) {
                ++n_users_reached_page[i];
            }
            
        } else {
            throw std::logic_error("bad request type "s + request_type);
        }
    }

    return 0;
}
