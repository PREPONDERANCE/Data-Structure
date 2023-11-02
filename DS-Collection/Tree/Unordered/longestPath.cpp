 #include<iostream>
#define MAXSIZE 100
using namespace std;
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T,char S[],int &i){
	if(S[i]=='0') T=NULL;
	else{
		T=new BiTNode;
		T->data=S[i];
		CreateBiTree(T->lchild,S,++i);
		CreateBiTree(T->rchild,S,++i);
	}
}

void longestUtil(BiTree root, BiTree temp[], BiTree path[], int &longest){
	static int len = 1;
	
	if( !root ) return;
	if( !root->lchild && !root->rchild ){
		temp[len] = root;
		if( longest < len ){
			longest = len;
			for(int i = 1; i <= len; i++)
				path[i] = temp[i];
		}
		return;
	}
	temp[len++] = root;
	longestUtil(root->lchild, temp, path, longest);
	longestUtil(root->rchild, temp, path, longest);
	len--;
}

void longestPath(BiTree root,BiTree path[],int &longest)
{//二叉树最长路径的求解
	BiTree temp[100];
	longestUtil(root, temp, path, longest);
}

int main()
{
	char S[100];
	while(cin>>S&&S[0]!='0')
		{
			int i=-1;
			BiTree T;
			BiTree l[MAXSIZE];
			int longest=0;
			CreateBiTree(T,S,++i);
			longestPath(T,l,longest);
			cout<<longest<<endl;
			for(int k=1;k<=longest;k++)
				cout<<l[k]->data;
			cout<<endl;
		}
	return 0;
}
