#include "Tree.h"



void Tree::fileInitHelper(FILE **filePtr, const char *extension) {
	printf("Over here\n");
	size_t newSize = strlen(baseFileName) + strlen(extension);
	char *fullFileName = (char *)malloc(newSize + 1);
	strcpy(fullFileName, baseFileName);
	strcat(fullFileName, extension);
	printf("fullFileName being created: %s\n", fullFileName);
	*filePtr = fopen(fullFileName, "w");
	if(!*filePtr) {
		perror("fopen failed");
	}
	free(fullFileName);
}



void Tree::displayPreOrder(TreeNode *nodePtr, int depth) const {
	printf("Start of displayPreOrder func\n");
	if(nodePtr) {
		for(size_t i = 0; i < depth * 2; i++) fprintf(preOrderFile, " ");
		printf("Error here?\n");
		int tokenID = -1;
		printf("preOrderFile %p\n", (void*)preOrderFile);
		fprintf(preOrderFile, "%s ", nodePtr->label);
		printf("Maybe error here?\n");

		for(int i = 0; i < 3; i++) {
			printf("Within display\n");
			tokenID = nodePtr->tokenArr[i].tokenID;
			if(tokenID != -1) {
				fprintf(preOrderFile, "%s:%s:%d", tokenNames[tokenID - 1000], nodePtr->tokenArr[i].lexeme, nodePtr->tokenArr[i].lineNum);
			} else {
				fprintf(preOrderFile, "\n");
				break;
			}
		}
		printf("After display for loop\n");
		for(int i = 0; i < 3; i++) {
			displayPreOrder(nodePtr->nodeArr[i], depth+1);
		}
	}
}
void Tree::displayPreOrder()const {
	displayPreOrder(root, 0);
}



