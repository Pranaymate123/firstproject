//  =================================Binary Search Tree============================================//
#include<stdio.h>
#include<stdlib.h>
struct node *makeNode(int);
void left(struct node* ,int);
void right(struct node*,int);
void inorder(struct node*);
void preorder(struct node*);
void postorder(struct node*);
struct node *create();
void insertNode(struct node*,int);
int searchNode(struct node*,int);
struct node *deleteNode(struct node*,int);
void deleteLeafNode(struct node*,struct node*);
void deleteNodeWith_1child(struct node*,struct node*);
void deleteNodeWith_2child(struct node*,struct node*);

struct node
{
    int data;
    struct node *right;
    struct node *left;
}*root,*parent,*curr;

int main()
{
     int num1,search;
    root=NULL;
    int key,ch,c=1;
    do
    {
        printf("\nEnter the choice\n1 for create The BST\n2 for display tree\n3 for insert node in the tree \n4 For delete The node\n5 for searching node \n");
        scanf("%d",&ch);
        if(ch==1)
        {
            root=create();
        }
        else if(ch==2)
        {
            if(root==NULL)
            {
                printf("\nThe Tree Is not created or The tree is deleted or empty\n");
            }
            else
            {
                int ch1;
                printf("\n1 For Inorder\n2 For Preorder\n3 For Postorder\nEnter the choice\n");
                scanf("%d",&ch1);
                if(ch1==1)
                {
                    printf("\nThe inorder Trversal is \n");
                    inorder(root);

                }
                else if(ch1==2)
                {
                    printf("\nThe preorder Trversal is \n");
                    preorder(root);
                }
                else if(ch1==3)
                {
                    printf("The Postorder Traversal is \n");
                    postorder(root);
                }
                else
                {
                    printf("\nInvalid Choice");
                }

            }
            
        }  
        else if(ch==3)
        {
            if(root==NULL)
            {
                printf("\nThe tree is not created yet \n");
            }
            else
            {
                printf("\nEnter the element\n");
                scanf("%d",&key);
                insertNode(root,key);
            }
        } 
        else if(ch==4)
        {
            if(root==NULL)
            {
                printf("\nThe tree is not created yet \n");
            }
            else
            {
                 printf("\nEnter the node to delete\n");
                scanf("%d",&num1);
                root=deleteNode(root,num1);
            }
            
           
        }
        else if(ch==5)
        {
            printf("\nEnter the element to search in the tree\n");
            scanf("%d",&search);
            int flag=searchNode(root,search);   
            if(flag==1)
            {
                printf("\n%d is present in the tree \n",search);
            }
            else
            {
                printf("\n%d is not present in the tree\n",search);
            }
        }
        else
        {
            printf("\nInvalid\n");
        }
        printf("\nTo continue Press 1\n");
        scanf("%d",&c);
    } while (c==1);
    
    return 0;
} 

struct node *create()
{
    int key;
    int choice;
    printf("\nEnter the Root Element To create the Tree ");
    scanf("%d",&key);
    if(root==NULL)
    {
        root=makeNode(key);
    }
    else
    {
        insertNode(root,key);
    }  
    return root;
}

// Function to Which make the node and returns it
struct node *makeNode(int num)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=num;
    newnode->left=newnode->right=NULL;
    return newnode;
}

// Function To insert the node at left
void left(struct node *temp,int key)
{
    if(temp->left==NULL)
    {
        temp->left=makeNode(key);   
    }
    else
    {
        printf("\nInvalid\n");
    }
}

// Function to insert the node at right
void right(struct node *temp,int key)
{
    if(temp->right==NULL)
    {
        temp->right=makeNode(key);   
    }
    else
    {
        printf("\nInvalid\n");
    }
}

//Recursive Functin For Inorder Traversal
void inorder(struct node *root)
{
    struct node *temp;
    temp=root;
    if(temp!=NULL)
    {
        inorder(temp->left);
        printf("\t%d",temp->data);
        inorder(temp->right);
    }
}

//Recursive Functin For Preorder Traversal
void preorder(struct node *root)
{
    struct node *temp;
    temp=root;
    if(temp!=NULL)
    {
        printf("\t%d",temp->data);
        preorder(temp->left);
        preorder(temp->right);
    }
}

//Recursive Functin For Postorder Traversal
void postorder(struct node *root)
{
    struct node *temp;
    temp=root;
    if(temp!=NULL)
    {
        postorder(temp->left);
        postorder(temp->right);
        printf("\t%d",temp->data);

    }
}

void insertNode(struct node *root,int key)
{
    
        parent=root;
        curr=root;
        while(key !=parent->data && curr!=NULL )
        {
            parent=curr;
            if(key<parent->data)
            {
                curr=parent->left;
            }
            else
            {
                curr=parent->right;
            }

        }
        if(key<parent->data)
        {
            printf("\nLeft branch of %d is %d\n",parent->data,key);
            left(parent,key); 
        }
        else
        {
            printf("\nRight branch of %d is %d\n",parent->data,key);
            right(parent,key);
        }
   
}
// ======================================================DELETE NODE SECTION ===============================================================
struct node *deleteNode(struct node *root,int key)
{
    if(root->data==key)
    {
        root=NULL;
        printf("\nThe Root is deleted i.e. Tree Is deleted\n");
    }

    else if(searchNode(root,key)==1)
    {
        // Code to find the parent node and the node which is to be deleted
        // -----------------------------------------------------------------------//
        struct node *temp;
        temp=root;
        parent=root;
        while(temp->data!=key)
        {
            parent=temp;
            if(key<temp->data)
            {
                temp=temp->left;
            }
            else
            {
                temp=temp->right;
            }
        }
        //Temp  is the node which is to be Deleted 
        // Parent is the parent node of temp

        // ----------------------------To delete the node having Two child Nodes----------------------------//
        if(temp->left!=NULL && temp->right!=NULL)
        {
            deleteNodeWith_2child(temp,parent);   
        }
        // -----------------------------------To delete The node having One child ------------------------------//
        else if((temp->left!=NULL&& temp->right==NULL)  || (temp->left==NULL && temp->right!=NULL))
        {
            deleteNodeWith_1child(temp,parent);
        }
        //---------------------------------- to delete the leaf node---------------------------------//
        else if(temp->left==NULL && temp->right==NULL)
        {
            deleteLeafNode(temp,parent);
        }
        printf("%d is successFully deleted",key);
    }
    else
    {
        printf("\n%d Element not present in the tree \n");
    }
    return root;
 
}


void deleteNodeWith_2child(struct node *temp,struct node *parent)
{
    int flag=0;
    struct node *temp_succ;
    struct node *ts_parent;
    ts_parent=temp;
    temp_succ=temp->right;
    while(temp_succ->left!=NULL)
    {
        flag=1;
        ts_parent=temp_succ;
        temp_succ=temp_succ->left;
    }
    if(flag==0)
    {
        temp->data=temp_succ->data;
        temp->right=temp_succ->right;
    }
    else
    {
        temp->data=temp_succ->data;
        ts_parent->left=temp_succ->right;
    }  
}


void deleteNodeWith_1child(struct node *temp,struct node *parent)
{
    // --------------------------------Node having Left Child --------------------------------------------//
    if(temp->left!=NULL && temp->right==NULL)
    {
        if(parent->left==temp)
        {
            parent->left=temp->left;
        }
        else
        {
            parent->right=temp->left;
        }
    }
    // --------------------------------Node having Right Child --------------------------------------------//
    if(temp->left==NULL && temp->right!=NULL)
    {
        if(parent->left==temp)
        {
            parent->left=temp->right;
        }
        else
        {
            parent->right=temp->right;
        }
    }

}


void deleteLeafNode(struct node *temp,struct node *parent)
{
    
        if(parent->left==temp)
        {
            parent->left=NULL;
        }
        else
        {
            parent->right=NULL;
        }
    
}

// ==========================================================================================================================
// ----------------------Function to search The Node in the Binary Search Tree-----------------------//
int searchNode(struct node *root,int key)
{
    int flag=0;
    if(root==NULL)
    {
        printf("\nThe Tree Is empty\n");
    }
    else
    {
        struct node *temp;
        temp=root;
        
        while(temp!=NULL)
        {
            if(temp->data==key)
            {
                flag=1;
                
                break;
            }
            if(key < temp->data)
            {
                temp=temp->left;
            }
            else
            {
                temp=temp->right;
            }
        }
       
    } 
     return flag;
}


                                