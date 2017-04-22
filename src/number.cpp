#include <iostream>
#include "number.hpp"

using namespace std;

Number::Number(){
	firstInNumber=new int[MAX_ARRAY_SIZE];
	lastInNumber=firstInNumber;
}

Number::Number(const Number &copy){
	firstInNumber=new int[MAX_ARRAY_SIZE];
	lastInNumber=firstInNumber+copy.length();
		
	for(int a=0; a<=copy.length(); ++a){
		firstInNumber[a]=copy[a];
	}
		
}

Number::~Number(){
	lastInNumber=0;
	delete []firstInNumber;
}

bool Number::operator==(Number& b){
	if(length()!=b.length())return false;
	
	for(int a=0;a<length();++a)
	{
		if(firstInNumber[a]!=b[a])return false;
	}
	return true;
	
}

bool Number::operator<(Number& b) const{
	if(length()>b.length())return false;
	if(length()<b.length())return true;
	
	for(int a=0;a<=length();++a)
	{
		if(firstInNumber[a]>b[a])return false;
		if(firstInNumber[a]<b[a])return true;
	}
	return false;
	
}

bool Number::operator>(Number& b){
	return !(*this<b); //*****************************
}

bool Number::operator>=(Number& b){
	if(length()>b.length())return true;
	if(length()<b.length())return false;
	
	for(int a=0;a<=length();++a)
	{
		if(firstInNumber[a]>b[a])return true;
		if(firstInNumber[a]<b[a])return false;
	}

	return true;
}

bool Number::operator<=(Number& b){
	if(length()>b.length())return false;
	if(length()<b.length())return true;
	
	for(int a=0;a<=length();++a)
	{
		if(firstInNumber[a]>b[a])return false;
		if(firstInNumber[a]<b[a])return true;
	}

	return true;
}

int& Number::operator[](int index)const{
	return firstInNumber[index];
}

int*& Number::lastPtr(){
	return lastInNumber;
}

int*& Number::firstPtr(){
	return firstInNumber;
}

int Number::length()const{
	return lastInNumber-firstInNumber;
}

void Number::operator=(string str){
	for(char ch: str){
		if(ch<'0' | ch>'9')break;
		*lastInNumber=ch-'0';
		++lastInNumber;
	}
	--lastInNumber;
}

void Number::operator=(Number& b){
	lastInNumber=firstInNumber;
	
	
	for(int a=0; a<=b.length(); ++a)
	{
		firstInNumber[a]=b[a];
		++lastInNumber;
	}
	if(b.length()>=0)--lastInNumber;
}

void Number::operator=(int num){
	lastInNumber=firstInNumber;
		
	while( num > 0 )
	{
		*lastInNumber=num%10;
		++lastInNumber;
		num/=10;
	}
	--lastInNumber;
}

void Number::print(){
	for(int a=0; a<=length(); ++a){
		cout<<firstInNumber[a]<<", ";
	}
	cout<<endl;
}

Number Number::operator+(Number& b){
	Number result;
	
	if(length()!=b.length())
	{	
		if(*this < b)
		{
			result=b+*this; 
			return result;
		}
	}
	
	result[0]=0;

	for(int q=0; q<=length(); ++q)
	{
		if(b.length()-q >= 0)
		{
			result[q]+=(*this)[length()-q]+b[b.length()-q];

		} 
		else
		{
			result[q]+=(*this)[length()-q];
		}
		result[q+1]=0;
		
		if(result[q]>9)
		{
			result[q+1]=result[q]/10;
			result[q]%=10;
		}
		
	++result.lastPtr();	
	}
	if(!*result.lastPtr())
		--result.lastPtr();
	
	return result;
}

Number Number::operator-(Number& b){

	Number result;
	
	if(*this < b)
	{
		result=b-*this;
		*result.lastPtr()*=-1;
		return result;
	} 
	
	result[0]=0;
	
	for(int q=0; q<=length(); ++q)
	{
		
		if(b.length()-q >= 0)
		{
			result[q]+=(*this)[length()-q]-b[b.length()-q];
			
			if(result[q] < 0)
			{
				result[q]+=10;
				result[q+1]=-1;
				
			} 
			else
			{
				result[q+1]=0;
			}
			
		}
		else
		{
			result[q]+=(*this)[length()-q];
			
		}
		
	++result.lastPtr();	
	}
	do{
		if(result.lastPtr()<=result.firstPtr())return result;
		--result.lastPtr();       // depricated shit. Legacy! What if arr is default initialized to zero, moron 
	}while(!*result.lastPtr());
	
	return result;
}

Number Number::operator*(Number& b){
	
	Number result;
	
	if(*this < b)return b*(*this);
	
	result[0];
	int reachedIndex=0;
	
	for(int q=0; q<=b.length(); ++q)
	{
		for(int y=0; y<=length(); ++y)
		{
			if(q+y >= reachedIndex)
			{
				result[q+y]=0;
				++reachedIndex;
				++result.lastPtr();
			}
			result[q+y]+=(*this)[length()-y]*b[b.length()-q];
			if(result[q+y]>9)
			{
				if(q+y+1 >= reachedIndex)
				{
					result[q+y+1]=0;
					++reachedIndex;
					++result.lastPtr();
				}
				result[q+y+1]+=result[q+y]/10;
				result[q+y]%=10;
			}
		}
	}
	
	--result.lastPtr();
	
	return result;
}	

void Number::reverse(Number &num)const{

	for(int a=0; a< (num.length()+1)/2; ++a)
	{
		int tmp=num[a];
		num[a]=num[num.length()-a];
		num[num.length()-a]=tmp;
	}
	
}

Number Number::operator/(Number& b) const{
	
	Number result;
	
	if(*this < b)return result;
	
	Number tmp=*this;
	
	int index=b.length();
	tmp.lastPtr()=tmp.firstPtr()+index;

	while(tmp <= b)
	{
		tmp.lastPtr()+=1;
		++index;
	}
	while(tmp >= b)
	{
		int count=0;

		while( tmp >= b)
		{
			tmp=tmp-b;
			reverse(tmp);
			++count;
		}
		
		result[result.length()]=count;
		
		if(result[result.length()]>9){
			result[result.length()+1]=result[result.length()]%10;
			result[result.length()]/=10;
			++result.lastPtr();
		}
			++result.lastPtr();
		
		while(tmp < b)
		{
			if(length() <= index)break;
			tmp[tmp.length()+1] = (*this)[index + 1]; 
			++index;
			++tmp.lastPtr();
		}
		
	}
	--result.lastPtr();
	return result;
	
}