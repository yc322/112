/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
    	int num=0;
    	int len=G.size();
    	ListNode *curr=head;
    	bool ret,post_ret;
    	post_ret=find(G.begin(),G.end(),curr->val)!=G.end();
    	curr=curr->next;
        while(curr){
        	ret=find(G.begin(),G.end(),curr->val)!=G.end();
        	if(ret && post_ret) num++;
        	curr=curr->next;
        	post_ret=ret;
        }
        return len-num;

        
    }
};