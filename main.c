#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* right;
    struct node* left;
};

struct stack
{
    struct node *dataa[30];
    int top;
};

struct stack *s=NULL;
struct node* root=NULL;
struct node* parent;
struct node* helper; // when displaying with either of the method the root value is lost so to restore the root value helper is used
void insert();
void display_inorder();
void init();
void push(struct node *);
struct node* pop();
int isEmpty();
void display_preorder();
void display_postorder();
void deletee();
void count();
void leaf_node(struct node*);
int main()
{

    int ch;
    while(1)
    {
        printf("\n============Enter Your Choice===============\n");
        printf("\n1.Insert \n2.Display Inorder \n3.Display Preorder \n4.Display Postorder \n5.Delete \n6.Total Nodes \n7.Leaf Node \n8. Exit \nCHOICE = ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\n===========INSERT============\n");
                insert();

                break;
            case 2:
                printf("\n============Display Inorder============\n ");
                init();
                display_inorder();

                break;
            case 3:
                printf("\n============Display Preorder============\n ");
                init();
                display_preorder();
                break;
            case 4:
                printf("\n============Display Postorder============\n ");
                init();
                display_postorder();
                break;
            case 5:
                printf("\n=================Delete==================\n");
                deletee();
                break;
            case 6:
                printf("\n=================Total Nodes==================\n");
                count();
                break;
            case 7:
                printf("\n=======================Leaf Node===================\n");
                leaf_node(helper);
                break;
            case 8: exit(0);
        }
    }
}

void insert()
{
    //int elem,i;
    int a;
    //printf("Enter the no. of elements\n");
    //scanf("%d",&elem);
    //for(i=0;i<elem;i++)
    printf("Enter the number\n");
    scanf("%d",&a);
    struct node* t;

    //for(i=0;i<elem;i++)
    //printf("%d",a[i]);
    t=(struct node*)malloc(sizeof(struct node));
    t->data=a;
    t->left=NULL;
    t->right=NULL;
    if(root==NULL)
    {
        root=t;
    }
    else
    {
        struct node* curr;
        //struct node*parent;
        curr=root;
        while(curr!=NULL)
        {
            parent=curr;
            if(t->data > curr->data)
            {
                curr=curr->right;
            }
            else
            {
                curr=curr->left;
            }
        }
        if(a<parent->data)
            parent->left=t;
        else
            parent->right=t;

    }
    helper=root;
}


void display_inorder()
{

    root=helper;
    while(1)
    {
        while(root!=NULL)
        {
            push(root);
            root=root->left;
        }
        if(isEmpty()==1){
            break;
        }
        root=pop();
        printf("%d-> ",root->data);

        root=root->right;
    }
    // s->top=-1;
}
void display_preorder()
{
    root=helper;
    while(1)
    {
        while(root!=NULL)
        {
            printf("%d->",root->data);
            push(root);
            root=root->left;
        }
        if(isEmpty()==1)
            break;
        root=pop();
        root=root->right;
    }
}
void display_postorder()
{
    root=helper;
    struct node* prev=NULL;
    do{
        while(root!=NULL)
        {
            push(root);
            root=root->left;
        }
        while(root==NULL && isEmpty()!=1)
        {
            root=s->dataa[s->top];
            if(root->right==NULL || root->right==prev)
            {
                printf("%d->",root->data);
                pop();
                prev=root;
                root=NULL;
            }
            else
                root=root->right;
        }
    }while(isEmpty()==0);
}
void init()
{
    s= (struct stack*)malloc(sizeof(struct stack));
    s->top=-1;
}

void push(struct node* temp) {
    s->top++;
    s->dataa[s->top]=temp;
}
struct node* pop()
{
    struct node *temp;
    temp= s->dataa[s->top];
    s->top=(s->top)-1;
    return(temp);

}
int isEmpty(){
    if( s->top==-1)
        return(1);
    else
        return(0);
}

void deletee()
{
    root=helper;
    int val;
    printf("Enter the value\n");
    scanf("%d",&val);
    struct node* curr;
    if(root==NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    curr=root;
    while(curr->data!=val)
    {
        parent=curr;
        if(val<curr->data)
        {
            curr=curr->left;
        }
        else if(val>curr->data)
        {
            curr=curr->right;
        }
        if(curr==NULL)
        {
            printf("Value not present");
            return;
        }
    }
    //deleting a left node without child
    if(curr->left==NULL && curr->right==NULL) {
        if (curr == parent->left) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        free(curr);
    }
        //deleting a right node with one left child
    else if(curr->left!=NULL && curr->right== NULL){
        if(curr==parent->right)
        {
            parent->right=curr->left;
        }
        curr->left=NULL;
        free(curr);

    }
        //deleting a right node with one right child
    else if(curr->left==NULL && curr->right!= NULL){
        if(curr==parent->right)
        {
            parent->right=curr->right;
        }
        curr->right=NULL;
        free(curr);
    }
    else if(curr->left==NULL && curr->right!= NULL){
        if(curr==parent->left)
        {
            parent->left=curr->right;
        }
        curr->right=NULL;
        free(curr);

    }
    else if(curr->left!=NULL && curr->right== NULL){
        if(curr==parent->left)
        {
            parent->left=curr->left;
        }
        curr->left=NULL;
        free(curr);

    }
    else if(curr->left!=NULL && curr-> right!=NULL)
    {
        struct node* t1, *t2;
        t1=curr->right;
        if(t1->left==NULL && t1->right==NULL)
        {
            curr->data=t1->data;
            curr->right=NULL;
            free(t1);
        }
        else if(t1->right!=NULL && t1->left==NULL)
        {
            curr->data=t1->data;
            curr->right=t1->right;
            t1->right=NULL;
            free(t1);
        }
        else if(t1->left!=NULL && (t1->right == NULL || t1->right!=NULL))
        {
            while(t1->left!=NULL) {
                t2 = t1;
                t1 = t1->left;
            }
            curr->data=t1->data;
            t2->left=NULL;
            free(t1);
        }
    }

}

void count()
{
    int total=0;
    root=helper;
    while(1)
    {
        while(root!=NULL)
        {
            push(root);
            root=root->left;
        }
        if(isEmpty()==1){
            break;
        }
        root=pop();
        total=total+1;
        //printf("%d-> ",root->data);

        root=root->right;
    }
    printf("Total Nodes =%d",total);
    // s->top=-1;
}

void leaf_node(struct node* root)
{
    //printf("hi");
    //root=helper;
    if(!root)
    {
        return;
    }
    if(!root->left && !root->right)
    {
        printf("%d->",root->data);
        return;
    }

    if(root->left!=NULL)
    {
        leaf_node(root->left);
    }
    if(root->right!=NULL)
    {
        leaf_node(root->right);
    }
}