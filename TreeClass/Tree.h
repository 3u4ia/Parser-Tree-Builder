#ifndef TREE_H
#define TREE_H
#include "../IntermediateStruct.h"
#include "TreeNodeStruct.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>

class Tree {
	private:
		TreeNode *root;

		char *baseFileName;
		FILE *inOrderFile = NULL;
		FILE *preOrderFile = NULL;
		FILE *postOrderFile = NULL;

		void insert(TreeNode *&, TreeNode *&);

		void displayInOrder(TreeNode *, size_t) const;
		void displayPreOrder(TreeNode *, size_t) const;
		void displayPostOrder(TreeNode *, size_t) const;
		void fileInitHelper(FILE **, const char *);
		
	public:
		Tree(char *fileName) {
			root = nullptr;
			if(fileName == nullptr){
				baseFileName = "out";
			} else {
				baseFileName = fileName; // Allocating new memory and copying the contents of the str
			}
			
			fileInitHelper(&preOrderFile, ".preorder");
		}
		Tree(TreeNode *root) {
			
		}
		~Tree() {
			if(inOrderFile) {
				fclose(inOrderFile);
			}
			if(preOrderFile) {
				fclose(preOrderFile);
			}
			if(postOrderFile) {
				fclose(postOrderFile);
			}

		}

		void insertNode(IntermediateRep);
		void buildTree(std::vector<IntermediateRep>);

		void displayInOrder()const { // overload
			displayInOrder(root, 0); // helper function essentially that calls displayInOrder
		}
		void displayPreOrder()const {
			displayPreOrder(root, 0);
		}
		void displayPostOrder()const {
			displayPostOrder(root, 0);
		}



		
};


#endif

