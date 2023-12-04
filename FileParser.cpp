/*Operations:
    1. Read
    2. Sort
    3. Search
    4. Filter
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <queue>
#include "quicksort.h"
#include "binarysearch.h"

using namespace std;

class CSVFileParser {
    fstream file;
    string **OriginalData;
    string **indexedData;
    string *fileDataType;
public:
    int col, row;
    CSVFileParser() {
        col = 0, row = 0;
        OriginalData = indexedData = nullptr;
        fileDataType = nullptr;
    }
    //Function to Open the file and count the number of columns and rows
    bool openFile(const string &fName) {
        //Opening the File
        file.open(fName, ios::in | ios::out);
        if (!file) {
            return false;
        }
        resetFilePointer();
        //Cache the file
        cacheFile();
        resetFilePointer();
        return true;
    }

    void cacheFile() {
        resetFilePointer();

        //Counting the Columns
        int col = 0;
        string demoLine;
        getline(file, demoLine);
        stringstream str(demoLine);
        while (getline(str, demoLine, ','))col++;
        this->col = col;
        resetFilePointer();
        int row = 0;
        string dline;
        while (getline(file, dline)) {
            row++;
        }
        this->row = row;
        cout << "Row: " << row << endl;
        cout << "Column: " << col << endl;
        resetFilePointer();

        //Allocation of Required Memory
        OriginalData = new string *[col + 1];
        indexedData = new string *[col + 1];
        for (int i = 0; i < col + 1; i++) {
            OriginalData[i] = new string[row];
            indexedData[i] = new string[row];
        }

        //Allocating Memory to store the data type of columns
        fileDataType = new string[col];

        //Storing the CSV data in both Original & Index Array
        string line, tempData;
        int i = 0;
        string tempStr, tempDataType;
        while (getline(file, line)) {
            stringstream str(line);
            for (int j = 0; j < col; j++) {
                getline(str, tempStr, ',');
                tempDataType = getDataType(tempStr);
                OriginalData[j][i] = tempStr;
                indexedData[j][i] = tempStr;
            }
            i++;
        }

        //Finding data type of each column
        for (int j = 0; j < col; j++) {
            fileDataType[j] = getColumnDataType(OriginalData[j]);
            cout << left << setw(10) << fileDataType[j];
        }
        cout << endl;

        //Setting the ID for each row
        OriginalData[col][0] = "ID";
        indexedData[col][0] = "ID";
        for (int i = 1; i < row; i++) {
            OriginalData[col][i] = to_string(i + 1);
            indexedData[col][i] = to_string(i + 1);
        }
        //Displaying the File Data stored in array
        //displayArray(OriginalData);
    }

    //Function to sort the Array
    bool sortColumn(int columnToSort, const string &op = "<=") {
        if (columnToSort <= 0 || columnToSort > col) {
            cout << "Error:: Column out of range";
            return false;
        }
        quickSort(indexedData, columnToSort - 1, col, 1, row - 1, fileDataType[columnToSort - 1], op);
        return true;
    }

    //Function to find element in array
    bool findElement(const string &str, int columnToFind = -1) {
        int index, startPtr = 1;
        int isFound = -1;

        if (columnToFind < -1) {
            cout << "Index Out of Range" << endl;
            return false;
        }
        if (columnToFind == -1) {
            for (int j = 0; j < col; j++) {
                sortColumn(j + 1);
                do {
                    index = binarySearch<string>(indexedData[j], str, startPtr, row - 1);
                    if (index != -1) {
                        isFound++;
                        startPtr = index + 1;

                        if (isFound == 0) {
                            cout << "Element(s) Found" << endl;
                            displayHeaderRow();
                        }
                        displayRow(indexedData, index);
                    }
                } while (index != -1 && startPtr < row);
            }
            if (isFound == -1) {
                cout << "Element Not Found" << endl;
                return false;
            } else {
                return true;
            }
        }
        sortColumn(columnToFind);
        do {
            index = binarySearch<string>(indexedData[columnToFind - 1], str, startPtr, row - 1);
            if (index != -1) {
                startPtr = index + 1;
                isFound++;
                if (isFound == 0) {
                    cout << "Element(s) Found" << endl;
                    displayHeaderRow();
                }
                displayRow(indexedData, index);
            }
        } while (index != -1 && startPtr < row);
        return true;
    }

    //Finding the Datatype:

    //Of a particular element
    static string getDataType(const string &str) {
        int isDec = 0;
        bool isNum = true;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '.') {
                isDec++;
                if (isDec > 1) {
                    isNum = false;
                    break;
                }
                continue;
            }
            if (str[i] > '9') {
                isNum = false;
                break;
            }
        }
        if (isNum) {
            if (isDec == 0 && isValidInt(str)) return "int";
            else if (isDec == 1 && isValidDouble(str)) return "double";
        }
        return "string";
    }

    //Of a whole column
    string getColumnDataType(const string str[]) const {
        return getColumnDataType(str, row, 1);
    }

    static string getColumnDataType(const string str[], int rows, int start = 0) {
        bool isInt = false, isDouble = false;
        string dt;
        for (int i = start; i < rows; i++) {
            dt = getDataType(str[i]);
            if (dt == "string") return "string";
            if (dt == "int") {
                isInt = true;
            } else if (dt == "double") {
                isDouble = true;
            }
        }
        if (isInt && !isDouble) return "int";
        if (isInt) return "double";
        return "string";
    }

    void readFile() {
        resetFilePointer();
        string line, tempData;
        while (getline(file, line)) {
            stringstream str(line);
            for (int i = 0; i < col; i++) {
                getline(str, tempData, ',');
                cout << tempData << "\t";
            }
            cout << endl;
        }
    }

    void displayArray(string **arr) {
        displayArray(arr, row, col);
    }

    static void displayArray(string **arr, int row, int col) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << left << setw(10) << arr[j][i];
            }
            cout << endl;
        }
    }

    void displayHeaderRow(int header = -1) {
        if (header == -1) {
            for (int i = 0; i < col; i++) {
                cout << left << setw(10) << indexedData[i][0];
            }
            cout << endl;
        } else {
            cout << left << setw(10) << indexedData[header][0];
        }
    }

    void displayRow(string **arr, int r) const {
        for (int i = 0; i < col; i++)
            cout << left << setw(10) << arr[i][r];
        cout << endl;
    }

    void displayIndexedArray() {
        displayArray(indexedData);
    };

    //Function to Reset the Read & Write Pointer of the file
    void resetFilePointer() {
        file.clear();
        file.seekp(0);
        file.seekg(0);
    }

    ~CSVFileParser() {
        file.close();
    }
};

int main() {
    int fileOp;
    string fName;
    CSVFileParser obj;
    cout << "*** C.S.V. File Parser ***" << endl << endl;
    do {
        cout << "Enter the File Address: ";
        cin >> fName;
        if (obj.openFile(fName)) {
            cout << "File Opened Successfully" << endl;
            break;
        } else {
            cout << "Error: File could not be opened. Enter the correct file address." << endl;
            continue;
        }
    } while (true);

while (true)
{
        cout << endl << "File Operations:" << endl;
        cout << "1. Display File Data" << endl;
        cout << "2. Sort" << endl;
        cout << "3. Search" << endl;
        cout << "4. Filter" << endl;
        cout << "9. Quit" << endl << endl;
        cout << "Choose Option: ";
        cin >> fileOp;
        cout << endl;

    if (fileOp == 1)
    {
                obj.readFile();
    }
    else if (fileOp == 2)
    {
        int sortType, colToSort;
        do {
            cout << "Select the Sorting Type:" << endl;
            cout << "1. Ascending: A-Z | a-z | 1-10" << endl;
            cout << "2. Descending: Z-A | a-z | 10-1" << endl;
            cout << "Enter Option: ";
            cin >> sortType;
            cout << "Select the Column to Sort: ";
            cin >> colToSort;

            if (colToSort <=0 || colToSort > obj.col) {
                cout << "Column out of range" << endl;
                continue;
            } else if (sortType == 1) {
                obj.sortColumn(colToSort, "<=");
                obj.displayIndexedArray();
                break;
            } else if (sortType == 2) {
                obj.sortColumn(colToSort, ">=");
                obj.displayIndexedArray();
                break;
            } else {
                cout << "Invalid Selection" << endl;
                continue;
            }
        } while (true);        
    }
    else if (fileOp==3)
    {
        string searchElement;
        cout << "Find: " << endl;
        cin >> searchElement;
        if (searchElement.empty() || searchElement == " ") {
            cout << "Invalid Input" << endl;
            continue;
        }
        obj.findElement(searchElement);
    }
    else if (fileOp == 4)
    {
        string filterElement;
        int column;
        cout << "Select the Column to Filter: ";
        cin >> column;
        cout << "Enter the Filter Element: ";
        cin >> filterElement;
        obj.findElement(filterElement, column);     
    }
    else if (fileOp == 9)
    {
        cout<<"Thanks For using FileParser .... !!!!\n";
        break;
    }
    else 
    {
        cout<<"Please Select Valid Operation !!! \n";
    }
  }
    return 0;
}

