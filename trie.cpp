
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
    //comment out maxNo calculation if not required
    //check if it works without overchecking in else condition 
    //Reduce the number of digits

    int arr[45];
    int numarr[45];
    long long maxNo = 0; 
    long long returnNumber = 0;
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
        maxNo = maxNo + pow(2,i); 
        returnNumber = returnNumber +pow(2,i);    
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
        returnNumber = returnNumber +pow(2,i); 
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
     
     
    return returnNumber;

    
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
    
    
    return 0; 
}