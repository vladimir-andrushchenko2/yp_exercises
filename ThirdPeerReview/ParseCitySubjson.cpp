// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
vector<City> ParseCitySubjson(const Country& country, const Json& json) {
    vector<City> cities;

    for (const auto& city_json : json.AsList()) {
        const auto& city_obj = city_json.AsObject();

        cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          country.phone_code + city_obj["phone_code"s].AsString(), country.name,
                          country.iso_code, country.time_zone, country.languages});
    }

    return cities;
}

// ParseCitySubjson вызывается только из функции ParseCountryJson следующим образом:
pair<vector<Country>, vector<City>> ParseCountryJson(const Json& json) {
    vector<Country> countries;
    vector<City> cities;

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

        for (auto city : ParseCitySubjson(country, country_obj["cities"s])) {
            cities.push_back(move(city));
        }
    }

    return {move(countries), move(cities)};
}
