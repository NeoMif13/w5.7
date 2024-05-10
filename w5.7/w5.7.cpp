
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

void inputFile(const string& filename, const string& text)
{
    ofstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Íå óäàëîñü îòêðûòü ôàéë äëÿ çàïèñè: " << filename << endl;
        return;
    }

    inputFile << text;
    inputFile.close();
}

bool readFile(const string& filename, list<string>& lines)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Íå óäàëîñü îòêðûòü ôàéë äëÿ ÷òåíèÿ: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return true;
}

void filterWords(const list<string>& lines, list<string>& filteredList)
{
    for (const string& line : lines)
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
}

void writeToFile(const string& filename, const list<string>& words)
{
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cout << "Íå óäàëîñü îòêðûòü ôàéë äëÿ çàïèñè: " << filename << endl;
        return;
    }

    for (const string& word : words)
    {
        outputFile << word << endl;
    }

    outputFile.close();
}

void printFileContents(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Íå óäàëîñü îòêðûòü ôàéë äëÿ ÷òåíèÿ: " << filename << endl;
        return;
    }

    string word;
    while (file >> word)
    {
        cout << word << " ";
    }

    file.close();
}

int main()
{
    setlocale(LC_ALL, "RU");
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    cout << "Ââåäèòå òåêñò: " << endl;
    string inputText;
    getline(cin, inputText);

    inputFile(inputFilename, inputText);

    list<string> lines;
    if (!readFile(inputFilename, lines))
    {
        return 1;
    }

    list<string> filteredList;
    filterWords(lines, filteredList);

    writeToFile(outputFilename, filteredList);

    printFileContents(outputFilename);

    return 0;
}
