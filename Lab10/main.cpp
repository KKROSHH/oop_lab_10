#include <iostream>
#include <vector>
#include <algorithm>
#include "Date.h"

int main() {
    int n;
    std::cout << "Enter number of dates: ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "Error: Number of dates must be positive.\n";
        return 1;
    }

    std::vector<Date> dates;
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter date #" << (i + 1) << ":\n";
        dates.push_back(Date::inputDate());
    }

    // Сортування дат
    std::sort(dates.begin(), dates.end(), [](const Date &a, const Date &b) {
        return a.daysDifference() < b.daysDifference();
    });

    std::cout << "\nSorted Dates:\n";
    for (const auto &date : dates) {
        date.print();
    }

    // Зменшення кожної дати
    int daysToSubtract;
    std::cout << "\nEnter number of days to subtract from each date: ";
    std::cin >> daysToSubtract;

    if (daysToSubtract < 0) {
        std::cerr << "Error: Cannot subtract a negative number of days!\n";
        return 1;
    }

    for (auto &date : dates) {
        date == daysToSubtract;
    }

    std::cout << "\nDates after subtraction:\n";
    for (const auto &date : dates) {
        date.print();
    }

    return 0;
}
