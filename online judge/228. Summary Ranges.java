package problem;

import java.util.ArrayList;
import java.util.List;

public class solution {
	public static void main(String args[]) {
		int[] nums = {};
		System.out.println("HHHHHHHHHHHHHHHHHHH");
		List<String> res = summaryRanges(nums);
		System.out.println("tttt");
		for(int i = 0 ;i<res.size();i++) {
			System.out.println("**************");
			Object obj = res.get(i);
			if(obj instanceof String) {
				System.out.println((String)obj);
			}
		}
		
	}
	public static List<String> summaryRanges(int[] nums) {
		
		int begin = 0;
		int end = 0;
		List<String> res = new ArrayList();
		if(nums.length == 0) {
			return res;
		}
		//System.out.print("length" + nums.length);
		for(int cur = 1 ; cur < nums.length ; cur++ ) {
			//System.out.println("the begin is " + begin + " the end is " + end);
			if(nums[cur]==nums[end]+1) {
				end = cur;
			}
			else {
				if(begin == end) {
					String tmp = new String();
					tmp = tmp + String.valueOf(nums[begin]);
					begin = cur;
					end = cur;
					res.add(tmp);
				}
				else {
					String tmp = new String();
					tmp = tmp + String.valueOf(nums[begin]);
					tmp = tmp + "->";
					tmp = tmp + String.valueOf(nums[end]);
					begin = cur;
					end = cur;
					res.add(tmp);
					
				}
			}
		}
		if(begin == end) {
			String tmp = new String();
			tmp = tmp + String.valueOf(nums[begin]);
			res.add(tmp);
		}
		else {
			String tmp = new String();
			tmp = tmp + String.valueOf(nums[begin]);
			tmp = tmp + "->";
			tmp = tmp + String.valueOf(nums[end]);
			res.add(tmp);
			
		}
		return res;
	}

}
