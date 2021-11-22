/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode** find_replace(struct TreeNode **root){
    if((*root)->left == NULL){
        return root;
    }
    
    return find_replace(&(*root)->left);
}
void __deleteNode(struct TreeNode **root, int key){
    struct TreeNode **replace, *del;
    
    if(*root == NULL){
        return;
    }
    
    if((*root)->val == key){
        if((*root)->left==NULL && (*root)->right==NULL){
            free(*root);
            *root = NULL;
        }
        else if((*root)->left && (*root)->right){
            replace = find_replace(&(*root)->right);
            (*root)->val =(*replace)->val;
            __deleteNode(replace, (*replace)->val);
        }
        else{
            if((*root)->left){
                del = *root;
                *root = (*root)->left;
                free(del);
            }
            else{        
                del = *root;
                *root = (*root)->right;
                free(del);
            }
        }
        return;
    }
    
    if((*root)->val < key){
        __deleteNode(&(*root)->right, key);
    }
    else{
        __deleteNode(&(*root)->left, key);
    }
}

struct TreeNode* deleteNode(struct TreeNode* root, int key){
    __deleteNode(&root, key);
    return root;
}
