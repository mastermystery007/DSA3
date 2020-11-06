
#include<bits/stdc++.h> 
using namespace std; 
 
class TrieNode 
{ 
    public:
    TrieNode * left;
    TrieNode * right;    
}; 

 
void insert(TrieNode *root,long long val); 
int findMaxVal(TrieNode* root,long long val);



int findMaxVal(TrieNode* root,long long val)
{
    int arr[45];
    int numarr[45];
    int maxNo = 0; 
    TrieNode* curr = root;
    
    for(int i=44;i>=0;i--)
    {
    if((val>>i)&1==1){arr[i]=1;}else{arr[i]=0;}
    }
    

    
    for(int i=44;i>=0;i--)
    {
    
    if(arr[i]==0)
    {
        

        if(curr->right)
        {
        numarr[i]=1;
        maxNo=maxNo+pow(2,i);    
        curr= curr->right;
        }
        else //if(curr->left)
        {
        numarr[i] = 0; 
        curr=curr->left;
        }
    
    }
    else
    {
        
        if(curr->left)
        {
        numarr[i]=0;    
        curr=curr->left;
        
        }
        else //if(curr->right)
        {
        numarr[i]=1;   
        maxNo=maxNo+pow(2,i);    
        curr=curr->right; 
        }
    
    }
    }
     
     
    return maxNo;

    
}


void insert(TrieNode *root,long long val) 
{ 
    TrieNode * current = root;

    for(int i=44;i>=0;i--)
    {
        
        if(((val>>i)&1) == 1)
        {
            if(current->right==NULL)
            {
                TrieNode * temp  = new TrieNode();
                current->right = temp;
                current = current->right;
                
            }

            else
            {
            current = current->right;
            }
            

        }
        else if(((val>>i)&1) == 0)
        {
            if(current->left == NULL)
            {
                TrieNode * temp  = new TrieNode();
                current->left = temp;
                current = current->left;
            }

            else{current = current->left;}
            
        }
    }

} 



int main() 
{ 
    int N,q;
    cin>>N>>q;
    TrieNode * tn = new TrieNode();


    for(int i=0;i<N;i++)
    {
        long long num;
        cin>>num;
        insert(tn,num);

    }
    for(int i=0;i<q;i++)
    {
    long long query;    
    cin>>query;
    long long max = findMaxVal(tn,query);
    cout<<"\n"<<max;
    }
    
    //insert(tn,1024);
    
   /*
    insert(tn,100);
    insert(tn,128);
    insert(tn,25);
    insert(tn,32);
    cout<<"\n";
    insert(tn,32);
    cout<<"\n";
    insert(tn,5);
    cout<<"\n";
    insert(tn,2);
    cout<<"\n";
    insert(tn,1);
    cout<<"\n";
    insert(tn,1024);
    insert(tn,24);
      cout<<"\n";*/
   
    //showFormation(tn);
    return 0; 
}