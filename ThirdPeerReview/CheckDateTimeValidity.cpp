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
