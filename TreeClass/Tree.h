#ifndef TREE_H
#define TREE_H
#include "TreeNodeStruct.h"
#include "../TokensAndStates/TokensAndStates.h" // May cause circular dependencies

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>

class Tree {
	private:
		TreeNode *root;

		char *baseFileName;
		FILE *preOrderFile = NULL;

		void displayPreOrder(TreeNode *, int) const;
		void fileInitHelper(FILE **, const char *);
		
	public:
		Tree(char *fileName) {
			printf("hello?\n");
			printf("something new\n");
			root = nullptr;
			if(fileName == nullptr){
				baseFileName = "out";
			} else {
				baseFileName = fileName; // Allocating new memory and copying the contents of the str
			}
			
			fileInitHelper(&preOrderFile, ".preorder");
		}
		Tree(char *fileName, TreeNode *root) {
			printf("First line in Tree(fileName, root)\n");
			printf("Filename Tree Class received: %s\n", fileName);
			printf("This should re run make\n");
			this->root = root;
			if(fileName == nullptr) {
				baseFileName = "out";
			} else {
				baseFileName = fileName;
			}
			printf("Before fileInitHelper runs\n");
			fileInitHelper(&preOrderFile, ".preorder");
			printf("AFter fileInitHelper runs\n");
		}
		~Tree() {
			if(preOrderFile) {
				fclose(preOrderFile);
			}
			cleanTree(root);
		}
		void cleanTree(TreeNode *node) {
			if (node == nullptr) return;
			for(int i = 0; i < 3; i++) {
				cleanTree(node->nodeArr[i]);
			}
			delete node;
		}

		void displayPreOrder() const;


		
};


#endif

