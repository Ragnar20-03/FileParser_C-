#ifndef QUICKSORT_QUICKSORT_H
#define QUICKSORT_QUICKSORT_H
#endif //QUICKSORT_QUICKSORT_H
using namespace std;
//Function Declarations

void quickSort(string **array,int colToSort,int cols, int lowIndex, int highIndex, const string& dataType, const string& op);
int partition(string **array,int colToSort,int cols, int lowIndex, int highIndex, const string& pivot, const string& dataType,const string& op);
void swap(string **arr,int cols,int index1, int index2);
bool isValidInt(const string& num);
bool isValidDouble(const string& num);
bool compareStr(const string& str1, const string& str2, const string& dataType, const string& op);
//Function Definitions
void quickSort(string **array,int colToSort,int cols, int lowIndex, int highIndex, const string& dataType,const string& op) {
    if (lowIndex >= highIndex) return;
    string pivot = array[colToSort][highIndex];
    int leftPointer = partition(array,colToSort,cols, lowIndex, highIndex, pivot, dataType,op);
    quickSort(array,colToSort, cols,lowIndex, leftPointer - 1,dataType, op);
    quickSort(array,colToSort, cols,leftPointer + 1, highIndex,dataType, op);
}

int partition(string **array,int colToSort,int cols, int lowIndex, int highIndex, const string& pivot, const string& dataType,const string& op) {
    int rightPointer = highIndex;
    int leftPointer = lowIndex;

    while (leftPointer < rightPointer) {
        while (compareStr(array[colToSort][leftPointer],pivot,dataType,op) && leftPointer < rightPointer){
            leftPointer++;
        }
        while (compareStr(array[colToSort][rightPointer],pivot,dataType,(op=="<="?">=":"<=")) && leftPointer < rightPointer){
            rightPointer--;
        }
        swap(array,cols, leftPointer, rightPointer);
    }
    swap(array,cols, leftPointer, highIndex);
    return leftPointer;
}

void swap(string **arr,int cols,int index1, int index2) {
    for(int i=0;i<cols;i++) {
        string temp = arr[i][index1];
        arr[i][index1] = arr[i][index2];
        arr[i][index2] = temp;
    }
}
bool compareStr(const string& str1, const string& str2, const string& dataType, const string& op){
    if(dataType=="string"){
        if(op=="<=") return str1<=str2;
        else if(op==">=") return str1>=str2;
        else return false;
    }
    else if(dataType=="int" && isValidInt(str1) && isValidInt(str2)){
        if(op=="<=") return (stoi(str1) <=stoi(str2));
        else if(op==">=") return (stoi(str1) >= stoi(str2));
        else return false;

    }else if(dataType=="double" && isValidDouble(str1) && isValidDouble(str2)){
        if(op=="<=") return (stod(str1) <=stod(str2));
        else if(op==">=") return (stod(str1) >= stod(str2));
        else return false;
    }
    return false;
}
bool isValidInt(const string& num){
    try{
        stoi(num);
    }catch(const std::invalid_argument& e){
        return false;
    }catch(const std::out_of_range& e){
        return false;
    }
    return true;
}
bool isValidDouble(const string& num){
    try{
        stod(num);
    }catch(const std::invalid_argument& e){
        return false;
    }catch(const std::out_of_range& e){
        return false;
    }
    return true;
}
