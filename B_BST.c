#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *left,*right;
    int ht;
}node;

node *insert(node *,int);
void preorder(node *);
void inorder(node *);
void postorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
int count_nodes(node *);
int count_intnodes( node *);
int count_extnodes( node *);


int main()
{
    node *root=NULL;
    int x,n,i,op;

    do
    {
        printf("\n1)Create:");
        printf("\n2)Insert:");
        printf("\n3)Print:");
		printf("\n4)Total nodes:");
		printf("\n5)Internal Nodes:");
		printf("\n6)External Nodes:");
        printf("\n7)PreOrder Sequence:");
        printf("\n8)InOrder Sequence:");
		printf("\n9)PostOrder Sequence:");
        printf("\n10)Quit:");
        printf("\n\nEnter Your Choice:");
        scanf("%d",&op);

        switch(op)
        {
            case 1: printf("\nEnter no. of elements:");
                    scanf("%d",&n);
                    printf("\nEnter tree data:");
                    root=NULL;
                    for(i=0;i<n;i++)
                    {
                        scanf("%d",&x);
                        root=insert(root,x);
                    }
                    break;

            case 2: printf("\nEnter a data:");
                    scanf("%d",&x);
                    root=insert(root,x);
                    break;

            case 3: printf("\nPreorder sequence:\n");
                    preorder(root);
                    printf("\nInorder sequence:\n");
                    inorder(root);
					printf("\nPostorder sequence:\n");
                    postorder(root);
                    printf("\n");
                    break;

			case 4: printf("\nThus Total No Of Nodes Are %d\n",count_nodes(root));
				    break;

			case 5: printf("\nThus Total No Of Internal Nodes Are %d\n",count_intnodes(root));
				    break;

			case 6: printf("\nThus Total No Of External Nodes Are %d\n",count_extnodes(root));
				    break;

			case 7: printf("\nPreorder sequence:\n");
                    preorder(root);
					printf("\n");
                    break;

			case 8: printf("\nInorder sequence:\n");
                    inorder(root);
					printf("\n");
                    break;

			case 9: printf("\nPostorder sequence:\n");
                    postorder(root);
					printf("\n");
                    break;

        }
    }while(op!=10);

    return 0;
}

node * insert(node *T,int x)
{
    if(T==NULL)
    {
        T=(node*)malloc(sizeof(node));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
        if(x > T->data)        // insert in right subtree
        {
            T->right=insert(T->right,x);
            if(BF(T)==-2)
                if(x>T->right->data)
                    T=RR(T);
                else
                    T=RL(T);
        }
        else
            if(x<T->data)
            {
                T->left=insert(T->left,x);
                if(BF(T)==2)
                    if(x < T->left->data)
                        T=LL(T);
                    else
                        T=LR(T);
            }

        T->ht=height(T);

        return(T);
}

int height(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);

    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;

    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;

    if(lh>rh)
        return(lh);

    return(rh);
}

node * rotateright(node *x)
{
    node *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    return(y);
}

node * rotateleft(node *x)
{
    node *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);

    return(y);
}

node * RR(node *T)
{
    T=rotateleft(T);
    return(T);
}

node * LL(node *T)
{
    T=rotateright(T);
    return(T);
}

node * LR(node *T)
{
    T->left=rotateleft(T->left);
    T=rotateright(T);

    return(T);
}

node * RL(node *T)
{
    T->right=rotateright(T->right);
    T=rotateleft(T);
    return(T);
}

int BF(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);

    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;

    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;

    return(lh-rh);
}

void preorder(node *T)
{
    if(T!=NULL)
    {
        printf("%d  [Bf=%d]\t",T->data,BF(T));
        preorder(T->left);
        preorder(T->right);
    }
}

void inorder(node *T)
{
    if(T!=NULL)
    {
        inorder(T->left);
        printf("%d  [Bf=%d]\t",T->data,BF(T));
        inorder(T->right);
    }
}

void postorder(node *T)
{
    if(T!=NULL)
    {
        postorder(T->left);
		postorder(T->right);
        printf("%d  [Bf=%d]\t",T->data,BF(T));
    }
}
int count_nodes(node *T)
{
    int count=0;
	int countl=0;
	int countr=0;

    if(T!=NULL)
    {
        count++;
        countl=count_nodes(T->left);
        countr=count_nodes(T->right);
        count+=countl+countr;
    }
    return count;
}
int count_intnodes( node *T)
{
    int count=0;
	int countl=0;
	int countr=0;
    if(T!=NULL)
    {
        if ((T->left==NULL)&&(T->left==NULL))
                count++;
        countl=count_intnodes(T->left);
        countr=count_intnodes(T->right);
        count+=countl+countr;
    }
    return count;
}
int count_extnodes( node *T)
{
    int count=0;
	int countl=0;
	int countr=0;
    if(T!=NULL)
    {
        if (!((T->left==NULL)&&(T->left==NULL)))
                count++;
        countl=count_extnodes(T->left);
        countr=count_extnodes(T->right);
        count+=countl+countr;
    }
    return count;
}
