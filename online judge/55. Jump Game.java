class Solution {
    public boolean canJump(int[] nums) {
        int index = 0;
        //int len = nums.len();
        return Jump(nums,0);
    }
    public boolean Jump(int[] nums,int index) {
    	if(index == nums.length-1) {
    		return true;
    	}
    	else if(nums[index]==0){
    		return false;
    	}
    	else{
    		boolean flag = false;
            int len = nums.length - 1;
            int tmp = nums[index] + index;
            int k = Math.min(len,tmp);
         	//int j = nums.length - nums[index];
    		for(int i = index ;i<=k;i++) {
    			flag =flag || Jump(nums,i);
    		}
    		return flag;
    	}
  
    }
}