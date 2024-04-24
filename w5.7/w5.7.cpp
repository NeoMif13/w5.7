

#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

bool isDelimiter(char c)
{
    static const string delimiters = " .,:;!?-()";
    return delimiters.find(c) != string::npos;
}

bool isSameLetterWord(const string& word)
{
    if (word.empty())
    {
        return false;
    }
    char firstLetter = tolower(word[0]);
    char lastLetter = tolower(word[word.length() - 1]);
    return firstLetter == lastLetter;
}

int main()
{
    setlocale(LC_ALL, "RU");
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    ofstream inputFile(inputFilename);
    if (!inputFile.is_open())
    {
        cout << "Не удалось открыть файл для записи: " << inputFilename << endl;
        return 1;
    }

    cout << "Введите текст: " << endl;
    string inputText;
    getline(cin, inputText);

    inputFile << inputText;
    inputFile.close();

    ifstream outputFile(inputFilename);
    if (!outputFile.is_open())
    {
        cout << "Не удалось открыть файл для чтения: " << inputFilename << endl;
        return 1;
    }

    string line;
    list<string> filteredList;

    while (getline(outputFile, line))
    {
        string word;
        for (char c : line)
        {
            if (isDelimiter(c))
            {
                if (!word.empty() && isSameLetterWord(word))
                {
                    filteredList.push_back(word);
                }
                word.clear();
            }
            else 
            {
                word += c;
            }
        }

        if (!word.empty() && isSameLetterWord(word))
        {
            filteredList.push_back(word);
        }
    }

    outputFile.close();

    ofstream resultFile(outputFilename);
    if (!resultFile.is_open())
    {
        cout << "Не удалось открыть файл для записи: " << outputFilename << endl;
        return 1;
    }

    for (const string& word : filteredList)
    {
        resultFile << word << endl;
    }

    resultFile.close();

    ifstream finalOutputFile(outputFilename);
    if (!finalOutputFile.is_open())
    {
        cout << "Не удалось открыть файл для чтения: " << outputFilename << endl;
        return 1;
    }

    string word;
    while (finalOutputFile >> word)
    {
        cout << word << " ";
    }
    finalOutputFile.close();

    return 0;
}