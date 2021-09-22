#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

struct LoadPersonsParams {
    string_view db_name;
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
    int min_age;
    int max_age;
    string_view name_filter;

    LoadPersonsParams& SetDBName(string_view db_name) {
        this->db_name = db_name;
        return *this;
    }

    LoadPersonsParams& SetDBConnectionTimeOut(int db_connection_timeout) {
        this->db_connection_timeout = db_connection_timeout;
        return *this;
    }

    LoadPersonsParams& SetAllowExceptions(bool db_allow_exceptions) {
        this->db_allow_exceptions = db_allow_exceptions;
        return *this;
    }

    LoadPersonsParams& SetDBLogLevel(DBLogLevel db_log_level) {
        this->db_log_level = db_log_level;
        return *this;
    }

    LoadPersonsParams& SetMinAge(int min_age) {
        this->min_age = min_age;
        return *this;
    }

    LoadPersonsParams& SetMaxAge(int max_age) {
        this->max_age = max_age;
        return *this;
    }

    LoadPersonsParams& SetNameFilter(string_view name_filter) {
        this->name_filter = name_filter;
        return *this;
    }
};

vector<Person> LoadPersons(LoadPersonsParams params) {
    DBConnector connector(params.db_allow_exceptions, params.db_log_level);
    DBHandler db;

    if (params.db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(params.db_name, params.db_connection_timeout);
    } else {
        db = connector.Connect(params.db_name, params.db_connection_timeout);
    }

    if (!params.db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;

    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << params.min_age << " and "s << params.max_age << " "s
              << "and Name like '%"s << db.Quote(params.name_filter) << "%'"s;

    DBQuery query(query_str.str());

    vector<Person> persons;

    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }

    return persons;
}

enum class TimeValidity {
    IsValid,
    YearTooSmall,
    YearTooBig,
    MonthTooSmall,
    MonthTooBig,
    DayTooSmall,
    DayTooBig,
    HourTooSmall,
    HourTooBig,
    MinuteTooBig,
    MinuteTooSmall,
    SecondTooBig,
    SecondTooSmall
};

TimeValidity CheckDateTimeValidity(const DateTime& dt) {
    TimeValidity result = TimeValidity::IsValid;

    if (dt.year < 1) {
        result = TimeValidity::YearTooSmall;
    }
    if (dt.year > 9999) {
        result = TimeValidity::YearTooBig;
    }

    if (dt.month < 1) {
        result = TimeValidity::MonthTooSmall;
    }
    if (dt.month > 12) {
        result = TimeValidity::MonthTooBig;
    }

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt.day < 1) {
        result = TimeValidity::DayTooSmall;
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        result = TimeValidity::DayTooBig;
    }

    if (dt.hour < 0) {
        result = TimeValidity::HourTooSmall;
    }
    if (dt.hour > 23) {
        result = TimeValidity::HourTooBig;
    }

    if (dt.minute < 0) {
        result = TimeValidity::MinuteTooSmall;
    }
    if (dt.minute > 59) {
        result = TimeValidity::MinuteTooBig;
    }

    if (dt.second < 0) {
        result = TimeValidity::SecondTooSmall;
    }
    if (dt.second > 59) {
        result = TimeValidity::SecondTooBig;
    }

    return result;
}

// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCitySubjson(vector<City>& cities, const Json& json, const string& country_name,
                      const string& country_iso_code, const string& country_phone_code,
                      const string& country_time_zone, const vector<Language>& languages) {
    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();
        cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          country_phone_code + city_obj["phone_code"s].AsString(), country_name,
                          country_iso_code, country_time_zone, languages});
    }
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
        });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        ParseCitySubjson(cities, country_obj["cities"s], country.name, country.iso_code,
                         country.phone_code, country.time_zone, country.languages);
    }
}

int main(int argc, const char* argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
