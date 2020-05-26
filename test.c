#include<stdio.h>
#include<stdlib.h>
#define BLACK 0
#define RED 1
struct RBT{
    struct RBT *parent,*left,*right;
    int data,color;
}*root=NULL;
void LLR(struct RBT *p,struct RBT **roots){
    struct RBT *p1=p->left;
    struct RBT *plr=p1->right;
    p1->right=p;
    p->left=plr;
    p1->color=BLACK;
    p->color=RED;
    p1->parent=p->parent;
    p->parent=p1;
    if(plr!=NULL)
        plr->parent=p;
    if(p1->parent==NULL)
        *roots=p1;
    else if(p1->parent->left==p)
        p1->parent->left=p1;
}
struct RBT * LRR(struct RBT *p,struct RBT **roots){
    struct RBT *p1=p->left;
    struct RBT *plr=p1->right;
    p1->right=plr->left;
    p->left=plr->right;
    plr->left=p1;
    plr->right=p;
    plr->parent=p->parent;
    p1->parent=p->parent=plr;
    p->color=RED;
    plr->color=BLACK;
    if(p1->right!=NULL)
        p1->right->parent=p1;
    if(p->left!=NULL)
        p->left->parent=p;
    if(plr->parent==NULL)
        *roots=plr;
    else if(plr->parent->left==p)
        plr->parent->left=plr;
}
struct RBT * RLR(struct RBT *p,struct RBT **roots){
    struct RBT *p1=p->right;
    struct RBT *plr=p1->left;
    p->right=plr->left;
    p1->left=plr->right;
    plr->left=p;
    plr->right=p1;
    plr->color=BLACK;
    p->color=RED;
    plr->parent=p->parent;
    p->parent=p1->parent=plr;
    if(p->right!=NULL)
        p->right->parent=p;
    if(p1->left!=NULL)
        p1->left->parent=p1;
    if(plr->parent==NULL)
        *roots=plr;
    else if(plr->parent->right==p)
        plr->parent->right=plr;
}
void RRR(struct RBT *p,struct RBT **roots){
    struct RBT *p1=p->right;
    struct RBT *plr=p1->left;
    p1->left=p;
    p->right=plr;
    p1->parent=p->parent;
    p->parent=p1;
    p1->color=BLACK;
    p->color=RED;
    if(p->right!=NULL)
        p->right->parent=p;
    if(p1->parent==NULL)
        *roots=p1;
    else if(p1->parent->right==p)
        p1->parent->right=p1;
}
void Inorder(struct RBT *p){
    if(p==NULL)
        return;
    Inorder(p->left);
    printf("%d[%d]\t",p->data,p->color);
    Inorder(p->right);
}
void Preorder(struct RBT *p){
    if(p==NULL)
        return;
    printf("%d[%d]\t",p->data,p->color);
    Preorder(p->left);
    Preorder(p->right);
}
void Fix(struct RBT *p,struct RBT **roots){
    if(p->color==RED && p->parent==NULL){
        p->color=BLACK;
        return;
    }
    while(p->color==RED && p->parent->color==RED){
        if(p->parent==p->parent->parent->left){
            if(p->parent->parent->right==NULL || p->parent->parent->right->color==BLACK){
                if(p==p->parent->left){
                    LLR(p->parent->parent,roots);
                }
                else if(p==p->parent->right){
                    LRR(p->parent->parent,roots);
                }
            }
            else if(p->parent->parent->right->color==RED){
                p->parent->color=BLACK;
                p->parent->parent->right->color=BLACK;
                p->parent->parent->color=RED;
                p=p->parent->parent;
                if(p->parent==NULL)
                    break;
            }
        }
        else if(p->parent==p->parent->parent->right){
            if(p->parent->parent->left==NULL || p->parent->parent->left->color==BLACK){
                if(p==p->parent->left){
                    RLR(p->parent->parent,roots);
                }
                else if(p==p->parent->right){
                    RRR(p->parent->parent,roots);
                }
            }
            else if(p->parent->parent->left->color==RED){
                p->parent->color=BLACK;
                p->parent->parent->left->color=BLACK;
                p->parent->parent->color=RED;
                p=p->parent->parent;
                if(p->parent==NULL)
                    break;
            }
        }
    }
    if(p->color==RED && p->parent==NULL){
        p->color=BLACK;
        return;
    }
}
void Insert(struct RBT **roots,int key){
    struct RBT *p=*roots,*prev=NULL;
    struct RBT *node=(struct RBT *)malloc(sizeof(struct RBT));
    node->data=key;
    node->color=RED;
    node->left=node->right=node->parent=NULL;
    while(p!=NULL){
        prev=p;
        if(p->data<key)
            p=p->right;
        else if(p->data>key)
            p=p->left;
    }
    if(prev==NULL)
        *roots=node;
    else if(prev->data<key)
        prev->right=node;
    else if(prev->data>key)
        prev->left=node;
    node->parent=prev;
    Fix(node,roots);
}
int main(){
    Insert(&root,10);
    Insert(&root,20);
    Insert(&root,30);
    Insert(&root,50);
    Insert(&root,40);
    Insert(&root,60);
    Insert(&root,70);
    Insert(&root,80);
    Insert(&root,4);
    Insert(&root,8);
    printf("Inorder:\t");
    Inorder(root);
    printf("\n-------------\n");
    printf("Preorder:\t");
    Preorder(root);
    return 0;
}
