#include <iostream>
#include "MyAVLTree.h"

using namespace std;



/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

void ParseInput(MyAVLTree tree){
    string temp;
    getline(cin, temp);
    cout << endl;
    int numLines = stoi(temp);
    for(int i =0; i < numLines; i++){
        string input;
        getline(cin, input);

        if(input.substr(0, 6) == "insert"){
            if((input.find('"') == string::npos) || (input.find(' ') == string::npos) || input.length() < 18){
                cout << "unsuccessful" << endl;
            }
            else {
                string temp2 = input.substr(input.find(' ') + 2, input.length() - 8);
                if (temp2.find(' ') == string::npos) {
                    cout << "unsuccessful" << endl;
                }
                else {
                    string Name = temp2.substr(0, temp2.find(' ') - 1);
                    string ID = temp2.substr(temp2.find(' ') + 1, temp2.length() - Name.size() - 2);
                    tree.insert(ID, Name);
                }
            }
        }
        else if(input == "printInorder"){
            tree.printInOrder();
        }
        else if(input == "printPreorder"){
            tree.printPreOrder();
        }
        else if(input == "printPostorder"){
            tree.printPostOrder();
        }
        else if(input == "printLevelCount"){
            cout << tree.getLevelCount() << endl;
        }
        else if(input.substr(0, 13) == "removeInorder"){
            string secondHalf = input.substr(13, input.length() - 13);
            string index;
            if(secondHalf.length() > 1) {
                index = input.substr(14, input.length() - 14);
                tree.removeInOrderN(index);
            }
            else
                cout << "unsuccessful" << endl;
        }
        else if(input.substr(0, 6) == "remove"){
            string secondHalf = input.substr(6, input.length() - 6);
            string id;
            if(secondHalf.length() > 1) {
                id = input.substr(7, input.length() - 7);
                tree.removeID(id);
            }
            else
                cout << "unsuccessful" << endl;
        }
        else if(input.substr(0, 6) == "search"){
            if(input.length() > 6) {
                string IDorName = input.substr(7, input.length() - 7);
                if (IDorName.find('"') != string::npos) {
                    //SEARCHING NAME
                    string Name = IDorName.substr(1, IDorName.length() - 2);
                    tree.searchName(Name);
                } else {
                    //SEARCHING ID
                    string ID = IDorName;
                    tree.searchID(ID);
                }
            }
            else
                cout << "unsuccessful" << endl;

        }
        else
            cout << "unsuccessful" << endl;

    }


}



int main(){

    MyAVLTree tree;
    ParseInput(tree);


	return 0;
}

