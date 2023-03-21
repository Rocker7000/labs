

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string line, new_line, result_line; 
    char prev_char = '\0';


    ifstream file("cmd.txt"); // відкриття файлу для читання
  
    if (file.is_open()) { // перевірка, чи вдалося відкрити файл
        while (getline(file, line)) { // зчитування рядка з файлу у змінну line
            new_line = "";
            if (line.length() < 1) { 
                if (prev_char != '\n') {
                    new_line = '\n'; 
                    prev_char = '\n';
                }
            }

            for (char& c : line) { // проходження по кожному символу в рядку
                if (c != ' ' && c != '\t' && c != '\n') { // якщо символ не є пропуском, додати його до нового рядка
                    new_line += c;
                }
                else if (prev_char != ' ' && prev_char != '\t' && prev_char != '\n') { // якщо це перший пропуск підряд, додати один пропуск до нового рядка
                    new_line += c;
                }
                prev_char = c;\
            }

            result_line += new_line;
        }
        file.close(); // закриття файлу
    }
    else {
        return 1;
    }

    ofstream outfile("cmd.txt", ios::app); // відкриття файлу для запису
    if (outfile.is_open()) { // перевірка, чи вдалося відкрити файл
        outfile << "\n" << result_line; // запис нового рядка в файл
        outfile.close(); // закриття файлу
    }
    else {
        return 1;
    }

    return 0;
}