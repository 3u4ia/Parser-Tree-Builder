#include "Tree.h"



void Tree::fileInitHelper(FILE **filePtr, const char *extension) {
	size_t newSize = strlen(baseFileName) + strlen(extension);
	char *fullFileName = (char *)malloc(newSize + 1);
	strcpy(fullFileName, baseFileName);
	strcat(fullFileName, extension);
	*filePtr = fopen(fullFileName, "w");
	if(!*filePtr) {
		perror("fopen failed");
	}
	free(fullFileName);
}



void Tree::displayPreOrder(TreeNode *nodePtr, size_t depth) const {
	if(nodePtr) {
		for(size_t i = 0; i < depth * 2; i++) fprintf(preOrderFile, " ");

		fprintf(preOrderFile, "%s: ", nodePtr->label);
		for(size_t i = 0; i < nodePtr->words.size(); i++) {
			fprintf(preOrderFile, "%s ", nodePtr->words[i]);
		}
		fprintf(preOrderFile, "\n");
		displayPreOrder(nodePtr->left, depth+1);
		displayPreOrder(nodePtr->middle, depth+1);
		displayPreOrder(nodePtr->right, depth+1);

	}
}


