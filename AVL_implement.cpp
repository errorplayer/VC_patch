#include<iostream>
#include ".\utility.h"

using namespace std;

struct AVL_node {
  int v, height;
  AVL_node *lchild, *rchild;
};

AVL_node* newNode(int v){
  AVL_node* node = new AVL_node;
	node->v= v;
	node->height = 1;
	node->lchild = node ->rchild = NULL;
	return node;
}

int getHeight(AVL_node * root){
  if (root == NULL)  return 0;
  return root->height;
}

int getBalanceFactor(AVL_node* root){
  return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(AVL_node * root){
  root->height = max (getHeight(root->lchild),getHeight(root->rchild)) + 1;
}

void search(AVL_node* root ,int x ){
  if (root ==NULL)
  {
    cout<<"search failed!"<<endl;
    return ;
  }
  if (x== root->v)
  {
    cout<<"make it!"<<endl;
  }else if (x < root->v)
  {
    search(root->lchild,x);
  }else{
    search(root->rchild,x);
  }
}

void LeftRotation(AVL_node * root){
  AVL_node* temp = root->rchild;
  root->rchild = temp->lchild;
  temp->lchild = root;
  updateHeight(root);
  updateHeight(temp);
  root = temp;
}

void RightRotation(AVL_node* root){
  AVL_node* temp = root->lchild;
  root->lchild = temp->rchild;
  temp->rchild = root;
  updateHeight(root);
  updateHeight(temp);
  root = temp;
}

void insert(AVL_node* &root,int v){
  if(root == NULL)
  {
    root = newNode(v);
    return ;
  }

  if (v < root->v)
  {
    insert(root->lchild,v);
    updateHeight(root);
    if (getBalanceFactor(root) == 2)
    {
      if (getBalanceFactor(root->lchild) == 1)
      {
          RightRotation(root);
      }else if (getBalanceFactor(root->lchild)==-1)
      {
          LeftRotation(root->lchild);
          RightRotation(root);
      }
      
    }

  }else{
    insert(root->rchild,v);
    updateHeight(root);
    if (getBalanceFactor(root)== -2 )
    {
      if (getBalanceFactor(root->rchild)==-1)
      {
        LeftRotation(root);
      }else if (getBalanceFactor(root->rchild)==1)
      {
        RightRotation(root->rchild);
        LeftRotation(root);
      }
    }
  }
}

AVL_node* CreateAVLtree(int data[],int n){
  AVL_node * root = NULL;
  for (int i = 0;i!= n;i++)
  {
    insert(root,data[i]);
  }
  return root;
}

void preAVL_tree(AVL_node *root,int level){
  //queue<AVL_node*> a;
   if (root == NULL)
   {
	   return;
   }
   cout<<root->v<<" ";//<<level<<endl;
   preAVL_tree(root->lchild,root->lchild->height);
   preAVL_tree(root->rchild,root->rchild->height);
   
}
void main()
{
  cout<<"compile successfully!"<<endl;

  int data[8] = {2,1,4,10,142,12,42,5};
  for (int i=0;i!=8;i++)
  {
	  cout<<data[i]<<" ";

  }
  cout<<endl;
  AVL_node * root = CreateAVLtree(data,8);
  preAVL_tree(root,1);
}
     