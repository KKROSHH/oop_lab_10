#include "Date.h"
#include <cmath>
#include <ctime>

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::daysSinceStart() const {
    tm t = {};
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900; // початок від 1900
    return mktime(&t) / (24 * 60 * 60);
}

bool Date::operator<=(const Date &other) const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date today(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);

    int diff1 = std::abs(this->daysSinceStart() - today.daysSinceStart());
    int diff2 = std::abs(other.daysSinceStart() - today.daysSinceStart());
    return diff1 <= diff2;
}

Date& Date::operator==(int daysToSubtract) {
    if (daysToSubtract < 0) {
        std::cerr << "Error: Cannot subtract a negative number of days!\n";
        return *this;
    }

    this->day -= daysToSubtract;
    while (day <= 0) {
        month--;
        if (month <= 0) {
            month = 12;
            year--;
        }
        day += 30; // Спрощення: припускаємо, що всі місяці мають 30 днів
    }
    return *this;
}

bool Date::isValidDate(int d, int m, int y) {
    if (y < 1900 || y > 2100) return false; // Межі років
    if (m < 1 || m > 12) return false;     // Межі місяців
    if (d < 1 || d > 31) return false;     // Межі днів
    return true;
}

Date Date::inputDate() {
    int d, m, y;

    // Введення дня
    while (true) {
        std::cout << "Enter day (1-31): ";
        std::cin >> d;

        if (std::cin.fail() || d < 1 || d > 31) {
            std::cerr << "Invalid input! Please enter a numeric value between 1 and 31.\n";
            std::cin.clear(); // Очищення потоку
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск некоректного вводу
        } else {
            break;
        }
    }

    // Введення місяця
    while (true) {
        std::cout << "Enter month (1-12): ";
        std::cin >> m;

        if (std::cin.fail() || m < 1 || m > 12) {
            std::cerr << "Invalid input! Please enter a numeric value between 1 and 12.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Введення року
    while (true) {
        std::cout << "Enter year (1900-2100): ";
        std::cin >> y;

        if (std::cin.fail() || y < 1900 || y > 2100) {
            std::cerr << "Invalid input! Please enter a numeric value between 1900 and 2100.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Остаточна перевірка на валідність дати
    if (!isValidDate(d, m, y)) {
        std::cerr << "Error: Invalid date combination! Defaulting to 1/1/1900.\n";
        return Date(1, 1, 1900);
    }

    return Date(d, m, y);
}



void Date::print() const {
    std::cout << day << "/" << month << "/" << year << "\n";
}

int Date::daysDifference() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date today(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
    return std::abs(this->daysSinceStart() - today.daysSinceStart());
}
