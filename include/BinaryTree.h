#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct BinaryNode
{
    int data;
    int layer;
    int location_x;
    BinaryNode* parent;
    BinaryNode* child_l;
    BinaryNode* child_r;

};

struct ListNode
{
    int indegree;
    int outdegree;
    int data;
    ListNode* next;
    ListNode* previous;
};

inline void BinaryNodeSet(BinaryNode* node, int _data, int _layer, int _location_x, BinaryNode* _parent, BinaryNode* _child_l, BinaryNode* _child_r)
{
    node->data = _data;
    node->layer = _layer;
    node->location_x = _location_x;
    node->parent  = _parent;
    node->child_l = _child_l;
    node->child_r = _child_r;
}

class BinaryTree
{
private:
    BinaryNode* start_node;
    int bst_height;
    vector<BinaryNode*>leaf;
    vector<ListNode*>bst_list;

public:
    BinaryTree()
    {
        start_node = new BinaryNode;
        BinaryNodeSet(start_node, 0, 1, 1, NULL, NULL, NULL);
        BST_Refresh();
    }
    BinaryTree(int *a, int number)
    {
        //start_node 初始化
        start_node = new BinaryNode;
        BinaryNodeSet(start_node, *a, 1, 1, NULL, NULL, NULL);
        //create BST 确定指针关系
        BinaryNode* temp; 
        for (int i=1; i<number; i++)
        {
            temp = BST_Insert(*(a+i));
        }
        BST_Refresh();
    }

    //
    ~BinaryTree()
    {
        queue<BinaryNode*>rm;
        rm.push(start_node);
        cout << "~BinaryTree()" << endl;
        while (rm.empty() != true)//队列非空
        {
            if (rm.front()->child_l != NULL)
            {
                rm.push(rm.front()->child_l);
            }
            if (rm.front()->child_r != NULL)
            {
                rm.push(rm.front()->child_r);
            }        
            cout << "delete: " << rm.front() << endl;
            delete rm.front();
            rm.pop();
        }
        BST_ClearList();
    }



    inline void BST_InOrder(BinaryNode* node)
    {
        if (node->child_l != NULL)
        {
            BST_InOrder(node->child_l);
        }
        cout << "data: "<< node->data << "  " << "layer: " << node->layer << "  " << "location_x: " << node->location_x << "  " << endl;
        if (node->child_r != NULL)
        {
            BST_InOrder(node->child_r);
        }
        
    }

    inline void BST_LeafNodePrint()
    {
        cout <<"================"<<endl;
        cout << "LeafNode: ";
        for (vector<BinaryNode*>::iterator it=leaf.begin(); it<leaf.end(); it++)
        {
            cout << (*it)->data << " ";
        }
        cout << endl;
        cout <<"================"<<endl;
    }

    inline void BST_Copy(BinaryNode* source_node)
    {
        queue<BinaryNode*>node;
        BinaryNodeSet(start_node,source_node->data,1,1,NULL,NULL,NULL);
        if (source_node->child_l != NULL) node.push(source_node->child_l);
        if (source_node->child_r != NULL) node.push(source_node->child_r);
        while (node.empty() != true)
        {
            BST_Insert(node.front()->data);
            if (node.front()->child_l != NULL) node.push(node.front()->child_l);
            if (node.front()->child_r != NULL) node.push(node.front()->child_r);
            node.pop();
        }
    }


    inline void BST_ClearList()
    {
        int show_number=0;
        ListNode* temp;
        for (vector<ListNode*>::iterator it=bst_list.begin(); it<bst_list.end(); it++)
        {
            temp = (*it)->previous;
            while (temp != NULL)
            {
                ListNode* delete_temp = temp;
                temp = temp->previous;
                delete delete_temp;
                show_number++;
                cout << show_number  << " ";
                cout << "delete: " << delete_temp << endl;
            }
            temp = *it;
            while (temp != NULL)
            {
                ListNode* delete_temp = temp;
                temp = temp->next;
                delete delete_temp;
                show_number++;
                cout << show_number  << " ";
                cout << "delete: " << delete_temp << endl;
            }
        }
        bst_list.clear();
    }

    inline void BST_ShowList()
    {
        ListNode* temp;
        cout << endl << "==========LIST===========" << endl;
        for (vector<ListNode*>::iterator it=bst_list.begin(); it<bst_list.end(); it++)
        {
            temp = *it;
            if (temp->previous == NULL) cout << "NULL<== ";
            else cout << temp->previous->data << "  <== ";
            while (temp != NULL)
            {
                cout << temp->data << " --> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
        cout << "==========LIST===========" << endl;
    }

    inline int  BST_GetHeight(){ return bst_height; }
    inline BinaryNode* BST_GetStartNode(){ return start_node; }

    void BST_RefreshList(BinaryNode* node);//更新邻接表
    void BST_TopologicalSorting();
    bool BST_Delete(int delete_data);
    void BST_ShowTree();
    void BST_Refresh();//refresh layer height location_x leaf
    BinaryNode* BST_Insert(int insert_data);
    BinaryNode* BST_Find(int find_data);
};

#endif
