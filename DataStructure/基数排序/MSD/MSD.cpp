#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;
void MSD(int start,int end,int *a,int d);
int findMax(int *a,int length);
int getdigit(int d,int a);

int main()
{
    int num,a[100];
    cout<<"please input the size of number:";
    cin>>num;
    for(int i=0;i<num;i++) cin>>a[i];
    int d=findMax(a,num);
    cout<<"d"<<d<<endl;
    cout<<endl;
    MSD(0,num-1,a,d);
    cout<<"the final result:"<<endl;
    for(int i=0;i<num;i++) cout<<a[i]<<"  ";
    return 0;
}

int findMax(int *a,int length){
    int max=-1;
    //find the largest number
    for(int i=0;i<length;i++){
        if(a[i]>max) max=a[i];
    }
    //caculate the max digit
    int count=0;
    while(max>0){
        max=max/10;
        count++;
    }
    return count;
}

int getdigit(int d,int a){
    //return the number which index is d
    return (a/(int)pow(10,d-1))%10;
}

void MSD(int start,int end,int *a,int d){
    int count[10];
    memset(count,0,sizeof(count));
    int *bucket=new int(sizeof(int)*(end-start+1));
    //Count the number of elements that need to be installed in each bucket
    for(int i=start;i<=end;i++) cout<<getdigit(d,a[i])<<" ";

    for(int i=start;i<=end;i++){
        count[getdigit(d,a[i])]++;
    }
    cout<<"count"<<endl;
    for(int i=0;i<10;i++) cout<<count[i]<<" ";
    //���Ͱ�ı߽�������count[i]ֵΪ��i��Ͱ���ұ߽�����+1
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    //keep the balance
    for(int i=end;i>=start;i--){
        int j=getdigit(d,a[i]);
        bucket[count[j]-1]=a[i];//�����Ӧ��Ͱ�У�count[j]-1�ǵ�j��Ͱ���ұ߽�����
        --count[j];
    }
    cout<<" bucket:"<<endl;
    for(int i=0;i<end-start;i++) cout<<bucket[i]<<" ";
    cout<<endl<<endl;
    //count[i]�ǵ�i��Ͱ�ı߽�
    for(int i=start,j=0;i<=end;i++,j++){
        a[i]=bucket[j];
    }
    //cout<<"start"<<start<<"end"<<end<<endl;
    //for(int i=start;i<=end;i++) cout<<a[i]<<" ";
    cout<<endl;
    delete bucket;
    //for(int i=0;i<10;i++) cout<<count[i]<<" ";
    for(int i=0;i<10;i++){
        int p1=start+count[i];
        int p2=start+count[i+1]-1; //��i��Ͱ���ұ߽�
        if(p1<p2 && d>1) MSD(p1,p2,a,d-1);
    }
}
