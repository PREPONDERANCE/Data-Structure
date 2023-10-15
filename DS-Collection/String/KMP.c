#include <stdio.h>
#include <string.h>

int KMP(char* haystack, char* needle){
	if( needle == NULL ) return 0;
	int M = strlen(needle);
	int lps[M];
	
	int prevLPS = 0, i = 1;
	while( i < M ){
		if( needle[i] == needle[prevLPS] ){
			lps[i] = prevLPS+1;
			prevLPS++;
			i++;
		}else if( prevLPS == 0 ) lps[i++] = 0;
		else prevLPS = lps[prevLPS-1];
	}
	
	i = 0; int j = 0;
	while( i < strlen(haystack) ){
		if( haystack[i] == needle[j] ) { i++; j++; }
		else{
			if( j == 0 ) i++;
			else j = lps[j-1];
		}
		if( j == M ) return i-M;
	}
	
	return -1;
}

int main(int argc, char *argv[]) {
	char target[] = "acabaabaabcacaabc";
	char matching[] = "abaabc";
	
	printf("%d", KMP(target, matching));
	
	return 0;
}


//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//int* KMP(char* haystack, char* needle){
//	if( needle == NULL ) return 0;
//	int len1 = strlen(needle), len2 = strlen(haystack);
//	int lps[len1];
//	
//	int prevLPS = 0, i = 1, j = 0, k = 0;
//	while( i != len1 ){
//		if( needle[i] == needle[prevLPS] ){
//			lps[i++] = prevLPS+1;
//			prevLPS++;
//		}else if( prevLPS == 0 ) lps[i++] = 0;
//		else prevLPS = lps[prevLPS-1];
//	}
//	
//	i = 0;
//	int* match = (int*)malloc(sizeof(int) * len2);
//	while( i != len2 ){
//		if( haystack[i] == needle[j] ) { i++; j++; }
//		else{
//			if( j == 0 ) i++;
//			else j = lps[j-1];
//		}
//		if( j == len1 ){
//			match[k++] = i-len1;
//			j = 0;
//		}
//	}
//	
//	return match;
//}
//
//int main(int argc, char *argv[]) {
//	char testString[] = "This string is a test string";
//	char matchString[] = "string";
//	
//	int* arr = KMP(testString, matchString);
//	for(int i = 0; arr[i] != 0; i++) printf("%d ", arr[i]);
//	
//	return 0;
//}