#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	
	
	//declaring variables to use when calculating cost
	int insertCost;
	int avlRotationCost;
	int splayCost=0;

	//variable for checking avl tree is balanced or not
    bool is_balanced; 


    //declaring struct node for creating avl and splay tree
	struct Node{
		int data;
		int height;
		struct Node *left;
		struct Node *right;
	}; 
	 
	
	//creating new node struct
	 struct Node* newNode(int data){
		struct Node* newNode = malloc(sizeof(struct Node));
		newNode -> left = NULL;
		newNode -> right = NULL;
		newNode -> data = data;
		newNode -> height = 0;
		return newNode;
	}
	

	//max function for calculating height value
    int max(int a,int b){
        if (a>b)
            return a;
        else return b;
    }
    
    
    //height function return height value of the node
      int height(struct Node *a){
		if (a==NULL)
		 return -1;
		 else 
		 return a->height;
	}	



   //function for checking balance factor of avl-tree
	int checkbalance(struct Node* root){
     if(root!=NULL){	 
     

         int right = height(root -> right);
         int left = height(root -> left);
    	
		
            if ( abs(right - left) > 1){
             is_balanced = false;
        
                }
    
        return (left-right);  
}
    }
     
     //that function checking tree is balanced or not for avl-tree
     bool isBalanced(struct Node* root){
	  is_balanced=true;
      checkbalance(root);
    printf("%s", is_balanced ? "Avl-Tree is balanced\n\n" : "Error! Tree is not balanced\n\n");
    
    return is_balanced;
    }



   // rotate left function which is used both avl and splay tree
    struct Node *leftRotation(struct Node *a){
    
    	struct Node *y = a->right;
    	struct Node *temp = y->left;
    	
    	y->left = a;
    	a->right= temp;
    	
		//calculating new height values 
    	a-> height = 1 + max(height(a->left),height(a->right));
    	y->height= 1 + max(height(y->left),height(y->right));

    	return y;
	}
    
    
      //rotate rþght function which is used both avl and splay tree
	    struct Node *rightRotation(struct Node *a){

	  
    	struct Node *y = a->left;
    	struct Node *temp = y->right;
    
    	y->right = a;
    	a->left= temp;
    	
    	//calculating new height values 
    	a-> height = max(height(a->left),height(a->right)) +1;
    	y->height=  max(height(y->left), height(y->right)) +1;
  
    	return y;
	}
	
	
	
	//creating the tree that conforms to the avl tree properties with the inserted key.
    struct Node *checkAvlProperty(struct Node *a, int key){
    	
		//checking the balance value by calling the a function
    		int balance = checkbalance(a);
  		// calculating new height value because new node is inserted
	  a-> height = 1 + max(height(a->left),height(a->right));
	  
		
	//if the left part of the tree is larger than the right
		if(balance>1){
		 // single right rotation and increase cost value
			if(key < a->left->data){
					avlRotationCost=avlRotationCost + 1;
		    return rightRotation(a); 
	}
		//double rotation  left-right and increase cost value
		if(key > a->left->data){
				avlRotationCost = avlRotationCost + 2;
		 
			 a->left = leftRotation(a->left);
			 return rightRotation(a);
	}
	
			}
			
		//if the right part of the tree is larger than the left
		 if (balance < -1){
		 
		 	    // single left rotation and increase cost value
			if(key > a->right->data){
			 	avlRotationCost = avlRotationCost + 1;
			return leftRotation(a);
		}
			//double rotation  right-left  and increase cost value
			if(key < a->right->data){
				
			avlRotationCost = avlRotationCost + 2;
			a->right= rightRotation(a->right);
			return leftRotation(a);
			}
		}		
 		return a;
			  	
	}


	//inserting method for avl-tree.it inserting key like binary search tree after that calling avl-property function.
	struct Node *insertAvl(struct Node *a, int key){
		if(a == NULL){
			 			 return (newNode(key));	 		 

	}
				 		 
		if (key > a->data){
			
	    	insertCost=insertCost+1;
		    a->right =	insertAvl(a -> right,key);
				   	 }
					 
		else if (key <  a->data){
			
     	  	insertCost=insertCost+1;
    		a->left = insertAvl(a->left,key);
 
	}
	 //if it is equal 
		else {
			
			insertCost=insertCost+1;
			return a;	
		}	
		     			 
	  checkAvlProperty(a,key);
		 		
	}
	
	

//creating the tree that conforms to the splay tree properties with the inserted key.
	struct Node *checkSplay(struct Node *root, int key) {
 
   if(root==NULL ){
   	return root;
   }
   //if the key is to the left of the tree
   if (key < root->data) {
    	
    //zig-zig operation with calling rotation functions and increase cost value
        if (key < root->left->data){
    		splayCost = splayCost + 1;
    	root = rightRotation(root);
     	}
  //zig-zag	operation with calling rotation functions and increase cost value
      	else if (key> root->left->data) {
 		   splayCost = splayCost + 2;
 		  root->left=rightRotation(root->left);
 	    	root=leftRotation(root);
        }
	 
        else
  //zig if the key has no children and is a child of root
     	 
           if (root -> height== 0) 
	    	return  root;
		   else 
		   	splayCost = splayCost + 1;
		   return rightRotation(root);
  
}


     //if the key is to the right of the tree
   else if(key > root->data) {
  	  
   	//zag-zag operation with calling rotation functions and increase cost value
         if (key > root->right->data){
	    	splayCost = splayCost + 1;
        	root = leftRotation(root);
	
  }
        //zag-zig operation with calling rotation functions and increase cost value
     	else if  (key < root->right->data) {
          	splayCost = splayCost + 2;
     	    root->right = leftRotation(root->right);
 	    	root =rightRotation(root);
    }


  //zag  if the key has no children and is a child of root
        else
		 	
            if(root -> height == 0)
		      return root;
		    else 
		    	splayCost = splayCost + 1;
		    	return leftRotation(root);
    }
    else //if it already conforms to the splay tree with inserted key
    return root;
  }
  

	

	//inserting method for splay-tree.it inserting key like binary search tree after that calling splay function.
	struct Node *insertSplay(struct Node *a, int key){
		//if root is null inserting key
		if(a == NULL){
			 a = newNode(key);	   	
	}
					 		 

	   	if (key > a->data){
	       	splayCost = splayCost + 1;
		    a->right = insertSplay(a -> right,key);
				   	 }
					 
		else if (key <  a->data){
			splayCost = splayCost + 1;
		    a->left = insertSplay(a->left,key);
	 }
	 //if it is equal 
		else {
		 	splayCost = splayCost + 1;

		}
		// calculating new height value because new node is inserted
		   a-> height = 1 + max(height(a->left),height(a->right));	
		   	  	  
	  checkSplay(a,key);
		 		
	}
	
		
	//preorder traversal printing function
	void printList(struct Node *node){
		if( node == NULL)
		return;
		printf("%d ", node -> data);
		printList(node -> left);
		printList(node -> right);}
		


int main(int argc, char *argv[]) {
	
		struct Node *avlTree = NULL;
        struct SplayNode *splayTree = NULL;
  		char str[20];
  		
  		
  	/*	I used this part of the code while writing the report. it creates avl and splay tree with given the number of nodes, also keys created randomly.
  		int k=1;
  		
  		int numberOfNodes;
  		
  		scanf("%d",&numberOfNodes);

  		
  		for(k;k<=numberOfNodes;k++){
  			int a=rand();	
  		avlTree = insertAvl(avlTree,a);
  		splayTree = insertSplay(splayTree,a);
  		
		  }
  		
  		int TotalCost = insertCost+avlRotationCost;
  			printf("%d \n",TotalCost);
  		
  			printf("%d \n",splayCost);
  	*/	
  		
  		
  	printf("Please enter the input file name: ");
  		
    	scanf("%s",str);
       FILE* file = fopen (str, "r");
       int i = 0;
 
   fscanf (file, "%d", &i);    
   while (!feof (file)) {  
	  
		
		avlTree= insertAvl(avlTree,i);
    	splayTree = insertSplay(splayTree,i);
    	     
    	     
      fscanf (file, "%d", &i); 
	        
    }
  fclose (file);  
   	
   	
    printf("Avl-Tree:\n");
    
       printList(avlTree);
      
	int TotalCost = insertCost+avlRotationCost;
	printf("\nTotal cost=%d \n",TotalCost);
		
	 isBalanced(avlTree);
	  printf("Splay-Tree:\n");
	 printList(splayTree);
     	printf("\nTotal cost=%d \n",splayCost);

	return 0;

	
}
