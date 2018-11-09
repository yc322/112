class Solution {
public:
    int maxArea(vector<int>& height) {
    	int max=0,area,len,hr,hl;
    	len=height.size()-1;
    	int r=len,l=0;
    	while(l<r){
    		hl=height.at(l);
    		hr=height.at(r);
    		if(hl<hr){
    			area=hl*len;
    			l++;
    		}else{
    			area=hr*len;
    			r--;
    		}
    		if(area>max) max=area;
    		len--;
    	}
    	return max;
        
    }
};