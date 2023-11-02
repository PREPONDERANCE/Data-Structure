 #include <iostream>
#include <string.h>
using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int size(BiTree T){
    if( !T ) return 0;
    return size(T->lchild) + size(T->rchild) + 1;
}

void create(BiTree &T, char S[], int &i){
    if(S[i]=='0')
		T=NULL;
	else
	{
		T=new BiTNode;
		T->data=S[i];
		create(T->lchild,S,++i);
		create(T->rchild,S,++i);
	}
}

BiTree CreateBiTree(int &pos, char *str)
{// 先序建立二叉树
   BiTree T;
   create(T, str, pos);
    return T;
}

int Width(BiTree T)
{// 求二叉树T最大宽度
    BiTree queueNode[size(T)];
    int l = 0, r = 0;
    queueNode[l] = T;

    int maxWidth = 0;
    while( r >= l ){
        int currWidth = r-l+1;
        maxWidth = max(maxWidth, currWidth);
        int temp = r;
        for(int i = l; i <= temp; i++){
            BiTree node = queueNode[l++];
            if( node->lchild ) queueNode[++r] = node->lchild;
            if( node->rchild ) queueNode[++r] = node->rchild;
        }
    }

    return maxWidth;
}


int main()
{
    char str[1000];
    while(cin>>str)
        {
            if(strcmp(str,"0")==0) break;
            int pos=0;                         // 标记字符串处理位置
            BiTree root=CreateBiTree(pos,str);
            cout<<Width(root)<<endl;
        }
    return 0;
}