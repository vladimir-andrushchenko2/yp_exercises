#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std::string_literals;

class Book {
   public:
    // size needs to be 1001 because max possible page index is 1000
    Book() : unique_people_read_page(kMaxBookSize) {}

    void UpdateReader(int id, int new_page_number) {
        const int previously_reached_page = GetReadersCurrentPage(id);

        UpdateReadersProgress(id, new_page_number);

        int pages_to_mark_as_read_begin = previously_reached_page + 1;
        int pages_to_mark_as_read_end = new_page_number + 1;

        UpdatePagesReadCount(pages_to_mark_as_read_begin, pages_to_mark_as_read_end);
    }

    bool ContainsReader(int id) const { return reader_id_to_her_current_page.count(id) > 0; }

    int GetReadersCurrentPage(int id) const {
        // if book is not read by user then his page is 0
        return ContainsReader(id) ? reader_id_to_her_current_page.at(id) : 0;
    }

    int GetNumberOfReaders() const {
        return static_cast<int>(reader_id_to_her_current_page.size());
    }

    int GetNumberOfReadersWhoReadPage(int page) const { return unique_people_read_page.at(page); }

   private:
    void UpdateReadersProgress(int id, int new_page_number) {
        assert(new_page_number >= GetReadersCurrentPage(id));
        reader_id_to_her_current_page[id] = new_page_number;
    }

    void UpdatePagesReadCount(int pages_begin, int pages_end) {
        for (int i = pages_begin; i < pages_end; ++i) {
            ++unique_people_read_page[i];
        }
    }

   private:
    static constexpr int kMaxBookSize = 1001;

   private:
    std::unordered_map<int, int> reader_id_to_her_current_page;

    // index is page number, value is how many people read the page
    std::vector<int> unique_people_read_page;
};

namespace cheer {
void Cheer(std::ostream& output_stream, int book_reader_id, const Book& book) {
    // if cheered person hasn't read book, then he is ahead of 0 people
    if (!book.ContainsReader(book_reader_id)) {
        output_stream << 0 << std::endl;
        return;
    }

    int page_user_is_on = book.GetReadersCurrentPage(book_reader_id);

    // -1 to exclude current user
    double n_other_people_who_read_page = book.GetNumberOfReadersWhoReadPage(page_user_is_on) - 1;
    double n_other_users = book.GetNumberOfReaders() - 1;

    // if cheered person is the only person to have read the book, then he is ahead of all people
    if (n_other_users == 0) {
        output_stream << 1 << std::endl;
        return;
    }

    // share of people read page the cheered person is currently on
    double share_of_readers_read_page = n_other_people_who_read_page / n_other_users;

    // for example if 60% of people read the page the cheered person is on, then he is ahead of 40%
    // of people. For this reason (1 - share_of_readers_read_page)
    output_stream << 1 - share_of_readers_read_page << std::endl;
}
}  // namespace cheer

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

            cheer::Cheer(std::cout, user_id, book);

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
