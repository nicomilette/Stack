#include <iostream>
using namespace std;

template <typename T>
Stack<T>::Stack(int initialValue){
    theStack = new T[50];
    theSize = 0;
}

template <typename T>
Stack<T>::~Stack(){
    delete [] theStack;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs){
    for(int i = 0; i < rhs.size(); i++) push(rhs.theStack[i]);
}

template <typename T>
Stack<T>::Stack(Stack<T> && rhs) : theStack{rhs.theStack}, theSize{rhs.theSize}{
    rhs.theStack = nullptr;
    rhs.theSize = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs){
    T copy = rhs;
    std::swap(*this, rhs);
    return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && rhs){ 
    std::swap(theSize, rhs.theSize);
    std::swap(theStack, rhs.theStack);
    return *this;
}

template <typename T>
bool Stack<T>::empty() const{
    return (theSize == 0);
}

template <typename T>
void Stack<T>::clear(){
    while(!empty()) pop();
} 

template <typename T>
int Stack<T>::size() const{
    return theSize;
}

template <typename T>
void Stack<T>::push(const T& x){
    theSize++;
    theStack[theSize-1] = x;
}

template <typename T>
void Stack<T>::push(T && x){
    theSize++;
    theStack[theSize-1] = std::move(x);
}

template <typename T>
void Stack<T>::pop(){
    theSize--;
}

template <typename T>
T& Stack<T>::top(){
    return theStack[theSize-1];
}

template <typename T>
const T& Stack<T>::top() const{
    return std::move(theStack[theSize-1]);
} 

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const{
    for(int i = 0; i < theSize; i++){
        os << theStack[i] << ofc;
    }
}

template <typename T>
ostream& operator<< (std::ostream& os, const Stack<T>& a){
    a.print(os, ' ');
    return os;
}

template <typename T>
bool Stack<T>::equals(const Stack<T>& rhs) const{
    if (size() != rhs.size()) return false;
    for(int i = 0; i < size(); i++) if(theStack[i] != rhs.theStack[i]) return false;
    return true;
}

template <typename T>
bool operator== (const Stack<T>& a, const Stack <T>& b){
    return a.equals(b);
}

template <typename T>
bool operator!= (const Stack<T>& a, const Stack <T>& b){
    return !(a == b);
}

template <typename T>
bool Stack<T>::lessequals(const Stack<T>& rhs) const{
    if (size() != rhs.size()) return false;
    for(int i = 0; i < size(); i++) if(!(theStack[i] <= rhs.theStack[i])) return false;
    return true;
}

template <typename T>
bool operator<= (const Stack<T>& a, const Stack <T>& b){
    return a.lessequals(b);
}