#include "Node.h"
#include <vector>
#include <queue>


class MyAVLTree {
private:
    Node* TreeRoot;
public:

    MyAVLTree(){
        TreeRoot = nullptr;
    }

    //Takes name input and returns if its a valid Name
    bool isValidName(string name){
        for(int i = 0; i < name.length(); i++){
            char ch = name[i];
            // A = 65
            // Z = 90
            // a = 97
            // z = 122
            // space = 32
            if (ch < 65 || (90 < ch && ch < 97) || (ch > 122)){
                if(ch == 32){

                }
                else
                return false;
            }
        }
        return true;
    }

    // Takes string input and returns if all chars are numbers
    bool isValidNumber(string name){
        for(int i = 0; i < name.length(); i++){
            char ch = name[i];
            // 0 = 48
            // 9 = 57
            if (ch < 48 || ch > 57){
                return false;
            }
        }
        return true;
    }

    //setter method
    void setRoot(Node* r){
        TreeRoot = r;
    }

    //Returns the node->left->left-> ...
    Node* findMin(Node* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    //Returns the height of a given node
    int getLevelCount(Node* root){//Checked and working (1-based)

        int lvl1, lvl2;
        if(root == nullptr) {
            return 0;// I can change it to return 1 if I want it 1-based
        }
        else {
            //gets the height of the left and right nodes and returns the larger of the two
            lvl1 = getLevelCount(root->left);
            lvl2 = getLevelCount(root->right);
            return max(lvl2, lvl1)+1;
        }
    }
    //Simplifies code / maxes it cleaner by getting rid of a parameter
    int getLevelCount(){
        return getLevelCount(TreeRoot);
    }

    //returns the balance factor of a given code
    int balanceFactor(Node* root){
        // Balance Factor = Height(node->left) - Height(node->right)
        return getLevelCount(root->left) - getLevelCount(root->right);
    }

    //Returns the corrected/balanced Node
    Node* rotateLeft(Node* root){
        Node* grandchild = root->right->left;//This makes sure no node gets accidently lost
        Node* newParent = root->right;
        newParent->left = root;
        root->right = grandchild;
        return newParent;
    }
    //Returns the corrected/balanced Node
    Node* rotateRight(Node* root){
        Node* grandchild = root->left->right;//This makes sure no node gets accidently lost
        Node* newParent = root->left;
        newParent->right = root;
        root->left = grandchild;
        return newParent;
    }

    //Returns the corrected balanced Node
    Node* balance(Node* root){
        int balFac = balanceFactor(root);
        //Right heavy case
        if (balFac == -2) {
            // Right-Right case
            if (balanceFactor(root->right) == -1)
                return rotateLeft(root);
            // Right-Left case
            else{
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        //Left heavy case
        if (balanceFactor(root) == 2) {
            // Left-Left case
            if (balanceFactor(root->left) == 1)
                return rotateRight(root);
            // left-Right case
            else{
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }
        return root;
    }

    //Inserts Node in and auto-balances it
    Node* insert(Node* root, Student S){

        if (root == nullptr) {//Once a leaf node is reached add node
            cout << "successful" << endl;
            return new Node(S);
        }
        else if (stoi(S.getID()) < stoi(root->getID())) {//If not a leaf and new value is smaller than current position
            root->left = insert(root->left, S);
        }
        else if (stoi(S.getID()) > stoi(root->getID())) {//If not a leaf and new value is larger than current position
            root->right = insert(root->right, S);
        }
        else{//In case a duplicate ID is added by mistake
            cout << "unsuccessful" << endl;
            return root;
        }
        //balances root
        Node* result = balance(root);
        return result;

    }

    //Simplifies code and checks for valid input
    void insert(string id, string nm){
        //Checks of valid input
        if(id.length() != 8 || !isValidNumber(id)){
            cout << "unsuccessful" << endl;
        }
        else if(!isValidName(nm)){
            cout << "unsuccessful" << endl;
        }
        else {
            //I know its valid and inserts
            Student S(id, nm);
            TreeRoot = insert(TreeRoot, S);
        }
    }

    //Removes a given student ID and does NOT balance
    Node* removeID(Node* root, string data, bool& printed){
        //if not there
        if(root == nullptr){
            if(printed){cout << "unsuccessful" << endl; printed =false;}
            return nullptr;
        }
        //once the ID is found
        if(root->getID() == data) {
            if(printed){cout << "successful" << endl; printed =false;}
            if (root->left == nullptr) {//If only 1 child on the right
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {//If only 1 child on the left
                Node* temp = root->left;
                delete root;
                return temp;
            }

            //if there are 2 children find the inorder successor
            Node* InOrderSuccParent = root->right;
            Node* InOrderSucc =InOrderSuccParent->left;
            if(InOrderSucc != nullptr) {
                while (InOrderSucc->left != nullptr) {
                    InOrderSuccParent = InOrderSuccParent->left;
                    InOrderSucc = InOrderSuccParent->left;
                }
                root->setStudent(InOrderSucc->getStudent());
                InOrderSuccParent->left = removeID(root->right, InOrderSucc->getID(), printed);
            }
            else{
                InOrderSuccParent = root;
                InOrderSucc = InOrderSuccParent->right;
                root->setStudent(InOrderSucc->getStudent());
                InOrderSuccParent->right = removeID(root->right, InOrderSucc->getID(), printed);
            }
        }
        else if(root->getID() > data)//if this node does not have the student id
            root->left = removeID(root->left, data, printed);
        else if(root->getID() < data)
            root->right = removeID(root->right, data, printed);
        return root;
    }

    //helper function that simplifies code and checks for valid ID number
    void removeID(string data){
        if(data.length() != 8 || !isValidNumber(data)){ //checks for valid ID
            cout << "unsuccessful" << endl;
        }
        else {
            bool printed = true; //if vaild remove ID number
            TreeRoot = removeID(TreeRoot, data, printed);
            printed = true;
        }
    }
    //returns the name of the student of a given ID number
    void searchID(Node* root, string i, bool& contains){//Checked and working
        if(root == nullptr){}
        else{
            if(root->getID() == i){cout << root->getName() << endl; contains = true;}//print if found.
            else if(root->getID() > i)//if less than current go left
                searchID(root->left, i, contains);
            else if(root->getID() < i)//if larger than current go right
                searchID(root->right, i, contains);
        }
    }

    //helper function that simplifies code and checks for valid ID number
    void searchID (string i){
        if(i.length() != 8 || !isValidNumber(i)){ //checks for valid ID
            cout << "unsuccessful" << endl;
        }
        else {
            bool contains = false;
            searchID(TreeRoot, i, contains);
            if (!contains) {
                cout << "unsuccessful" << endl;
            }
        }
    }

    //returns the number of nodes in a tree
    int getCount(Node* root){
        if(root == nullptr)
            return 0;
        else{
            return 1 + getCount(root->left) + getCount(root->right);
        }
    }
    //helper function
    int getCount(){
        return getCount(TreeRoot);
    }

    //prints the ID of a given student
    void searchName(Node* root, string s, bool& contains){
        //if no node there do nothing
        if(root == nullptr){}
        else{
            if(root->getName() == s){cout << root->getID() << endl; contains = true;}//if found print
            searchName(root->left, s, contains);//if not found continue looking
            searchName(root->right, s, contains);//if not found continue looking
        }
    }

    //helper function that simplifies code
    void searchName(string s){
        bool contains = false;
        searchName(TreeRoot, s, contains);
        if(!contains){
            cout << "unsuccessful" << endl;
        }
    }

    //adds all the nodes in order to the printing string reference
    void printInOrder(Node* root, string& printing){ //In ORDER = Left Node Right
        if(root == nullptr)
            cout << "";
        else{
            printInOrder(root->left, printing);
            printing = printing + root->getName() + ", ";
            printInOrder(root->right, printing);
        }
    }

    //creates a string, runs it through printInOrder, and prints it.
    void printInOrder(){
        if(TreeRoot == nullptr){
            cout << "unsuccessful" << endl;
        }
        else {
            string printing = "";
            printInOrder(TreeRoot, printing);
            cout << printing.substr(0, printing.length()-2) << endl;
        }
    }

    //adds all the nodes pre-order to the printing string reference
    void printPreOrder(Node* root, string& printing){ //Pre ORDER = Node Left Right
        if(root == nullptr)
            cout << "";
        else{
            printing = printing + root->getName() + ", ";
            printPreOrder(root->left, printing);
            printPreOrder(root->right, printing);
        }
    }

    //creates a string, runs it through printPreOrder, and prints it.
    void printPreOrder(){
        if(TreeRoot == nullptr){
            cout << "unsuccessful" << endl;
        }
        else {
            string printing = "";
            printPreOrder(TreeRoot, printing);
            cout << printing.substr(0, printing.length()-2) << endl;
        }
    }

    //adds all the nodes post-order to the printing string reference
    void printPostOrder(Node* root, string& printing){ //Post ORDER = Left Right Node
        if(root == nullptr)
            cout << "";
        else{
            printPostOrder(root->left, printing);
            printPostOrder(root->right, printing);
            printing = printing + root->getName() + ", ";
        }
    }

    //creates a string, runs it through printPostOrder, and prints it.
    void printPostOrder(){
        if(TreeRoot == nullptr){
            cout << "unsuccessful" << endl;
        }
        else {
            string printing = "";
            printPostOrder(TreeRoot, printing);
            cout << printing.substr(0, printing.length()-2) << endl;
        }
    }

    //removes the Nth node of the tree going in order. 0 is the first node
    Node* removeInOrderN(Node* root, int& count, int n){ //Checked and working

        //IN ORDER = Left Node Right
        if (root == nullptr) {
            return nullptr;
        }
        //LEFT
        root->left = removeInOrderN(root->left, count, n);
        count++;

        //NODE
        if (count == n) {//checks the current node

            if (root->left == nullptr) {//One child on right / No children
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {//One child on left
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = findMin(root->right); //Two children finds inorder successor.
            root->setStudent(temp->getStudent());
            root->right = removeInOrderN(root->right, count, n + 1);
            count = -1;
        }
        //RIGHT
        root->right = removeInOrderN(root->right, count, n);

        return root;
    }

    //helper function that simplifies code and tests edge cases
    void removeInOrderN(string n){
        //Makes sure N is valid number
        if(!isValidNumber(n)){
            cout << "unsuccessful" << endl;
        }
        else {
            if(stoi(n) < 0 || stoi(n) > getCount()){}
            else {
                int cnt = -1;
                removeInOrderN(TreeRoot, cnt, stoi(n));//if valid run function
                cnt = -1;
                cout << "successful" << endl;
            }
        }
    }

    //getter function
    Node* getRoot(){
        return TreeRoot;
    }


};