// Assgn3_DS.cpp : Defines the entry point for the console application.


#include<iostream>
#include<stdlib.h>  // For exit function
#include<queue>     // For level order traversal for printing
#include<stack>     // Used in deletion 
#include <sstream> 
#include <fstream>  // For File handling
#include <time.h>

using namespace std;

class TreapNode // NODE Structure of Treap
{
	private:
			int data;

			int priority;

			TreapNode *left;

			TreapNode *right;

			friend class TreapTree;

};

class TreapTree // Friend Class specifying Root of tree and various Functions
{
	private:
			TreapNode *root;

	public:
			TreapTree();

			TreapTree(const TreapTree &T);

			TreapTree &operator=(const TreapTree &T);

			TreapNode* newnode(int k);

			void Treap_Insert(int k);

			TreapNode* rightRotate(TreapNode *root);

			TreapNode* leftRotate(TreapNode *root);

			TreapNode* Recursive_insert(TreapNode* root,int k);

			void Treap_Delete(int k);

			TreapNode* Recursive_delete(TreapNode* root,int k);

			bool Treap_Search(int k);

			TreapNode* Recursive_search(TreapNode* root,int k);

			void Treap_Print();

			~TreapTree();

			void DestroyRecursive(TreapNode *node);

};

TreapTree :: TreapTree() // Constructor
{
	this->root=NULL;
}

TreapTree :: TreapTree(const TreapTree &T)
{
	this->root=T.root;
}


void TreapTree :: DestroyRecursive(TreapNode *node)// Utility function for Recursively destroying each node of Treap Tree
{
    if (node)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

TreapTree::~TreapTree() // Destructor for reclaiming memory
{
    DestroyRecursive(root);
}

TreapNode* TreapTree:: newnode(int k) // New node Creation Function
{
	TreapNode *temp=new TreapNode();

	temp->data=k;

	temp->left=temp->right=NULL;

	temp->priority=rand()%10000;

	return temp;
}

TreapNode* TreapTree :: Recursive_search(TreapNode *root,int k)
{
	if(!root) // Returns NULL If element NOT Found
		return root;

	if(root->data==k) // Return the node where element present
		return root;

	else if(k<root->data) // Search LST
		return Recursive_search(root->left,k);

	else // Search RST
		return Recursive_search(root->right,k);

}

bool TreapTree :: Treap_Search(int k)
{

	TreapNode *res=new TreapNode();

	res=Recursive_search(this->root,k);

	if(res)
		return true;

	else
		return false;
}

TreapNode* TreapTree :: rightRotate(TreapNode *root)
{
	TreapNode *x=root->left;
	TreapNode *subtree=x->right;

	// Perform rotation
	x->right=root;
	root->left=subtree;

	// Return new root
	return x;
}

TreapNode*  TreapTree :: leftRotate(TreapNode *root)
{
    TreapNode *y = root->right;
	TreapNode *subtree = y->left;
 
    // Perform rotation
    y->left = root;
    root->right = subtree;
 
    // Return new root
    return y;
}

TreapNode* TreapTree :: Recursive_insert(TreapNode* root,int k)
{

	if(!root) // Position Found! Create new node
		return newnode(k);

	if(k<=root->data) // Recursively find the position to insert in Left Subtree
	{
		root->left=Recursive_insert(root->left,k);

		if(root->left->priority>root->priority)
			root=rightRotate(root);
	}

	else // Recursively find the position to insert in Right Subtree
	{
		root->right=Recursive_insert(root->right,k);

		if(root->right->priority>root->priority)
			root=leftRotate(root);
	}

	return root;
}

void TreapTree:: Treap_Insert(int k)
{
		this->root=Recursive_insert(this->root,k);
}

TreapNode* TreapTree :: Recursive_delete(TreapNode *root,int k)
{
	if(root == NULL)
		return root;

	else if(k<root->data)
		root->left=Recursive_delete(root->left,k);

	else if(k>root->data)
		root->right=Recursive_delete(root->right,k);

	else
	{
		// Node with empty Left Child
		if(root->left==NULL)
		{
			TreapNode *temp=root->right;
			delete(root);
			root=temp;

		}

		// Node with empty Right Child
		else if(root->right==NULL)
		{
			TreapNode *temp=root->left;
			delete(root);
			root=temp;
		}

		// Intermediate node with both offsprings
		else
		{
			// Based on priority do the rotation such that Higher priority become Parent

			if(root->left->priority<root->right->priority)
			{
				root=leftRotate(root);
				root->left=Recursive_delete(root->left,k);
			}

			else
			{
				root=rightRotate(root);
				root->right=Recursive_delete(root->right,k);
			}

		}
	}
	return root;
}

void TreapTree:: Treap_Delete(int k)
{
		bool res=Treap_Search(k); // Search for the element

		// If NOT Found
		if(!res)
			cout<<"\n\n  \t\t\tElement to be deleted NOT Present!!!\n\n";


		// If Found
		else
		{
			this->root=Recursive_delete(this->root,k);
			cout<<"\n\n  \t\t\tSuccess in doing Deletion from Treap!!!\n\n";
		}
}

void TreapTree :: Treap_Print()
{

	// Creating/Opening .gv file
	ofstream MyFile("myfile.gv");

	// Write to the file
    MyFile << "digraph G{\n";
	MyFile << "node [shape = record, height = .1];";


	queue <TreapNode *> q; // Queue for level order traversal

        TreapNode *cur;

        q.push(this->root); // Enqueue root
        q.push(NULL);

		
        while(!q.empty())
		{
			cur = q.front();
           
            q.pop();

            if(cur == NULL && q.size()!=0)
			{
                
                q.push(NULL);

                continue;
            }

            if(cur!=NULL)
			{
               
                if (cur->left!=NULL)
				{
					 MyFile << "node" << cur->data << " [label = \"<f0> | <f1> " << cur->data << " | <f2> priority= " << cur->priority << " | <f3>\"];\n"; // Inserting link in gv file if Left Child present

					 MyFile << "node" << cur->left->data << " [label = \"<f0> | <f1> " << cur->left->data << " | <f2> priority=" << cur->left->priority << " | <f3>\"];\n";
    	             MyFile << "\"node" << cur->data << "\":f0 -> \"node" << cur->left->data << "\":f1;\n";

                     q.push(cur->left);// Enqueue Left Child if present
                }

                if (cur->right!=NULL)
				{
					 MyFile << "node" << cur->data << " [label = \"<f0> | <f1> " << cur->data << " | <f2> priority= " << cur->priority << " | <f3>\"];\n"; // Inserting link in gv file if Left Child present

					 MyFile << "node" << cur->right->data << " [label = \"<f0> | <f1> " << cur->right->data << " | <f2> priority=" << cur->right->priority << " | <f3>\"];\n";
    	             MyFile << "\"node" << cur->data << "\":f3 -> \"node" << cur->right->data << "\":f1;\n";

                     q.push(cur->right);// Enqueue Right Child if present
                }
            }
            
            
        }

		cout<<endl;


	MyFile << "}";

	// Close the file
    MyFile.close();
}


int main()
{
	srand(time(NULL));

	TreapTree *t=new TreapTree();

	int choice,num;

	printf("\n\n\n********* Menu Driven Mode *********\n\n\n");

	while(1)
	{
		cout<<"Enter Number corresponding to operation-\n\n1. Insert in Treap\n\n2. Delete from Treap\n\n3. Search in Treap\n\n4. Print-Tree\n\n5. Exit\n\n";

		cout<<"Choice: ";

		cin>>choice;

		switch(choice)
		{
			case 1:
				{
					cout<<"\nEnter number to Insert: ";
					cin>>num;
					t->Treap_Insert(num);
					printf("\n\n  \t\t\tSuccess in doing Insertion in Treap!!!\n\n");
					break;
				}

			case 2:
				{
					cout<<"\nEnter number to Delete: ";
					cin>>num;
					t->Treap_Delete(num);
					break;
				}

			case 3:
				{
					cout<<"\nEnter number to Search: ";
					cin>>num;
					bool res=t->Treap_Search(num);

					if(res)
						printf("\n\n  \t\t\tSuccess in doing Search in Treap!!! Element Found!\n\n");

					else
						printf("\n\n  \t\t\tElement NOT Present in Treap!!!\n\n");

					break;
				}

			case 4:
				t->Treap_Print();
				printf("\n\n  \t\t\tSuccess in Generating DOT File. Check Your Directory!!!\n\n");
				break;

			case 5:
				exit(0);

			default:
				printf("\nInvalid choice\n");

		}
	}


	/*t->Treap_Insert(50);

	t->Treap_Insert(30);

	t->Treap_Insert(20);

	t->Treap_Insert(40);

	t->Treap_Insert(70);

	t->Treap_Insert(60);

	t->Treap_Insert(80);

	bool res=t->Treap_Search(0);

	t->Treap_Delete(70);*/

	return 0;
}

