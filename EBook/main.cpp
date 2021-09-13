#include <iostream>
//#include <array>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <array>

using namespace std::string_literals;

class Book {
public:
    Book() : n_users_reached_page(1000) {}

    void UpdateReader(int id, int new_page_number) {
        const int previously_reached_page = GetReadersCurrentPage(id);

        // assert(new_page_number >= previously_reached_page);

        // id_to_page[id] = new_page_number;
        UpdateReadersProgress(id, new_page_number);

        int read_pages_end = new_page_number + 1;
        for (int i = previously_reached_page + 1; i < read_pages_end; ++i) {
            ++n_users_reached_page[i];
        }
    }

    int GetReadersCurrentPage(int id) const {
        if (id_to_page.count(id) == 0) {
            return 0;
        }

        return id_to_page.at(id);
    }

    void UpdateReadersProgress(int id, int new_page_number) {
        assert(new_page_number >= GetReadersCurrentPage(id));
        id_to_page[id] = new_page_number;
    }

public:
    std::map<int, int> id_to_page;
    std::vector<int> n_users_reached_page;
};

int main() {
    int n_requests;
    std::cin >> n_requests;

    Book book;

    std::string request_type;
    for (int i = 0; i < n_requests; ++i) {
        std::cin >> request_type;
        if ("CHEER"s == request_type) {
            int user_id;
            std::cin >> user_id;

            if (book.id_to_page.count(user_id) == 0) {
                std::cout << 0 << std::endl;
                continue;
            }

            int page_user_is_on = book.id_to_page[user_id];

            // -1 to exclude current user
            double users_reached_page = book.n_users_reached_page[page_user_is_on] - 1;
            double all_users = book.id_to_page.size() - 1;

            if (all_users <= 0) {
                std::cout << 1 << std::endl;
                continue;
            }

            double share_of_users_that_reached_page_excluding_cheered_person =  users_reached_page / all_users;



            std::cout << 1 - share_of_users_that_reached_page_excluding_cheered_person << std::endl;

        } else if ("READ"s == request_type) {
            int id, page;
            std::cin >> id >> page;

            book.UpdateReader(id, page);
            
        } else {
            throw std::logic_error("bad request type "s + request_type);
        }
    }

    return 0;
}
