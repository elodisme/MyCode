#include <iostream>
using namespace std;

struct node
{
	struct node* pLeft;
	struct node* pRight;
	int key;
	int height;
};
typedef struct node NODE;

typedef NODE* AVL_TREE;

//Height
int Height(AVL_TREE T)
{
	if (T == NULL)
		return -1;
	int a = Height(T->pLeft);
	int b = Height(T->pRight);
	return max(a, b) + 1;
}
//Create_Node
NODE* createNode(int x)
{
	NODE* p = new NODE;
	if (p == NULL)
		return NULL;
	p->key = x;
	p->pLeft = NULL;
	p->pRight = NULL;
	p->height = 0;
	return p;
}

NODE* rightRotate(NODE* y)
{
	NODE* x = y->pLeft;
	NODE* T2 = x->pRight;
	//Thuc hien xoay (perform Rotation)
	x->pRight = y;
	y->pLeft = T2;
	//Cap nhap chieu cao cua cac node (update Height)
	y->height = Height(y);
	x->height = Height(x);
	//return new ROOT
	return x;
}

NODE* leftRotate(NODE* x)
{
	//initialize
	NODE* y = x->pRight;
	NODE* T2 = y->pLeft;
	//perform rotate
	y->pLeft = x;
	x->pRight = T2;
	//update height
	y->height = Height(y);
	x->height = Height(x);
	//return new ROOT
	return y;
}

//BalanceFactor
int getBalanceFactor(NODE* p)
{
	if (p == NULL)
		return 0;
	return Height(p->pLeft) - Height(p->pRight);
}

//Insertion
int Insert(AVL_TREE& T, int key)
{
	if (T == NULL)
	{
		T = createNode(key);
		return 1;
	}
	if (key > T->key)
		Insert(T->pRight, key);
	if (key < T->key)
		Insert(T->pLeft, key);
	if (key == T->key)
		return 0;
	//Cap nhap chieu cao cho node
	T->height = Height(T);
	//Get balance factor to check whether balance this node
	int balance = getBalanceFactor(T);
	//4 cases:
	// 
	//L - L case
	if (balance > 1 && key < T->pLeft->key)
		T = rightRotate(T);
	//L - R case
	if (balance > 1 && key > T->pLeft->key) {
		T->pLeft = leftRotate(T->pLeft);
		T = rightRotate(T);
	}
	//R - R case
	if (balance < -1 && key > T->pRight->key)
		T = leftRotate(T);
	//R - L case
	if (balance < 1 && key < T->pRight->key) {
		T->pRight = rightRotate(T->pRight);
		T = leftRotate(T);
	}
	return 1;
}
//Nhap
void Nhap(AVL_TREE& T, int& n)
{
	cout << "Nhap so luong node: ";
	cin >> n;
	int x;
	T = NULL;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		Insert(T, x);
	}
}

//Xuat LNR
void xuatLNR(AVL_TREE T)
{
	if (T == NULL)
		return;
	xuatLNR(T->pLeft);
	cout << T->key << "(" << T->height << ")" << " ";
	xuatLNR(T->pRight);
}

int main()
{
	AVL_TREE T;
	int n;
	Nhap(T, n);
	xuatLNR(T);
	return 0;
}


