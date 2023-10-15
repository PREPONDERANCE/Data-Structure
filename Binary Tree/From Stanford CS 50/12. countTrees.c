#include <stdio.h>

int A(int k){
	if( k == 0 || k == 1 )
		return 1;
	if( k == 2 )  return 2;
	if( k == 3 )  return 5;
	
	int sum = 0;
	
	for(int i = 0; i <= (k-1)/2; i++){
		if( i == k-1-i )
			sum += A(i)*A(k-1-i);
		else sum += A(i)*A(k-1-i)*2;
	}
	
	return sum;
}

int countTrees(int numKeys) {
	if (numKeys <=1) {
		return(1);
	} else {
		// there will be one value at the root, with whatever remains
		// on the left and right each forming their own subtrees.
		// Iterate through all the values that could be the root...
		int sum = 0;
		int left, right, root;
		for (root=1; root<=numKeys; root++) {
			left = countTrees(root - 1);
			right = countTrees(numKeys - root);
			// number of possible trees with this root == left*right
			sum += left*right;
		}
		return(sum);
	}
}


int main(){
	int number = 5;
	
	printf("%d\n", A(number));
	printf("%d\n", countTrees(number));
	
	return 0;
}