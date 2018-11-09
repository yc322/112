#include <iostream>
#include <map>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;
void FindSpecialValue();
void AssociativeArray();
void MultiMapAsDict();
int main()
{

   AssociativeArray();
   MultiMapAsDict();
   FindSpecialValue();
}

void input()
{

}

void AssociativeArray()
{
    typedef map<string,int> StrIntMap;

    StrIntMap Maps;
    Maps.insert(StrIntMap::value_type("hello",21));
    Maps["jin"]=27;
    Maps["temp"]=99;
    StrIntMap::iterator pos;
    //print all elements
    Maps.insert(StrIntMap::value_type("hello",27));
    for(pos=Maps.begin();pos!=Maps.end();pos++){
        cout<<"Stock"<<pos->first<<" ";
        cout<<"price"<<pos->second<<" "<<endl;
    }
    Maps["kin"]=Maps["tin"];
    if(Maps.erase("jin")>=1){
        cout<<"rename success"<<endl;
    }
    for(pos=Maps.begin();pos!=Maps.end();pos++){
        cout<<"Stock"<<pos->first<<" ";
        cout<<"price"<<pos->second<<" "<<endl;
    }
}

void MultiMapAsDict()
{
    cout<<"*****************"<<endl;
    typedef multimap<string,string> StrStrMultiMap;
    StrStrMultiMap MultimapDict;
    MultimapDict.insert(make_pair("day","tag"));
    MultimapDict.insert(make_pair("strange", "fremd"));
	MultimapDict.insert(make_pair("car","Auto"));
	MultimapDict.insert(make_pair("smart","elegant"));
	MultimapDict.insert(make_pair("trait","Merkmal"));
	MultimapDict.insert(make_pair("strange","seltsam"));
	MultimapDict.insert(make_pair("smart","klug"));
	MultimapDict.insert(make_pair("smart","raffiniert"));
	MultimapDict.insert(make_pair("clever","raffiniert"));

	cout.setf(ios::left, ios::adjustfield);
	cout << ' ' << setw(10) << "english "
		 << "german " <<endl;
	cout << setfill('-') << setw(20) <<""
		 << setfill(' ') << endl;

    //print all element
    StrStrMultiMap::iterator pos;
	for (pos = MultimapDict.begin(); pos != MultimapDict.end(); ++pos)
	{
		cout << ' ' << setw(10) << pos->first.c_str()
			 << pos->second << endl;
	}
	cout << endl;

	//print all vaules for key "smart"
	string strKey("smart");
	cout << strKey << ":" << endl;
	for (pos = MultimapDict.lower_bound(strKey); pos != MultimapDict.upper_bound(strKey);++pos)
	{
		cout << "\t" << pos->second << endl;
	}
	cout << endl;

    //print all keys for value is "raffiniert"
	string strValue("raffiniert");
	cout << strValue << ":" <<endl;

	for (pos = MultimapDict.begin(); pos != MultimapDict.end();++pos)
	{
		if (pos->second == strValue)
		{
			cout << " " << pos->first << endl;
		}
	}
}


/*
template <class K,class V>
class CValueEqual
{
private:
	V value;
public:
	CValueEqual(const V &v):value(v)
	{
		cout << "constructor is initial" <<endl;
	}
	bool operator()(pair<const K, V> elem)
	{
		return elem.second == value;
	}
};*/



bool EqualValue(pair<const float, float> elem)
{
	if (elem.second == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/****************************************************
*函数名称：FindSpecialValue
*功    能：查找具有指定值的元素
*作    者：Jin
*日    期：2016年5月24日
****************************************************/
void FindSpecialValue()
{
	typedef map<float, float> FloatFloatMap;
	FloatFloatMap fMap;
	FloatFloatMap::iterator pos;

	//fill map
	fMap[1] = 7;
	fMap[2] = 4;
	fMap[3] = 2;
	fMap[4] = 3;
	fMap[5] = 6;
	fMap[6] = 1;
	fMap[7] = 3;

	//find element with key 3.0
	pos = fMap.find(3.0);
	if (pos != fMap.end())
	{
		cout << pos->first << ":"
			 << pos->second << endl;
	}
	else
	{
		cout << "do not find  element with key 3" << endl;
	}
	//find element with value 3.0
	//pos = find_if(fMap.begin(), fMap.end(), CValueEqual<float, float>(3.0));//方式一
	pos = find_if(fMap.begin(), fMap.end(), EqualValue);//方式二
	if (pos != fMap.end())
	{
		cout << pos->first << ":"
			<< pos->second << endl;
	}
	else
	{
		cout << "do not find element with value 3" << endl;
	}
}
