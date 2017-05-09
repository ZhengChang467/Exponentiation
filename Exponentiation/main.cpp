/*
Problems involving the computation of exact values of very large magnitude and precision are common.
 For example, the computation of the national debt is a taxing experience for many computer systems.
This problem requires that you write a program to compute the exact value of Rn where R is a real number
( 0.0 < R < 99.999 ) and n is an integer such that 0 < n <= 25.
*/
#include <iostream>
#include<string>
#include<stack>
#include<algorithm>
#include<math.h>
using namespace std;
string finalout;
string add(string a,string b)
{
    stack<char> result,p1,p2;
    for(int i=0; i<a.size(); i++)
    {
        p1.push(a[i]);
    }
    for(int i=0; i<b.size(); i++)
    {
        p2.push(b[i]);
    }
    int carry=0;
    for(int i=1; i<=max(a.size(),b.size()); i++)
    {
        if(p1.empty()!=true&&p2.empty()!=true)
        {
            result.push((p1.top()-'0'+p2.top()-'0'+carry)%10+'0');
            carry=(p1.top()-'0'+p2.top()-'0'+carry)/10;
            p1.pop();
            p2.pop();
        }
        if(p1.empty()==true&&p2.empty()==false)
        {
            result.push((p2.top()-'0'+carry)%10+'0');
            carry=(p2.top()-'0'+carry)/10;
            p2.pop();
        }
        if(p2.empty()==true&&p1.empty()==false)
        {
            result.push((p1.top()-'0'+carry)%10+'0');
            carry=(p1.top()-'0'+carry)/10;
            p1.pop();
        }
    }
    if(carry!=0)
        result.push(carry+'0');
    string out;
    for(int i=0; !result.empty(); i++)
    {
        out+=result.top();
        result.pop();
    }
    return out;
}
string multipy(string a,string b)
{
    string submultipy="0",out="0";
    stack<char> p;
    for(int i=0; i<b.size(); i++)
        p.push(b[i]);
    for(int i=0; i<b.size(); i++)
    {
        submultipy="0";
        for(int j=0; j<p.top()-'0'; j++)
        {
            submultipy=add(submultipy,a);
        }
        for(int j=0; j<i; j++)
        {
            submultipy+='0';
        }
        out=add(out,submultipy);
        p.pop();
    }
    return out;
}
int main()
{
    string s;
    int n,point_index,zero_index,point_num;
    while(cin>>s>>n)
    {
        point_index=0;
        zero_index=0;
        point_num=0;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]=='.')
            {
                point_index=i;
            }
        }
        point_num=s.size()-point_index-1;
        if(point_index!=0)
        s.erase(point_index,1);
        for(int i=1; i<=s.size(); i++)
        {
            if(s[i-1]=='0')
            {
                zero_index=i;
            }
            else
                break;
        }
        s.erase(0,zero_index);
        string temp=s;
        for(int i=0;i<n-1;i++)
            s=multipy(s,temp);
        point_num*=n;
        int add_zero=0;
        if(s.size()<=point_num){
            add_zero=point_num-s.size();
            for(int i=0;i<add_zero;i++){
                s='0'+s;
            }
            s='.'+s;
            while(s[s.size()-1]=='0'||s[s.size()-1]=='.'){
                s.erase(s.size()-1,1);
            }
            if(s.empty()) s="0";
        }
        else if(point_index!=0){
            s.insert(s.size()-point_num,".");
            while(s[s.size()-1]=='0'){
                s.erase(s.size()-1,1);
            }
            if(s[s.size()-1]=='.')
                s.erase(s.size()-1,1);
        }
        cout<<s<<endl;
    }
    return 0;
}
