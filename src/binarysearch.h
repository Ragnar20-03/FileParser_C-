
#ifndef BINARYSEARCH_BINARYSEARCH_H
#define BINARYSEARCH_BINARYSEARCH_H
template<typename T>
int binarySearchRecursion(T arr[],T elementToFind, int startPointer, int endPointer);

template<typename T>
int binarySearch(T arr[],T elementToFind, int startPointer, int endPointer);
#endif //BINARYSEARCH_BINARYSEARCH_H

template<typename T>
bool binarySearchRecursion(T arr[],T elementToFind, int startPointer, int endPointer){
    if(elementToFind==arr[startPointer]) return startPointer;
    if(elementToFind==arr[endPointer]) return endPointer;
    if(startPointer>=endPointer && elementToFind!=arr[endPointer]) return -1;

    int mid=(startPointer+endPointer)/2;
    if(elementToFind==arr[mid]) return mid;
    else if(elementToFind>arr[mid]){
        return binarySearchRecursion(arr,elementToFind,mid+1,endPointer);
    }else if(elementToFind<arr[mid]) {
        return binarySearchRecursion(arr, elementToFind, startPointer, mid - 1);
    }
    return -1;
}
template<typename T>
int binarySearch(T arr[],T elementToFind, int startPointer, int endPointer){
    int low=startPointer;
    int high=endPointer;
    int mid;
    while(low<=high){
        mid=(low+high)/2;
        if(elementToFind==arr[mid]) return mid;
        if(elementToFind>arr[mid]) low=mid+1;
        else if(elementToFind<arr[mid]) high=mid-1;
    }
    return -1;
}