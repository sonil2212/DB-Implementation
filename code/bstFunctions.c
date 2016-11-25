/*
 * bstFunctions.c
 *
 *  Created on: 30-Aug-2014
 *      Author: sonil
 */

#include <stdlib.h>
#include <stdio.h>
#include <pdsProject.h>
#include <stdbool.h>

struct BSTNode *parent = NULL;
struct BSTNode *currentNode = NULL;
struct BSTNode *precedessor = NULL;
struct BSTNode *precedessorParent = NULL;

//inserts node into binary search tree
void insertBST(struct BSTNode **ParRoot, unsigned long int ParKey,
		unsigned long int ParOffset, char ParFlag) {


	if (*ParRoot == NULL) {
		*ParRoot = malloc(sizeof(struct BSTNode));
		(*ParRoot)->left = NULL;
		(*ParRoot)->key = ParKey;
		(*ParRoot)->offset = ParOffset;
		(*ParRoot)->flag = ParFlag;
		(*ParRoot)->right = NULL;
	}

	else if (ParKey < ((*ParRoot)->key)) {
		insertBST(&((*ParRoot)->left), ParKey, ParOffset, ParFlag);
	}

	else if (ParKey > ((*ParRoot)->key)) {
		insertBST(&((*ParRoot)->right), ParKey, ParOffset, ParFlag);
	}

}

//inorder traversal of tree
void inorderTraversalBST(struct BSTNode *ParRoot) {
	if (ParRoot == NULL) {
		return;
	}

	inorderTraversalBST(ParRoot->left);
	printf("%lu  ", ParRoot->key);
	inorderTraversalBST(ParRoot->right);
}

//preorder traversl of BST
void preorderTraversalBST(struct BSTNode *ParRoot) {
	if (ParRoot == NULL) {
		return;
	}

	printf("%d  ", ParRoot->key);
	preorderTraversalBST(ParRoot->left);
	preorderTraversalBST(ParRoot->right);
}

//searching key in given bst

bool searchBST(struct BSTNode *ParRoot, unsigned long int value) {
		if (value == (ParRoot->key)) {
		currentNode = ParRoot;
		return true;
	}

	else if (value < (ParRoot->key)) {
		if ((ParRoot->left) != NULL) {
			parent = ParRoot;
			searchBST(ParRoot->left, value);
		} else {
			return false;
		}
	}

	else if (value > (ParRoot->key)) {
		if ((ParRoot->right) != NULL) {
			parent = ParRoot;
			searchBST(ParRoot->right, value);
		}

		else {
			return false;
		}
	}
else	{
		printf("\noops!seems key are not integers.Please check");
		return false;
	}


}

//find max element in the BST
void findPrecedessor(struct BSTNode *ParRoot) {

	if (ParRoot == NULL) {
		return;
	} else if (ParRoot->right == NULL) {
		precedessor = ParRoot;
		precedessorParent = currentNode;
	} else {
		while (ParRoot->right != NULL) {
			precedessorParent = ParRoot;
			ParRoot = ParRoot->right;
		}
		precedessor = ParRoot;

	}

}

//delete the node from BST
void deleteBST(struct BSTNode *ParRoot, int key) {
	searchBST(ParRoot, key);

	//when deleting node has both subtree NULL
	if (currentNode->left == NULL && currentNode->right == NULL) {
		if ((currentNode->key) < (parent->key)) {
			parent->left = NULL;
		} else {
			parent->right = NULL;
		}
	}

	//when deleting node has either subtree NULL
	else if (currentNode->left == NULL || currentNode->right == NULL) {
		//when right subtree null
		if (currentNode->left != NULL) {
			if ((currentNode->key) > (parent->key)) {
				parent->right = currentNode->left;
			} else {
				parent->left = currentNode->left;
			}
		}

		//when left subtree is null
		else {

			if ((currentNode->key) > (parent->key)) {
				parent->right = currentNode->right;
			} else {
				parent->left = currentNode->right;
			}
		}
	}

	else {
		findPrecedessor(currentNode->left);
		//when precedessor is left node itself
		if (currentNode == precedessorParent) {
			if (currentNode->key < parent->key) {
				parent->left = precedessor;
			} else {
				parent->right = precedessor;
			}
			precedessor->right = currentNode->right;
		}

		//when right subtree in left node of deleting node
		else {
			precedessorParent->right = NULL;
			precedessor->left = currentNode->left;
			precedessor->right = currentNode->right;
			if ((currentNode->key) < (parent->key)) {
				parent->left = precedessor;
			} else {
				parent->right = precedessor;
			}
		}
	}
	currentNode = NULL;
}

