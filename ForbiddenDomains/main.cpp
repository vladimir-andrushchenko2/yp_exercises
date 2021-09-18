#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
   public:
    Domain(std::string domain) : domain_(std::move(domain)) {}

    bool operator==(const Domain& other) const { return domain_ == other.domain_; }

    bool operator<(const Domain& other) const {
        return std::lexicographical_compare(domain_.rbegin(), domain_.rend(), other.domain_.rbegin(), other.domain_.rend());
    }

    bool IsSubdomain(const Domain& larger_domain) const {
        // larger domain has less letters the domain
        // larger domain connot have same length because subdomain has letters after '.'
        // Ex. passed argument potential_subdomain == .dz.ru and domain is gdz.ru have same length
        // but clearly .dz.ru is not subdomain of gdz.ru
        if (!(larger_domain.domain_.size() < domain_.size())) {
            return false;
        }

        // check that domain and subdomains have same suffixes
        if (!std::equal(larger_domain.domain_.rbegin(), larger_domain.domain_.rend(),
                        domain_.rbegin())) {
            return false;
        }

        // check that after suffix subdomain has '.' char
        if (*(domain_.rbegin() + larger_domain.domain_.size()) != '.') {
            return false;
        }

        return true;
    }

   private:
    std::string domain_;
};

class DomainChecker {
   public:
    template <typename Iterator>
    DomainChecker(Iterator begin, Iterator end) : forbidden_domains_(begin, end) {
        // domains have overwritten operator<
        std::sort(forbidden_domains_.begin(), forbidden_domains_.end());

        // delete subdomains
        // If one range is a prefix of another, the shorter range is lexicographically less than the
        // other.
        // aa.ru < aaa.ru domain have overwritten operator< so actually it is (ur.aa < ur.aaa)
        auto new_end =
            std::unique(forbidden_domains_.begin(), forbidden_domains_.end(),
                        [](const Domain& left, const Domain& right) { return right.IsSubdomain(left); });

        forbidden_domains_.erase(new_end, forbidden_domains_.end());
    }

    bool IsForbidden(const Domain& domain) {
        if (forbidden_domains_.empty()) {
            return false;
        }

        auto it =
            std::upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(), domain);

        auto lexicographically_smaller_or_equal_domain = *(it - 1);

        if (lexicographically_smaller_or_equal_domain == domain || domain.IsSubdomain(lexicographically_smaller_or_equal_domain)) {
            return true;
        }

        return false;
    }

   private:
    std::vector<Domain> forbidden_domains_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
std::vector<Domain> ReadDomains(std::istream& input_stream, const size_t n_domains) {
    std::vector<Domain> output;
    output.reserve(n_domains);

    std::string domain;
    for (size_t i = 0; i < n_domains; ++i) {
        std::getline(input_stream, domain);
        output.emplace_back(std::move(domain));
    }

    return output;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

//const string test_string = R"delim(4
//gdz.ru
//maps.me
//m.gdz.ru
//com
//7
//gdz.ru
//gdz.com
//m.maps.me
//alg.m.gdz.ru
//maps.com
//maps.ru
//gdz.ua
//)delim";
//
//std::istringstream test_input{test_string};

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
