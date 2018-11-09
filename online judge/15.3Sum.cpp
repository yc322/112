class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int num=nums.size();
        sort(nums.begin(),nums.end());
        for(int i=0;i<num-2;i++){
            if(i==0 || nums[i]>nums[i-1]){
            
                int head=i+1;
                int rear=num-1;
                while(head < rear){
                    int tmp=nums[i]+nums[head]+nums[rear];
                    if(tmp>0) rear-
                        -;
                    else if(tmp<0) head++;
                    else{
                        res.push_back({nums[i],nums[head],nums[rear]});
                        
                        while(nums[head]==nums[head+1] && head < rear){
                            head++;
                        }
                        while(nums[rear]==nums[rear-1] && head < rear){
                            rear--;
                        }
                        head++,rear--;
                    }
                }
            }
        }
        return res;
    }
};