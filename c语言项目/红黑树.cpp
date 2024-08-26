#include <bits/stdc++.h>
using namespace std;
const static bool RED = 0;
const static bool BLACK = 1;									//0�����1����� 
struct Node 													//�ڵ�ṹ�嶨�� 
{
	int val;
	bool color;             
	Node *left, *right, *p; 
	Node(const int &v, const bool &c = RED, Node *l = nullptr, Node *r = nullptr, Node *_p = nullptr): val(v), color(c),
		left(l), right(r), p(_p) {}
};

struct RBTree 													//��������� 
{
	Node *root;             
	Node *nil;              
	RBTree() 
	{
		nil = new Node(-1, BLACK, nil, nil, nil);
		root = nil;
	}
	void left_rotate(Node *x) 									//�������� 
	{ 
		Node *y = x->right;
		x->right = y->left;
		if (y->left != nil) {
			y->left->p = x;
		}
		y->p = x->p;
		if (x->p == nil)
			root = y;
		else if (x->p->left == x)
			x->p->left = y;
		else
			x->p->right = y;
		x->p = y;
		y->left = x;
	}
	void right_rotate(Node *x) 									//�������� 
	{ 
		Node *y = x->left;
		x->left = y->right;
		if (y->right != nil)
			y->right->p = x;
		y->p = x->p;
		if (x->p == nil)
			root = y;
		else if (x->p->left == x)
			x->p->left = y;
		else
			x->p->right = y;
		x->p = y;
		y->right = x;
	}
	//���뺯�� 
	Node *insert_bst(Node *&p, Node *&r, const int &v) {		//��ʼ���� 
		if (r == nil) {     
			r = new Node(v, RED, nil, nil, p);
			if ( p == nil )
				root = r;
			if (v > p->val)
				p->right = r;
			else
				p->left = r;
		} else {            
			if (v < r->val)
				return insert_bst(r, r->left, v);
			else
				return insert_bst(r, r->right, v);
		}
		return r;
	}
	void insert(const int &v) {									//�����任 
		Node *z = insert_bst(nil, root, v);
		while (z->p->color == RED) {
			if (z->p->p->left == z->p) {
				if (z->p->p->right->color == RED) {             
					z->p->color = BLACK;
					z->p->p->color = RED;
					z->p->p->right->color = BLACK;
					z = z->p->p;
				} else {
					if (z->p->right == z) {                     
						z = z->p;
						left_rotate(z);
					}                                           
					z->p->color = BLACK;
					z->p->p->color = RED;
					right_rotate(z->p->p);
				}
			} else {
				if (z->p->p->left->color == RED) {              
					z->p->color = BLACK;
					z->p->p->color = RED;
					z->p->p->left->color = BLACK;
					z = z->p->p;
				} else {
					if (z->p->left == z) {                      
						z = z->p;
						right_rotate(z);
					}
					z->p->color = BLACK;                        
					z->p->p->color = RED;
					left_rotate(z->p->p);

				}
			}
		}
		root->color = BLACK;                                   
	}
	void in_order(Node *r) {								//����������� 
		if (r == nil || r == nullptr)
			return ;
		in_order(r->left);
		cout << r->val << " color=";
		if(r->color==0)cout<<"RED"<<endl;
		else cout<<"BLACK"<<endl;
		in_order(r->right);
	}
	void in_order() {
		cout << "�������Ϊ:" << endl;
		in_order(root);
	}
	void pre_order(Node *r) {								//ǰ��������� 
		if (r == nil || r == nullptr)
			return ;
		cout << r->val << " color=";
		if(r->color==0)cout<<"RED"<<endl;
		else cout<<"BLACK"<<endl;
		pre_order(r->left);
		pre_order(r->right);
	}
	void pre_order() {
		cout << "ǰ�����Ϊ:" << endl;
		pre_order(root);
	}
};

int main() 
{
	int v,n;
	RBTree T;
	printf("������Ҫ�����������ݸ���:");
	cin>>n;
	cout<<"����������Ҫ���������:" ;
	for (int i=0;i<n;i++) 
	{
		cin >> v;
		T.insert(v);
	}
	T.in_order();
	T.pre_order();
	return 0;
}
