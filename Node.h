#include "Student.h"



class Node{
private:
    Student student;
public:
    Node* left;
    Node* right;

    //constructor
    Node(Student S){
        student = S;
        left = nullptr;
        right = nullptr;
    }
    //getter methods
    string getID(){
        return student.getID();
    }
    string getName(){
        return student.getName();
    }
    Student getStudent(){
        return student;
    }
    //setter methods
    void setID(string i){
        student.setID(i);
    }
    void setName(string i){
        student.setName(i);
    }
    void setStudent(Student s){
        student = s;
    }
};