// TestFileAndParameters.cpp : Defines the entry point for the console application.


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <time.h>

using namespace std;

class Parameters // Class That holds all the Parameters
{
	public:

		int comparisonDuringInsertion; // Total number of comparison while inserting

		int comparisonDuringDeletion; // Total number of comparison while deleting

		int heightOfFinalTree; // Final Height of tree

		int totalRotation; // Total Number of Rotations

		int typeOfTree; // 1->BST 2->AVL 3->TREAP
};

class BST 
{
	public:
			int key;

			BST *left;
			
			BST *right;
};

class AVL
{
    public:
			int key;

			AVL *left;

			AVL *right;

			int height;
};

class TreapNode // NODE Structure of Treap
{
	public:
			int data;

			int priority;

			TreapNode *left;

			TreapNode *right;

			friend class TreapTree;

};

class TreapTree // Friend Class specifying Root of tree and various Functions
{
	public:
			TreapNode *root;

			TreapTree();

			TreapNode* newnode(int k);

			void Treap_Insert(int k, Parameters*);

			TreapNode* rightRotate(TreapNode *root, Parameters*);

			TreapNode* leftRotate(TreapNode *root, Parameters*);

			TreapNode* Recursive_insert(TreapNode* root,int k, Parameters*);

			void Treap_Delete(int k, Parameters*);

			TreapNode* Recursive_delete(TreapNode* root,int k, Parameters*);

			int height(TreapNode *root);

};


void reverseStr(string& str)
{
    int n = str.length();
 
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}



/* ***************************************** ALL BST FUNCTIONS START ******************************************** */

 
// A utility function to create a new BST node
BST* newNode(int item)
{
    BST* temp= new BST();
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}


BST* insert(BST* node, int key,Parameters *p)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
	{
		p->comparisonDuringInsertion++;
		node->left = insert(node->left, key,p);
	}
    else
	{
		p->comparisonDuringInsertion++;
		node->right = insert(node->right, key,p);
	}
 
   
    return node;
}
 
BST* minValueNode(BST* node,Parameters *p)
{
    BST* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
	{
		current = current->left;
		p->comparisonDuringDeletion++;
	}
 
    return current;
}
 

BST* deleteNode(BST* root, int key,Parameters *p)
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (key < root->key)
	{
		p->comparisonDuringDeletion++;
		root->left = deleteNode(root->left, key,p);
	}
 
    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (key > root->key)
	{
		p->comparisonDuringDeletion++;
		root->right = deleteNode(root->right, key,p);
	}
 
    // if key is same as root's key, then This is the node to be deleted
    else 
	{
        // node with only one child or no child
        if (root->left == NULL) 
		{
            BST* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) 
		{
            BST* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest in the right subtree)
        BST* temp = minValueNode(root->right,p);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key,p);
    }

    return root;
}


int height(BST* root)
{
    // Base case: empty tree has a height of 0
    if (root == NULL) 
	{
        return 0;
    }
 
    // recur for the left and right subtree and consider maximum depth
    return 1 + max(height(root->left), height(root->right));
}

Parameters Test_BST_Parameters(const char *filename)
{
	Parameters P;

	P.comparisonDuringInsertion=0;
	P.comparisonDuringDeletion=0;
	P.totalRotation=0;
	P.typeOfTree=1; // BST

	int oprType; // 0->Operation 1->Insert 2->Delete

	int noOfOpr;

	BST *root = NULL;

	int flag=1;

	string myText;

	// Read from the text file
	ifstream MyReadFile(filename);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (MyReadFile, myText)) 
	{
		string mynum;

		if(myText[0]=='O')
			oprType=0;

		else if(myText[0]=='I')
			oprType=1;

		else if(myText[0]=='D')
			oprType=2;

		int len=myText.length();

		int num=0;

		len--;

		while(isdigit(myText[len]))
		{
			mynum+=myText[len];
			len--;
		}

		// Reverse str[begin..end]
		reverseStr(mynum);

		//cout<<mynum<<" ";

		stringstream tonum(mynum);
 

		tonum >> num;

		//cout <<num<<" ";

		if(oprType==1)
			root = insert(root, num, &P);
		
		if(oprType==0)
			noOfOpr=num;

		if(oprType==2)
			root = deleteNode(root, num,&P);
		
 
	}

	P.heightOfFinalTree=height(root);

	// Close the file
	MyReadFile.close(); 


	return P;
}



/* ********************************* ALL BST FUNCTIONS COMPLETETED ***************************************** */



/* ********************************* ALL AVL FUNCTIONS START *********************************************** */

int max(int a, int b);
 
// A utility function to get the height of the tree
int height(AVL *N)
{
    if (N == NULL)
        return 0;

    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 

AVL* newNodeAVL(int key)
{
    AVL* node = new AVL();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return(node);
}
 
AVL *rightRotate(AVL *y,Parameters *p)
{
    AVL *x = y->left;
    AVL *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

	p->totalRotation++;
 
    // Return new root
    return x;
}
 
AVL *leftRotate(AVL *x, Parameters *p)
{
    AVL *y = x->right;
    AVL *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

	p->totalRotation++;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(AVL *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
AVL* insert_AVL(AVL* node, int key, Parameters *p)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNodeAVL(key));
 
    if (key < node->key)
	{
		p->comparisonDuringInsertion++;
		node->left = insert_AVL(node->left, key,p);
	}

    else if (key > node->key)
	{
		p->comparisonDuringInsertion++;
		node->right = insert_AVL(node->right, key,p);
	}
    else // Equal keys are not allowed in BST
        return node;
 
    // 2. Update height of this ancestor node 
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node,p);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node,p);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left,p);
        return rightRotate(node,p);// NOTE: Number of Total Rotation increased TWICE
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right,p);
        return leftRotate(node,p);// NOTE: Number of Total Rotation increased TWICE
    }
 
    
    return node;
}

AVL* minValueNode(AVL* node, Parameters *p)
{
    AVL* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
	{
		p->comparisonDuringDeletion++;
		current = current->left;
	}
 
    return current;
}


AVL* deleteNode_AVL(AVL* root, int key,Parameters *p)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the root's key, then it isi n left subtree
    if ( key < root->key )
	{
		p->comparisonDuringDeletion++;
		root->left = deleteNode_AVL(root->left, key,p);
	}
 
    // If the key to be deleted is greater than the root's key, then it is in right subtree
    else if( key > root->key )
	{
		p->comparisonDuringDeletion++;
		root->right = deleteNode_AVL(root->right, key,p);
	}
 
    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            AVL *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            AVL* temp = minValueNode(root->right,p);
 
            // Copy the inorder successor's data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = deleteNode_AVL(root->right,
                                     temp->key,p);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE 
    int balance = getBalance(root);
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root,p);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left,p);
        return rightRotate(root,p);// NOTE: Number of Total Rotation increased TWICE
    }
 
    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root,p);
 
    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right,p); 
        return leftRotate(root,p); // NOTE: Number of Total Rotation increased TWICE
    }
 
    return root;
}



Parameters Test_AVL_Parameters(const char *filename)
{
	Parameters P;

	P.comparisonDuringInsertion=0;
	P.comparisonDuringDeletion=0;
	P.totalRotation=0;
	P.typeOfTree=2; // AVL

	int oprType; // 0->Operation 1->Insert 2->Delete

	int noOfOpr;

	AVL *root = NULL;

	int flag=1;

	string myText;

	// Read from the text file
	ifstream MyReadFile(filename);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (MyReadFile, myText)) 
	{
		string mynum;

		if(myText[0]=='O')
			oprType=0;

		else if(myText[0]=='I')
			oprType=1;

		else if(myText[0]=='D')
			oprType=2;

		int len=myText.length();

		int num=0;

		len--;

		while(isdigit(myText[len]))
		{
			mynum+=myText[len];
			len--;
		}

		// Reverse str[begin..end]
		reverseStr(mynum);

		//cout<<mynum<<" ";

		stringstream tonum(mynum);
 

		tonum >> num;

		//cout <<num<<" ";

		if(oprType==1)
			root = insert_AVL(root, num, &P);
		
		if(oprType==0)
			noOfOpr=num;

		if(oprType==2)
			root = deleteNode_AVL(root, num,&P);
		
 
	}

	P.heightOfFinalTree=height(root);

	// Close the file
	MyReadFile.close(); 

	return P;
}


/* ********************************* ALL AVL FUNCTIONS COMPLETED *********************************************** */





/* ********************************* ALL TREAP FUNCTIONS START ************************************************* */



TreapTree :: TreapTree() // Constructor
{
	this->root=NULL;
}


TreapNode* TreapTree:: newnode(int k) // New node Creation Function
{
	TreapNode *temp=new TreapNode();

	temp->data=k;

	temp->left=temp->right=NULL;

	temp->priority=rand()%10000;

	return temp;
}


int TreapTree :: height(TreapNode *root)
{
    // Base case: empty tree has a height of 0
    if (root == NULL) 
	{
        return 0;
    }
 
    // recur for the left and right subtree and consider maximum depth
    return 1 + max(height(root->left), height(root->right));
}


TreapNode* TreapTree :: rightRotate(TreapNode *root,Parameters *p)
{
	TreapNode *x=root->left;
	TreapNode *subtree=x->right;

	// Perform rotation
	x->right=root;
	root->left=subtree;

	p->totalRotation++;

	// Return new root
	return x;
}

TreapNode*  TreapTree :: leftRotate(TreapNode *root,Parameters *p)
{
    TreapNode *y = root->right;
	TreapNode *subtree = y->left;
 
    // Perform rotation
    y->left = root;
    root->right = subtree;

	p->totalRotation++;
 
    // Return new root
    return y;
}

TreapNode* TreapTree :: Recursive_insert(TreapNode* root,int k,Parameters *p)
{

	if(!root) // Position Found! Create new node
		return newnode(k);

	if(k<=root->data) // Recursively find the position to insert in Left Subtree
	{
		p->comparisonDuringInsertion++;

		root->left=Recursive_insert(root->left,k,p);

		if(root->left->priority>root->priority)
			root=rightRotate(root,p);
	}

	else // Recursively find the position to insert in Right Subtree
	{
		p->comparisonDuringInsertion++;

		root->right=Recursive_insert(root->right,k,p);

		if(root->right->priority>root->priority)
			root=leftRotate(root,p);
	}

	return root;
}

void TreapTree:: Treap_Insert(int k,Parameters *p)
{
		this->root=Recursive_insert(this->root,k,p);
}

TreapNode* TreapTree :: Recursive_delete(TreapNode *root,int k,Parameters *p)
{
	if(root == NULL)
		return root;

	else if(k<root->data)
	{
		p->comparisonDuringDeletion++;
		root->left=Recursive_delete(root->left,k,p);
	}

	else if(k>root->data)
	{
		p->comparisonDuringDeletion++;
		root->right=Recursive_delete(root->right,k,p);
	}

	else
	{
		p->comparisonDuringDeletion++;

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
				root=leftRotate(root,p);
				root->left=Recursive_delete(root->left,k,p);
			}

			else
			{
				root=rightRotate(root,p);
				root->right=Recursive_delete(root->right,k,p);
			}

		}
	}
	return root;
}


void TreapTree:: Treap_Delete(int k, Parameters *p)
{	
			this->root=Recursive_delete(this->root,k,p);
}


Parameters Test_TREAP_Parameters(const char *filename)
{
	Parameters P;

	P.comparisonDuringInsertion=0;
	P.comparisonDuringDeletion=0;
	P.totalRotation=0;
	P.typeOfTree=3; // TREAP

	int oprType; // 0->Operation 1->Insert 2->Delete

	int noOfOpr;

	TreapTree *t=new TreapTree();


	int flag=1;

	string myText;

	// Read from the text file
	ifstream MyReadFile(filename);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (MyReadFile, myText)) 
	{
		string mynum;

		if(myText[0]=='O')
			oprType=0;

		else if(myText[0]=='I')
			oprType=1;

		else if(myText[0]=='D')
			oprType=2;

		int len=myText.length();

		int num=0;

		len--;

		while(isdigit(myText[len]))
		{
			mynum+=myText[len];
			len--;
		}

		// Reverse str[begin..end]
		reverseStr(mynum);

		//cout<<mynum<<" ";

		stringstream tonum(mynum);
 

		tonum >> num;

		//cout <<num<<" ";

		if(oprType==1)
			t->Treap_Insert(num,&P);
		
		if(oprType==0)
			noOfOpr=num;

		if(oprType==2)
			t->Treap_Delete(num,&P);
		
 
	}

	P.heightOfFinalTree=t->height(t->root);

	// Close the file
	MyReadFile.close(); 

	return P;
}


/* ********************************* ALL TREAP FUNCTIONS COMPLETED ************************************************* */




/* ********************************* File Generating Module START ************************************************* */


template <typename T>
void remove_at(std::vector<T>& v, typename std::vector<T>::size_type n)
{
    std::swap(v[n], v.back());
    v.pop_back();
}

void GenerateFile(const char *filename,int n)
{
	ofstream MyFile(filename);

	int noOfOpr=n;

	int leastInsert=20;

	vector <int> del;

	MyFile << "Operation:"<< noOfOpr<< "\n";

	while(leastInsert--) // To maintain 70-30 ratio of insert-delete
	{
			int num=rand()%100;
			//insertNode(num);
			MyFile << "Insert:"<< num<< "\n";
			del.push_back(num);
	}

	for(int i=1;i<=noOfOpr-20;i++)
	{

		if(del.size()==0 || rand()%2==0)
		{
			int num=rand()%100;
			//insertNode(num);
			MyFile << "Insert:"<< num<< "\n";
			del.push_back(num);
		}

		else if(del.size() != 0)
		{
			int num=rand()%del.size();
			MyFile << "Delete:"<< del[num]<< "\n";
			remove_at(del, num);
		}


	}

	// Close the file
    MyFile.close();

	
}


/* ********************************* File Generating Module END ************************************************* */



/* ********************************* Final ANALYSIS File ****************************************************** */

void print_in_file(vector<Parameters> v) // Write in File Final Result
{
	int noOfTestFiles=5;

	ofstream MyFile("Final_Analysis.txt");

	for(int i=0;i<v.size();i++)
	{
			if(v[i].typeOfTree==1)
			{
				MyFile << "BST based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				MyFile << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				MyFile << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				MyFile << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				MyFile << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}

			else if(v[i].typeOfTree==2)
			{
				MyFile << "AVL based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				MyFile << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				MyFile << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				MyFile << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				MyFile << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}

			else if(v[i].typeOfTree==3)
			{
				MyFile << "Treap based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				MyFile << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				MyFile << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				MyFile << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				MyFile << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}
			
	}


	// Close the file
    MyFile.close();
}

void print_on_screen(vector<Parameters> v)
{
	int noOfTestFiles=5;
	
	for(int i=0;i<v.size();i++)
	{
			if(v[i].typeOfTree==1)
			{
				cout << "BST based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				cout << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				cout << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				cout << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				cout << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}

			else if(v[i].typeOfTree==2)
			{
				cout << "AVL based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				cout << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				cout << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				cout << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				cout << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}

			else if(v[i].typeOfTree==3)
			{
				cout << "Treap based implementation of Test File " << (i/3)+1 <<" details:"<<"\n\n";
				cout << "\t\t\tTotal No. of Comparison while insertion: "<<v[i].comparisonDuringInsertion<<"\n";
				cout << "\t\t\tTotal No. of Comparison while deletion: "<<v[i].comparisonDuringDeletion<<"\n";
				cout << "\t\t\tHeight of final tree: "<<v[i].heightOfFinalTree<<"\n";
				cout << "\t\t\tTotal No. of Rotations:"<<v[i].totalRotation<<"\n\n\n";
			}
			
	}

    return;
	
}


int main()
{
	srand(time(NULL));

	int noOfTestFiles=5;

	int num,i=1;

	cout<<"*** Test File Generation & Parameter Calculation Module ***\n\n\n";

	cout<<"*** Please NOTE: ***\n\n\n";

	cout<<"1. There are in total 5 TEST FILES\n\n";
	cout<<"2. Please specify Number of Operations in each TEST FILE.\n\n";
	cout<<"3. Please Enter A Large number like between 10000-5000.\n\n\n";

	cout<<"   Enter Number of Operation You want in test file "<<i++<<": ";

	cin>>num;

	cout<<"\n";

	GenerateFile("Test_File1.txt",num);

	cout<<"   Enter Number of Operation You want in test file "<<i++<<": ";

	cin>>num;

	cout<<"\n";

	GenerateFile("Test_File2.txt",num);

	cout<<"   Enter Number of Operation You want in test file "<<i++<<": ";

	cin>>num;

	cout<<"\n";

	GenerateFile("Test_File3.txt",num);

	cout<<"   Enter Number of Operation You want in test file "<<i++<<": ";

	cin>>num;

	cout<<"\n";

	GenerateFile("Test_File4.txt",num);

	cout<<"   Enter Number of Operation You want in test file "<<i++<<": ";

	cin>>num;

	cout<<"\n";

	GenerateFile("Test_File5.txt",num);

	cout<<"\n\n*** Successfully Made ALL the 5 TEST FILES!! ***\n\n\n";

	//Array of parameters
	vector<Parameters> P;

	P.push_back(Test_BST_Parameters("Test_File1.txt")); 
	P.push_back(Test_AVL_Parameters("Test_File1.txt"));
	P.push_back(Test_TREAP_Parameters("Test_File1.txt"));

	P.push_back(Test_BST_Parameters("Test_File2.txt")); 
	P.push_back(Test_AVL_Parameters("Test_File2.txt"));
	P.push_back(Test_TREAP_Parameters("Test_File2.txt"));

	P.push_back(Test_BST_Parameters("Test_File3.txt"));
	P.push_back(Test_AVL_Parameters("Test_File3.txt"));
	P.push_back(Test_TREAP_Parameters("Test_File3.txt"));

	P.push_back(Test_BST_Parameters("Test_File4.txt"));
	P.push_back(Test_AVL_Parameters("Test_File4.txt"));
	P.push_back(Test_TREAP_Parameters("Test_File4.txt"));

	P.push_back(Test_BST_Parameters("Test_File5.txt"));
	P.push_back(Test_AVL_Parameters("Test_File5.txt"));
	P.push_back(Test_TREAP_Parameters("Test_File5.txt")); 

	print_in_file(P); // Push into file

	cout<<"*** FILE STORED IN DIRECTORY FOR YOUR REFERENCE PLEASE CHECK!***\n\n\n";
	
	print_on_screen(P);
	
	return 0;
}

