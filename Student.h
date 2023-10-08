#include <string>

using namespace std;



class Student{
private:
    string ID;
    string name;
public:
    //Constructor
    Student(string id, string na){
        ID= id;
        name = na;
    }
    //default constructor just in case
    Student(){ID="-1", name = "DEFAULT";}

    //Getter methods
    string getID(){
        return ID;
    }
    string getName(){
        return name;
    }

    //setter methods
    void setName(string s){
        name =s;
    }
    void setID(string s){
        ID = s;
    }
};