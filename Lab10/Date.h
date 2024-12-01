#include <iostream>

class Date {
private:
    int day, month, year;

    // Внутрішня функція для обчислення кількості днів з 01.01.0000
    int daysSinceStart() const;

public:
    Date(int d = 1, int m = 1, int y = 1900);

    // Перевантаження операторів
    bool operator<=(const Date &other) const;
    Date& operator==(int daysToSubtract);

    // Ввід і перевірка валідності
    static Date inputDate();
    static bool isValidDate(int d, int m, int y);

    // Допоміжні методи
    void print() const;
    int daysDifference() const;
};
