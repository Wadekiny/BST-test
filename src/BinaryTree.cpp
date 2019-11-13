#include "BinaryTree.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

void BinaryTree::BST_Refresh()//refresh layer height location_x leaf
{
    queue<BinaryNode*>refresh;
    refresh.push(start_node);
    start_node->layer = 1;
    start_node->location_x = 1;
    int max_layer=0;
    leaf.clear();

    while (refresh.empty() != true)//队列非空
    {
        //height
        if (refresh.front()->layer > max_layer) max_layer = refresh.front()->layer;
        //leaf
        if (refresh.front()->child_l == NULL && refresh.front()->child_r == NULL)
        {
            leaf.push_back(refresh.front());
        }
        //location_x and layer
        if (refresh.front()->child_l != NULL)
        {
            refresh.push(refresh.front()->child_l);
            refresh.front()->child_l->layer = refresh.front()->layer+1;  //layer
            refresh.front()->child_l->location_x = refresh.front()->location_x*2-1;
        }
        if (refresh.front()->child_r != NULL)
        {
            refresh.push(refresh.front()->child_r);
            refresh.front()->child_r->layer = refresh.front()->layer+1;
            refresh.front()->child_r->location_x = refresh.front()->location_x*2;
        }        
        refresh.pop();
    }
    bst_height = max_layer-1;
}


void BinaryTree::BST_ShowTree()
{
    int cursor_layer = 1;
    int cursor_x = 1;
    int left_space = 0;
    int middle_space = 0;
    queue<BinaryNode*>show;
    show.push(start_node);

    left_space = pow(2,bst_height+1-cursor_layer+1);
    cout << endl;
    for (int i=0; i<left_space; i++) cout << " ";
    cout << show.front()->data;
    cursor_layer = 1;

    while (show.empty() != true)//非空
    {
        if (cursor_layer <= show.front()->layer)
        {
            cursor_layer = show.front()->layer+1;
            cursor_x = 1;
            left_space = pow(2,bst_height+1-cursor_layer+1);
            middle_space = 2*left_space-2;
            cout << endl << endl;
            for (int i=0; i<left_space; i++) cout << " ";
        }
        if (show.front()->child_l != NULL)
        {
            show.push(show.front()->child_l);
            if (show.front()->child_l->location_x > cursor_x)  
            {
                for (int i=0; i<show.front()->child_l->location_x - cursor_x; i++)
                {
                    cout << "  ";
                    for (int i=0; i<middle_space; i++) cout << " ";
                }
                cursor_x = show.front()->child_l->location_x;
            }
            if (show.front()->child_l->data < 10)
                cout << " ";
            cout << show.front()->child_l->data;
            for (int i=0; i<middle_space; i++) cout << " ";
            cursor_x ++;
        }
        if (show.front()->child_r != NULL)
        {
            show.push(show.front()->child_r);
            if (show.front()->child_r->location_x > cursor_x)  
            {
                for (int i=0; i<show.front()->child_r->location_x - cursor_x; i++)
                {
                    cout << "  ";
                    for (int i=0; i<middle_space; i++) cout << " ";
                }
                cursor_x = show.front()->child_r->location_x;
            }
            if (show.front()->child_r->data < 10)
                cout << " ";
            cout << show.front()->child_r->data;
            for (int i=0; i<middle_space; i++) cout << " ";
            cursor_x ++;
        }
        show.pop();
    }
    cout << endl;

}

BinaryNode* BinaryTree::BST_Insert(int insert_data)
{
    //新建一个节点
    BinaryNode* insert_node = new BinaryNode;
    BinaryNodeSet(insert_node, insert_data, 0, 0, NULL, NULL, NULL);

    BinaryNode* temp_node = start_node;

    while (true)
    {
        if (insert_data < temp_node->data)//判断比temp_node的值大或小
        {
            if (temp_node->child_l == NULL) //左子节点 空
            {
                temp_node->child_l = insert_node;//左子节点变成新插入的节点
                insert_node->parent = temp_node;
                insert_node->layer = temp_node->layer+1;
                break;                           //插入结束，break
            }
            else
            {
                temp_node = temp_node->child_l;  //左子节点 非空,更新为temp_node,while下继续向下判断。
            }
        }
        else
        {
            if (temp_node->child_r == NULL)//没有右子节点
            {
                temp_node->child_r = insert_node;
                insert_node->parent = temp_node;
                insert_node->layer = temp_node->layer+1;
                break;
            }
            else
            {
                temp_node = temp_node->child_r; 
            }
        }
    }
   // cout << "====================================\n";
   // cout << "InsertNode Data:  " << insert_node->data << endl;
   // cout << "InsertNode layer: " << insert_node->layer << endl;
   // if (insert_node->parent->child_l == insert_node)
   //     cout << "InsertNode is LEFT   " << endl;
   // else
   //     cout << "InsertNode is RIGHT  " << endl;
   // cout << "InsertNode parent_data:  " << insert_node->parent->data << endl;
   // cout << "====================================\n";
    return insert_node;
}

BinaryNode* BinaryTree::BST_Find(int find_data)
{
    BinaryNode* temp = start_node;
    while (true)
    {
        if (temp->data < find_data)
        {
            if (temp->child_r == NULL) 
            {
                 cout << "not exists" << endl;
                 return NULL;
            }
            else
            {
                temp = temp->child_r;
            }
        }
        else if (temp->data > find_data)
        {
            if (temp->child_l == NULL) 
            {
                 cout << "not exists" << endl;
                 return NULL;
            }
            else
            {
                temp = temp->child_l;
            }
        }
        else
        {
            cout << "Finished: " << temp << endl;
            cout << "layer: " << temp->layer << "  location_x: " << temp->location_x << endl << endl; 
            return temp;
        }
    }
}

bool BinaryTree::BST_Delete(int delete_data)
{
    BinaryNode* target_node;
    target_node = BST_Find(delete_data);
    if (target_node != NULL)//exists
    {
        if (target_node == start_node)//起始节点
        {
             
            if (target_node->child_l == NULL && target_node->child_r != NULL)//左节点空
            {
               start_node = target_node->child_r;
               start_node->parent = NULL;
               delete target_node;
               cout << "delete: " << target_node << endl;
               return true;
            }
            else if (target_node->child_r == NULL && target_node->child_l != NULL)//右节点空
            {
               start_node = target_node->child_l;
               start_node->parent = NULL;
               delete target_node;
               cout << "delete: " << target_node << endl;
               return true;
                
            }
            else if (target_node->child_r == NULL && target_node->child_l == NULL)//无子节点
            {
                cout << "last node, failed\n";
                return false;
            }
            else//两个子节点
            {
                start_node = target_node->child_l;
                BinaryNode* temp_node = start_node;
                while (temp_node->child_r != NULL)
                {
                    temp_node = temp_node->child_r;
                }
                temp_node->child_r = target_node->child_r;
                target_node->child_r->parent = temp_node;
                delete target_node;
                cout << "delete: " << target_node << endl;

                return false;
            }

        }
        else if (target_node->child_l == NULL && target_node->child_r != NULL)//左节点空,存在右子节点
        {
            if (target_node->parent->child_l == target_node)
            {
                target_node->parent->child_l = target_node->child_r;
                target_node->child_r->parent = target_node->parent;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
            }
            if (target_node->parent->child_r == target_node)
            {
                target_node->parent->child_r = target_node->child_r;
                target_node->child_r->parent = target_node->parent;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
            }
            return false;
        }
        else if (target_node->child_r == NULL && target_node->child_l != NULL)//右节点空
        {
            if (target_node->parent->child_l == target_node)
            {
                target_node->parent->child_l = target_node->child_l;
                target_node->child_l->parent = target_node->parent;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
            }
            if (target_node->parent->child_r == target_node)
            {
                target_node->parent->child_r = target_node->child_l;
                target_node->child_l->parent = target_node->parent;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
            }
            return false;
        }
        else if (target_node->child_r == NULL && target_node->child_l == NULL)//无子节点,叶子节点
        {
            if (target_node->parent->child_l == target_node)//是它父节点的左子节点
            {
                target_node->parent->child_l = NULL;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
            }
            else//是它父节点的右子节点
            {
                target_node->parent->child_r = NULL;
                delete target_node;
                cout << "delete: " << target_node << endl;
                return true;
                
            }
        }
        else//有两个子节点
        {
            BinaryNode* temp_node = target_node->child_l;
            while (temp_node->child_r != NULL)
            {
                temp_node = temp_node->child_r;
            }
            
            if (target_node->parent->child_l == target_node)
            {
                target_node->parent->child_l = target_node->child_l;
                target_node->child_l->parent = target_node->parent;
            }
            else
            {
                target_node->parent->child_r = target_node->child_l;
                target_node->child_l->parent = target_node->parent;
            }

            temp_node->child_r = target_node->child_r;
            target_node->child_r->parent = temp_node;
            delete target_node;
            cout << "delete: " << target_node << endl;
            return true;
        }

    }

    return true;
}


void BinaryTree::BST_TopologicalSorting()
{
    ListNode* temp;
    queue<ListNode*>topo;
    //refresh indegre
    for (vector<ListNode*>::iterator it=bst_list.begin(); it<bst_list.end(); it++)
    {
        temp = *it;
        while (temp != NULL)
        {
            if (temp->previous != NULL)
            {
                (*it)->indegree++;
            }
            temp = temp->previous;
        }
        temp = *it;
        while(temp != NULL)
        {
            if (temp->next != NULL)
            {
                (*it)->outdegree++;
            }
            temp = temp->next;
        }
        
    }

    for (vector<ListNode*>::iterator it=bst_list.begin(); it<bst_list.end(); it++)
    {
        if((*it)->indegree == 0) topo.push(*it);//入度为0 加入队列
    }
    while (topo.empty() == false)
    {
        temp = topo.front()->next;
        while (temp != NULL)
        {
            for (vector<ListNode*>::iterator it=bst_list.begin(); it<bst_list.end(); it++)//在vector中找对应的节点
            {
                if((*it)->data == temp->data)
                {
                    (*it)->indegree--;//入度减1
                    if ((*it)->indegree == 0)
                    {
                        topo.push(*it);
                    }
                    break;
                }
            }
            temp = temp->next;

        }
        cout << topo.front()->data << " ";
        topo.pop();
    }
    cout << endl;
}


void BinaryTree::BST_RefreshList(BinaryNode* node)
{
    ListNode* temp_list_node = NULL;
    ListNode* new_list_node = NULL;
    if (node->child_l != NULL)
    {
        BST_RefreshList(node->child_l);
    }
    temp_list_node = new ListNode;
    temp_list_node->data = node->data;
    temp_list_node->next = NULL;
    temp_list_node->previous = NULL;
    temp_list_node->indegree = 0;
    temp_list_node->outdegree = 0;
    bst_list.push_back(temp_list_node);

    if (node->parent != NULL)
    {
        new_list_node = new ListNode;
        temp_list_node->previous = new_list_node;
        new_list_node->data = node->parent->data;
        new_list_node->next = temp_list_node;
        new_list_node->previous = NULL;
    }

    if (node->child_l != NULL)//left child is exists
    {
        new_list_node = new ListNode;
        temp_list_node->next = new_list_node;
        new_list_node->data = node->child_l->data;
        new_list_node->next = NULL;
        new_list_node->previous = NULL;
        temp_list_node = temp_list_node->next;
    }
    if (node->child_r != NULL)//left child is exists
    {
        new_list_node = new ListNode;
        temp_list_node->next = new_list_node;
        new_list_node->data = node->child_r->data;
        new_list_node->next = NULL;
        new_list_node->previous = NULL;
        temp_list_node = temp_list_node->next;
    }
    if (node->child_r != NULL)
    {
        BST_RefreshList(node->child_r);
    }
}
