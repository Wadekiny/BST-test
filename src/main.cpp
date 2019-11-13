#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "BinaryTree.h"

using namespace std;

int data_count;
int max_data;
int data_number[30];

void NumberRand()
{
    srand((unsigned)time(NULL));
    cout << "input data_count and max_data\n";
    cin >> data_count >> max_data;
    if (data_count > 30) 
    {
        cout << "data_count is too large" <<endl;
        return;
    }
    for (int i=0; i<data_count; i++)
    {
        int rand_number = rand() % max_data;
        int is_same = false;
        for (int j=0; j<i; j++)
        {
            if (rand_number == data_number[j])
            {
                is_same = true;
                break;
            }
        }
        if (is_same == true)
        {
            i--;
            continue;
        }
        data_number[i] = rand_number;
    }
    
    cout << "============================\n";
    cout << "Random number: ";
    for (int i=0; i<data_count; i++) 
    {
        cout << data_number[i] << " ";
    }
    cout << endl;
    cout << "============================\n";
}

int main()
{
    int find_data;
    NumberRand();        

    //创建对象
    BinaryTree bst(data_number, data_count);
    BinaryTree copy;
    bst.BST_Refresh();

    //BST height
    cout << endl << "BST_height is : " << bst.BST_GetHeight() << endl << endl;;

    cout << "==After InOrder==" << endl;
    bst.BST_InOrder(bst.BST_GetStartNode());
    cout << endl << endl;

    bst.BST_LeafNodePrint();//
    bst.BST_ShowTree();

    cout << "============copy===========\n";
    copy.BST_Copy(bst.BST_GetStartNode());
    copy.BST_Refresh();
    copy.BST_ShowTree();
    
    copy.BST_ClearList();
    copy.BST_RefreshList(copy.BST_GetStartNode());
    cout << "Refresh list finished" << endl;
    copy.BST_ShowList();
    cout << "BST_TopologicalSorting: ";
    copy.BST_TopologicalSorting();
    cout << endl;
    while (true)
    {
        cout << "delete: ";
        cin >> find_data;
        if (find_data == 65535) break;
        copy.BST_Delete(find_data);
        copy.BST_Refresh();
        copy.BST_ShowTree();

    }

    return 0;
}
