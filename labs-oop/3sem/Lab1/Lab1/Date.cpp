#include "Date.h"

TimeDifference TimeDifference::week(7, 0, 0, 0, 0, 0);

inline bool isLeap(unsigned int year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

//MomentOfTime

MomentOfTime MomentOfTime::normalize() const {
	MomentOfTime m = *this;

	if (UTC < 0) {
		bool isOverflow = false;

		m.hour = hour - UTC;

		if (m.hour >= 24) {
			isOverflow = true;
			m.hour %= 24;
		}

		m.day = day + (int)isOverflow;
		isOverflow = false;

		int daysInMonth = MAX_DAYS_IN_MONTH[month];

		if (!isLeap(year) && month == 2) {
			daysInMonth = 28;
		}

		if (m.day > daysInMonth) {
			isOverflow = true;
			m.day %= (daysInMonth + 1);
		}

		m.month = month + (int)isOverflow;
		isOverflow = false;

		if (m.month > 12) {
			isOverflow = true;
			m.month %= 13;
		}

		m.year = year + (int)isOverflow;
	}
	else if (UTC > 0) {
		bool isBorowed = false;

		m.hour = hour - UTC;
		isBorowed = false;

		if (m.hour < 0) {
			isBorowed = true;
			m.hour += 24;
		}

		m.day = day - (int)isBorowed;
		isBorowed = false;

		bool isBorowedYear = false;

		if (m.day < 0) {
			int prevMonth = month - 1;

			if (prevMonth == 0) {
				prevMonth = 12;
				isBorowedYear = true;
			}

			int toAdd = MAX_DAYS_IN_MONTH[prevMonth];

			if (!isLeap(year) && prevMonth == 2) {
				toAdd = 28;
			}
			isBorowed = true;
			m.day += toAdd;
		}

		m.month = month - (int)isBorowed;
		isBorowed = false;

		if (m.month < 0) {
			isBorowed = true;
			m.month += 12;
		}

		isBorowedYear = isBorowed || isBorowedYear;

		m.year = year - (int)isBorowedYear;
		isBorowed = false;
	}

	return m;
}

bool MomentOfTime::operator<(const MomentOfTime& rhs) const {
	if (year != rhs.year) return year < rhs.year;
	if (month != rhs.month) return month < rhs.month;
	if (day != rhs.day) return day < rhs.day;
	if (hour != rhs.hour) return hour < rhs.hour;
	if (minute != rhs.minute) return minute < rhs.minute;
	if (second != rhs.second) return second < rhs.second;
}

bool MomentOfTime::operator==(const MomentOfTime& rhs) const {
	if (year != rhs.year) return false;
	if (month != rhs.month) return false;
	if (day != rhs.day) return false;
	if (hour != rhs.hour) return false;
	if (minute != rhs.minute) return false;
	if (second != rhs.second) return false;

	return true;
}

TimeDifference MomentOfTime::operator-(const MomentOfTime& rhs) {
	return TimeDifference(*this, rhs);
}

//Date

bool Date::isValid() const {
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (second < 0 || second > 59)
		return false;
	if (minute < 0 || minute > 59)
		return false;
	if (hour < 0 || hour > 23)
		return false;

	// February 
	if (month == 2) {
		if (isLeap(year))
			return (day <= 29);
		else
			return (day <= 28);
	}

	if (month == 4 || month == 6 ||
		month == 9 || month == 11)
		return (day <= 30);

	if (abs(UTC) > 12)
		return false;

	return true;
}

void Date::makeRandomDate() {
}

Date Date::operator+(const TimeDifference& diff) const {
	int second = 0, minute = 0, hour = 0, day = 0, month = 0, year = 0;
	int secondDiv = 0, minuteDiv = 0, hourDiv = 0, dayDiv = 0, monthDiv = 0, yearDiv = 0;

	second = (diff.getSecond() + this->getSecond()) % 60;
	secondDiv = (diff.getSecond() + this->getSecond()) / 60;

	minute = (diff.getMinute() + this->getMinute() + secondDiv) % 60;
	minuteDiv = (diff.getMinute() + this->getMinute() + secondDiv) / 60;

	hour = (diff.getHour() + this->getHour() + minuteDiv) % 24;
	hourDiv = (diff.getHour() + this->getHour() + minuteDiv) / 24;

	day = diff.getDay() + this->getDay() + hourDiv;

	month = (diff.getMonth() + this->getMonth()) % 12;
	monthDiv = (diff.getMonth() + this->getMonth()) / 13;

	if (month == 0)
		month = 12;

	year = diff.getYear() + this->getYear() + monthDiv;

	if (month == 2) {
		if (!isLeap(year)) {
			dayDiv = day / 29;
			day %= 28;
			if (day == 0)
				day = 28;
		}
		else {
			dayDiv = day / 30;
			day %= 29;
			if (day == 0)
				day = 29;
		}
	}
	else if (month == 12) {
		dayDiv = day / 32;
		if (day > 31) {
			year++;
			month = 1;
		}
		day %= 31;
		if (day == 0)
			day = 31;
	}
	else {
		dayDiv = day / (MAX_DAYS_IN_MONTH[month] + 1);
		day %= MAX_DAYS_IN_MONTH[month];

		if (day == 0) {
			day = MAX_DAYS_IN_MONTH[month];
		}
	}

	month += dayDiv;

	return Date{ day, month, year, hour, minute, second };
}

Date Date::operator+=(const TimeDifference& diff) {
	*this = *this + diff;
	return *this;
}

Date Date::operator-(const TimeDifference& diff) const {
	TimeDifference result(*this, diff);

	return Date(result.getDay(), result.getMonth(), result.getYear(),
		result.getHour(), result.getMinute(), result.getSecond());
}

Date Date::operator-=(const TimeDifference& diff) {
	*this = *this - diff;
	return *this;
}

TimeDifference Date::operator-(const Date& rhs) const {
	MomentOfTime d1 = this->normalize(), d2 = rhs.normalize();
	return TimeDifference(d1, d2);
}

//Zeller’s algorithm
int Date::getDayOfWeekNumber() const {
	int m = month, y = year;

	if (m == 1) {
		m = 13;
		y--;
	}
	else if (m == 2) {
		m = 14;
		y--;
	}

	int k = y % 100;
	int j = y / 100;
	return (day + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
}

std::string Date::getWeekday() const {
	int w = getDayOfWeekNumber();
	switch (w) {
	case 0: return "Saturday";
	case 1: return "Sunday";
	case 2: return "Monday";
	case 3: return "Tuesday";
	case 4: return "Wednesday";
	case 5: return "Thursday";
	case 6: return "Friday";
	}
}

int Date::getWeekNumberInYear() const {
	int result = 0;
	int JanFirst = Date(1, 1, year, 0, 0, 0).getDayOfWeekNumber() - 2; // Monday == 0 ... Thursday == 3
	if (JanFirst == -2)
		JanFirst = 5;
	if (JanFirst == -1)
		JanFirst = 6;

	Date firstThursday;

	if (JanFirst <= 3)
		firstThursday = Date{ 4 - JanFirst,1,year,0,0,0 };
	else
		firstThursday = Date{ 4 + (7 - JanFirst),1,year,0,0,0 };

	TimeDifference current = *this - firstThursday;

	if (JanFirst > 3 && this->getDay() <= 3 && current.getMonth() == 0) {
		return Date{ 31,12,year - 1,0,0,0 }.getWeekNumberInYear();
	}


	while (current.getDay() > 3 || current.getMonth() > 0) {
		firstThursday += TimeDifference::week;
		result++;
		current = *this - firstThursday;
	}

	return result + 1;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	out << std::setfill('0')
		<< std::setw(2) << date.day << '/' << std::setw(2) << date.month << '/' << date.year << ' '
		<< std::setw(2) << date.hour << ':' << std::setw(2) << date.minute << ':' << std::setw(2) << date.second;
	return out;
}

std::istream& operator>>(std::istream& in, Date& date) {
	in >> date.day;
	in.ignore(1);
	in >> date.month;
	in.ignore(1);
	in >> date.year;
	in.ignore(1);
	in >> date.hour;
	in.ignore(1);
	in >> date.minute;
	in.ignore(1);
	in >> date.second;
	return in;
}

//TimeDifference

TimeDifference::TimeDifference(const MomentOfTime& moment1, const MomentOfTime& moment2) {
	MomentOfTime min, max;

	if (moment1 < moment2) {
		min = moment1;
		max = moment2;
	}
	else {
		min = moment2;
		max = moment1;
	}

	bool isBorowed = false;

	second = max.getSecond() - min.getSecond();
	if (second < 0) {
		isBorowed = true;
		second += 60;
	}

	minute = max.getMinute() - min.getMinute() - (int)isBorowed;
	isBorowed = false;

	if (minute < 0) {
		isBorowed = true;
		minute += 60;
	}

	hour = max.getHour() - min.getHour() - (int)isBorowed;
	isBorowed = false;

	if (hour < 0) {
		isBorowed = true;
		hour += 24;
	}

	day = max.getDay() - min.getDay() - (int)isBorowed;
	isBorowed = false;

	bool isBorowedYear = false;

	if (day < 0) {
		int prevMonth = max.getMonth() - 1;

		if (prevMonth == 0) {
			prevMonth = 12;
			isBorowedYear = true;
		}

		int toAdd = MAX_DAYS_IN_MONTH[prevMonth];

		if (!isLeap(max.getYear()) && prevMonth == 2) {
			toAdd = 28;
		}
		isBorowed = true;
		day += toAdd;
	}

	month = max.getMonth() - min.getMonth() - (int)isBorowed;
	isBorowed = false;

	if (month < 0) {
		isBorowed = true;
		month += 12;
	}

	isBorowedYear = isBorowed || isBorowedYear;

	year = max.getYear() - min.getYear() - (int)isBorowedYear;
	isBorowed = false;
}

bool TimeDifference::isValid() {
	if (month < 0 || month > 12)
		return false;
	if (day < 0 || day > 31)
		return false;
	if (second < 0 || second > 59)
		return false;
	if (minute < 0 || minute > 59)
		return false;
	if (hour < 0 || hour > 23)
		return false;

	return true;
}