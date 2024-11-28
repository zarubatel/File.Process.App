#include <iostream>
#include <fstream>
#include <string>
#include <set>

// Функция для подсчёта количества строк, слов и символов в файле
void processFile(const std::string& filename,
                 int& lineCount,
                 int& wordCount,
                 int& charCount,
                 double& avgLineLength,
                 double& avgWordsPerLine,
                 int& uniqueWordCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    // Инициализация счётчиков
    lineCount = 0;
    wordCount = 0;
    charCount = 0;
    int totalCharsInLines = 0;
    std::set<std::string> uniqueWords;

    std::string line;
    while (std::getline(file, line)) {
        ++lineCount;

        // Подсчёт символов в строке
        for (const auto& ch : line) {
            if (!isspace(ch)) {
                ++charCount;
                ++totalCharsInLines;
            }
        }

        // Подсчёт слов в строке
        size_t pos = 0;
        while ((pos = line.find_first_not_of(" \n\t\r", pos)) != std::string::npos) {
            ++wordCount;
            std::string word = line.substr(pos, line.find_first_of(" \n\t\r", pos) - pos);
            uniqueWords.insert(word);
            pos = line.find_first_of(" \n\t\r", pos + 1);
        }
    }

    // Расчёт средней длины строки
    if (lineCount > 0) {
        avgLineLength = static_cast<double>(totalCharsInLines) / lineCount;
    } else {
        avgLineLength = 0.0;
    }

    // Расчёт среднего количества слов в строке
    if (lineCount > 0) {
        avgWordsPerLine = static_cast<double>(wordCount) / lineCount;
    } else {
        avgWordsPerLine = 0.0;
    }

    // Количество уникальных слов
    uniqueWordCount = uniqueWords.size();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <имя_файла>" << std::endl;
        return 1;
    }

    const std::string filename(argv[1]);
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    double avgLineLength = 0.0;
    double avgWordsPerLine = 0.0;
    int uniqueWordCount = 0;

    processFile(filename, lineCount, wordCount, charCount, avgLineLength, avgWordsPerLine, uniqueWordCount);

    std::cout << "Количество строк: " << lineCount << std::endl;
    std::cout << "Количество слов: " << wordCount << std::endl;
    std::cout << "Количество символов: " << charCount << std::endl;
    std::cout << "Средняя длина строки: " << avgLineLength << std::endl;
    std::cout << "Среднее количество слов в строке: " << avgWordsPerLine << std::endl;
    std::cout << "Количество уникальных слов: " << uniqueWordCount << std::endl;

    return 0;
}
