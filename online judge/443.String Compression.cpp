class Solution {
public:
    int compress(vector<char>& chars) {
        sort(chars.begin(),chars.end());
        int repeat=1;
        int index=0;
        int size=chars.size();
        for(int i=1;i<size;i++){
            if(chars[i]==chars[i-1] ){
                repeat++;
                
            }
            else{
                if(repeat==0){
                    chars[index]=chars[i-1];
                    index++;
                }
                else{
                    chars[index]=chars[i-1];
                    index++;
                    chars[index]=repeat+'0';
                    index++;
                    repeat=1;
                }
            }
        }
        if(chars[size-1]==chars[size-2]){
            
            
        }
        return index;
        
    }
};