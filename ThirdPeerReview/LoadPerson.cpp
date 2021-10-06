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