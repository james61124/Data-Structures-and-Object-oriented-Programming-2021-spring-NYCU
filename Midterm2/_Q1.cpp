#include <iostream>
#include "BST.h"
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int file_number = 4;
    //long long index = 1; //use this line instead of "int index = 1" if you use VS2010, otherwise ignore it
    int index = 1;
    while (file_number--) {
        fstream file;
        string filename = "test" + to_string(index) + ".txt";
        cout << filename << endl;
        file.open(filename, ios::in);
        int cmd_num;
        file >> cmd_num;
        BST tree;
        while (cmd_num--) {
            char cmd;
            int value;
            file >> cmd;
            switch (cmd)
            {
            case 'a':
                file >> value;
                cout << "Insert value: " << value << endl;
                tree.InsertNode(value);
                break;
            case 'd':
                file >> value;
                cout << "Delete value: " << value << endl;
                tree.DeleteNode(value);
                tree.LevelOrderPrint();
                cout << endl << endl;
                break;
            case 'i':
                cout << "In-Order Traversal:" << endl;
                tree.InOrderPrint(tree.GetRoot());
                cout << endl << endl;
                break;
            case 'l':
                cout << "Level-Order Traversal:" << endl;
                tree.LevelOrderPrint();
                cout << endl << endl;
                break;
            case 'h':
                cout << "BST height: " << tree.ComputeHeight(tree.GetRoot()) << endl << endl;
                break;
            default:
                break;
            }
        }
        index++;
        file.close();
    }

    system("pause");
    return 0;
}
