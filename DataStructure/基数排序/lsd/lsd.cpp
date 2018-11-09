#include <iostream>
#include <string.h>

void LSD (int length,int *a);
using namespace std;

int main()
{
    int a[]={10,8,89,7,9,5,73,33,664};
    LSD(9,a);
    return 0;
}

void LSD(int length,int *a){
    int maxVal=0,digitpos=1;
    int pass=1;
    int bucket[length],count[10];
    memset(bucket,0,sizeof(bucket));
    //find the max number
    for(int i=0;i<length;i++){
        if(a[i]>maxVal) maxVal=a[i];
    }
    cout<<maxVal<<endl;
    //if not arrival the max index
    while(maxVal/digitpos>0){
        memset(count,0,sizeof(count));
        //the count of number
        for(int i=0;i<length;i++){
            count[(a[i]/digitpos)%10]++;
        }
        //caculate the index
        for(int i=1;i<10;i++){
            count[i]+=count[i-1];
        }
        //put number into the bucket
        for(int i=length-1;i>=0;i--){
            count[a[i]/digitpos%10]--;
            bucket[count[(a[i]/digitpos)%10]]=a[i];
        }
        //let a get the number in the bucket
        for(int i=0;i<length;i++){
            a[i]=bucket[i];
        }
        //find the larger index
        digitpos=digitpos*10;
        cout<<pass++<<":";
        for(int i=0;i<length;i++) cout<<a[i]<<"  ";
        cout<<endl;
    }
}

