#include <iostream>
using namespace std;

class Node // AVL tree node class
{
public:
	int key;// stores the node key
	Node* left;// pointer to the left subtree
	Node* right;// pointer to the right subtree
	int height;// tree height
};

int max(int a, int b)// Function to get the maximum of two integers
{
	return (a > b) ? a : b;
}

int height(Node* N)// Function for obtaining the height of the tree
{
	if (N == NULL)// if our N == NULL (tree is empty) then just return 0, otherwise return our height
	{
		return 0;
	}
	return N->height;
}

Node* newNode(int key)// Auxiliary function that selects a new node with a given key, and NULL left and right pointers.
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;// reset the left subtree
	node->right = NULL;// reset the right subtree
	node->height = 1;// a new node is first added to the letter
	return(node);// return this node
}

Node* rightRotate(Node* y)// Function for turning to the right of a subtree with roots y
{
	Node* x = y->left;// initialize, pointer to left and right subtree
	Node* T2 = x->right;

	x->right = y;// Perform rotation
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;// Update height

	x->height = max(height(x->left), height(x->right)) + 1;

	return x;// Return a new root
}

Node* leftRotate(Node* x)// Function to rotate the subtree to the root with x
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;// Perform rotation
	x->right = T2;

	x->height = max(height(x->left),// Update height
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;

	return y;// Return a new root
}

int getBalance(Node* N)// Get the balance coefficient of the node N
{
	if (N == NULL)// if n 0 (empty tree)
	{
		return 0;// return 0
	}
	return height(N->left) - height(N->right);// otherwise the height of the left node is the height of the right node
}

Node* insert(Node* node, int key)// recursive function to insert a key in a subtree rooted with a node and return a new subtree root.
{
	if (node == NULL)// 1. Perform a regular BST insert
	{
		return(newNode(key));
	}
	if (key < node->key)// normal insert into the binary search tree
	{
		node->left = insert(node->left, key);// if the key you want to insert is smaller than the key of the unchanged node (vertex) is the left subtree
	}
	else if (key > node->key)// if the key you want to insert is larger than the key of the unchanged node (vertex) it is the right subtree
	{
		node->right = insert(node->right, key);
	}
	else // It is forbidden to use the same keys in BST
	{
		return node;
	}

	node->height = 1 + max(height(node->left), height(node->right));// 2. Update the height of this ancestor node

	int balance = getBalance(node);// 3. Get the balance of this ancestor node to see if this node has become unbalanced

	// If this node becomes unbalanced, there are 4 cases
	if (balance > 1 && key < node->left->key)// 1) Left left case
	{// balance greater than 1, the key to be inserted is smaller than the key of the unchanged vertex of the left subtree
		return rightRotate(node);// rotate the tree to the right right right case
	}

	if (balance < -1 && key > node->right->key)// 2) Right Right case
	{
		return leftRotate(node);// similar to the first case
	}

	if (balance > 1 && key > node->left->key)// 3) Left right case
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key)// 4) Right left case
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;// return (unchanged) the node pointer
}

void preOrder(Node* root)// Function for printing AVL tree by sequence. The function also prints the height of each node
{
	if (root != NULL)// the root is not equal to 0
	{
		cout << root->key << " ";
		preOrder(root->left);// the root of the left subtree
		preOrder(root->right);// root of the right subtree
	}
}

int main()
{
	Node* root = NULL;

	root = insert(root, 17);
	root = insert(root, 26);
	root = insert(root, 28);
	root = insert(root, 30);
	root = insert(root, 45);
	root = insert(root, 60);

	/* The constructed AVL tree will look like:
			 30
			/  \
		   26  46
		  / \    \
		17  28   60
	*/
	cout << "1)Preorder traversal of the constructed AVL tree is " << endl;
	preOrder(root);

	Node* root_1 = NULL;

	root_1 = insert(root_1, 2);
	root_1 = insert(root_1, 4);
	root_1 = insert(root_1, 8);
	root_1 = insert(root_1, 7);
	root_1 = insert(root_1, 5);
	root_1 = insert(root_1, 9);
	root_1 = insert(root_1, 10);
	root_1 = insert(root_1, 11);
	root_1 = insert(root_1, 6);

	/* The constructed AVL tree will look like:
			   12
			/      \
		   6       19
		  / \      / \
		5   10    14  20
						\
						24
	*/
	cout << endl << "2)Preorder traversal of the constructed AVL tree is " << endl;
	preOrder(root_1);

	return 0;
	
}
