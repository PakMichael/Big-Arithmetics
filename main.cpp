#include <iostream>
#include <cstring>

using namespace std;

const int MAX_ARRAY_SIZE=256;
const unsigned MAX_INT_SIZE=-1;  
char MAX_INT_STRING[]="4294967295"; //Should be const??

char* add(char* aBeg, char *aEnd, char* bBeg, char* bEnd, char* pointerToLast);
char* subtract(char* aBeg, char *aEnd, char* bBeg, char* bEnd, char* pointerToLast);
char* divide(char* aBeg, char* aEnd, char* bBeg, char* bEnd, char* pointerToLast);
char* bigDivision(char* aBeg, char* aEnd, char* bBeg, char* bEnd, char* pointerToLast);
char* getOperatorIndex(char* equationString);
bool isOperator(int characterDec);
void printArray(char* resultBeg, char* pointerToLast);
char* normalizeAddition(char* resultBeg, char* pointerToLast);
void reverseArr(char* arrBeg, char* arrEnd);
void restoreForm(char* pointer, char* end);
void rewrite(char* aBeg, char* aEnd, char* bBeg, char* bEnd);
char* numberToArray(int number, char* arr);
bool additionOK();
bool subtractionOK();

int main(){
	char equationArray[MAX_ARRAY_SIZE*2+1];  // operandA(<=256) operator(1) operandB(<=256)
	char result[MAX_ARRAY_SIZE];
	char* pointerToLast=result; //always point to LAST element of the result array
	char* operatorPtr;
	char* endPtr;

	// if(!additionOK())return -1;
	// if(!subtractionOK())return -1;
	cin>>equationArray;
	operatorPtr=getOperatorIndex(equationArray);
	endPtr=(operatorPtr+1)+strlen(operatorPtr+1);  

switch(*operatorPtr){
	case 43:
		pointerToLast=add(equationArray, operatorPtr-1, operatorPtr+1, endPtr-1, pointerToLast); 
		pointerToLast=normalizeAddition(result, pointerToLast); //outdated?
		break;
	case 45:
		pointerToLast=subtract(equationArray,operatorPtr-1,operatorPtr+1,endPtr-1, pointerToLast);
		break;
	case 47:
		pointerToLast=divide(equationArray,operatorPtr-1,operatorPtr+1,endPtr-1, pointerToLast);
		break;
}
	printArray(result, pointerToLast);
	system("pause");
};

char* add(char* aBeg, char *aEnd, char* bBeg, char* bEnd, char* pointerToLast){
	int aLength=aEnd-aBeg;
	int bLength=bEnd-bBeg;
	if(aLength<bLength){
		pointerToLast=add(bBeg,bEnd,aBeg,aEnd, pointerToLast); 
		return pointerToLast;
	}
		
	do{
		*pointerToLast=*aEnd+*bEnd-96;
		--aEnd;
		--bEnd;
		++pointerToLast;
	}while(bEnd>=bBeg);
	while(aEnd>=aBeg){
		*pointerToLast=*aEnd-48;
		--aEnd;
		++pointerToLast;
	}
	return --pointerToLast;
}

char* getOperatorIndex(char *equationString){
	while(!isOperator(*++equationString));   
	return equationString;
}
 
bool isOperator(int characterDec){
	if(characterDec>47)return false;
	
	switch(characterDec){
		case 42:       
			// '*' assumed multiplication
			return true;
		case 43:
			// '+' assumed addition
			return true;
		case 45:
			// '-' assumed subtraction
			return true;
		case 47:
			// '/' assumed division
			return true;
	}
	return false;
}

void printArray(char* resultBeg, char* pointerToLast){
	//stats one past the last elem, so --pointerToLast accounts for that
	while(pointerToLast>=resultBeg){
		cout<<(int)*pointerToLast<<" ";
		--pointerToLast;
	}
	cout<<endl;
	
}


char* normalizeAddition(char* resultBeg, char* pointerToLast){
	while(resultBeg<=pointerToLast){
		if(*resultBeg>9){
			if(resultBeg==pointerToLast){
				++pointerToLast;
				*pointerToLast=0;
			}
			*(resultBeg+1)+=*resultBeg/10;
			*resultBeg%=10;
		}
		++resultBeg;
	}
	return pointerToLast;
	
}
 

char* subtract(char* aBeg, char *aEnd, char* bBeg, char* bEnd, char* pointerToLast){
	// aBeg is beginning of the string, 
	// aEnd is pointerToOperator-1,
	//	bBeg=pointerToOperator+1,
	//  bEnd is '\0' of string-1
	int aLength=aEnd-aBeg;
	int bLength=bEnd-bBeg;
	char* firstPtr=pointerToLast;
	/*
	* Assure that A is bigger than B, 
	* if numbers equal make A the number with bigger [0] value
	*/
	if(aLength<bLength){
		pointerToLast=subtract(bBeg,bEnd,aBeg,aEnd, pointerToLast);
		*pointerToLast*=-1;
		return pointerToLast;
	}else if(aLength==bLength)
		if(*aBeg<*bBeg){
			pointerToLast=subtract(bBeg,bEnd,aBeg,aEnd, pointerToLast);
			*pointerToLast*=-1;
			return pointerToLast;
	}
	int aPrev=*aEnd;

	do{
		int a=aPrev;
		--aEnd;		
		aPrev=*aEnd;
		if(a<*bEnd){
			a+=10;
			--aPrev;
		}
		*pointerToLast=a-*bEnd;
		++pointerToLast;
		--bEnd;
	}while(bEnd>=bBeg); 
	aPrev-=48;
	// --aEnd;
	while(aEnd>=aBeg){
		if(aPrev<0){
			aPrev+=10;
			--*(aEnd-1);
		}
		*pointerToLast=aPrev;
		--aEnd;
		aPrev=*aEnd-48;
		++pointerToLast;
	}		
	//pointerToLast will otherwise point one past last element
	--pointerToLast;
	while(!*pointerToLast){
		if(pointerToLast==firstPtr)
		break; //remove zeros
		--pointerToLast;
	}
	return pointerToLast;
}


char* divide(char* aBeg, char* aEnd,char* bBeg, char* bEnd, char* pointerToLast){
 
	return bigDivision(aBeg, aEnd, bBeg, bEnd, pointerToLast);
 
	
}

char* bigDivision(char* aBeg, char* aEnd,char* bBeg, char* bEnd, char* pointerToLast){
		 
		

	return nullptr;

}


void reverseArr(char *arrBeg, char *arrEnd){
	int length=(arrEnd-arrBeg+1)/2;
	do{
		char tmp=*arrBeg;
		*arrBeg=*arrEnd;
		*arrEnd=tmp;
		++arrBeg;
		--arrEnd;
		--length;
	}while(length);
}

void restoreForm(char* pointer, char* end){
	do{
		*pointer+=48;
		++pointer;
	}while(pointer<=end);
}

void rewrite(char* aBeg, char* aEnd, char* bBeg, char* bEnd){
	do{
		*bEnd=*aEnd;
		--bEnd;
		--aEnd;
	}while(aEnd>=aBeg);
}

char* numberToArray(int number, char* arr){
	do{
	*arr=number%10;
	number/=10;
	++arr;
	}while(number>0);
	return --arr;
}

bool additionOK(){
	cout<<"PASSING ADDITION TEST...";
	
	char res[MAX_ARRAY_SIZE];
	char* eq[][2]={
		{"1234+9876","11110"},
		{"9876+1234", "11110"},
		{"12345+9876","22221"},
		{"98765+1234", "99999"}
	};
	for(int i=0;i<4;++i){
		char* operatorPtr=getOperatorIndex(eq[i][0]);
		char* pointerToLast=res;
		char* endPtr=(operatorPtr+1)+strlen(operatorPtr+1);  
		pointerToLast=add(eq[i][0], operatorPtr-1, operatorPtr+1, endPtr-1, pointerToLast); 
		pointerToLast=normalizeAddition(res, pointerToLast); //outdated?
		int index=0;
		while(pointerToLast>res){
			if(*pointerToLast!=eq[i][1][index]-48){
				cout<<endl;
				cout<<"--------Addition-Test-Fail-------------------"<<endl;
				cout<<"Predefined expr nr."<<i<<"->"<<eq[i][1]<<endl;
				cout<<"Result for ["<<i<<"]->";
				printArray(res,pointerToLast);
				cout<<endl;
			cout<<"At pointerToLast="<<(int)*pointerToLast<<", eq["<<i<<"][1]["<<index<<"]="<<(int)eq[i][1][index]<<endl;
				cout<<"---------------------------------------------"<<endl;
				return false;
				}
			--pointerToLast;
			++index;
		}
	}
		cout<<"OK"<<endl;
	return true;
	
}
bool subtractionOK(){
	cout<<"PASSING SUBTRATCION TEST...";
	
	char res[MAX_ARRAY_SIZE];
	char* eq[][2]={
		{"1234-9876","-8642"},
		{"9876-1234", "8642"},
		{"12345-9876","2469"},
		{"98765-1234", "97531"},
		{"10000-10000","0"},
		{"10000-9990","10"}
	};
	for(int i=0;i<4;++i){
		char* operatorPtr=getOperatorIndex(eq[i][0]);
		char* pointerToLast=res;
		char* endPtr=(operatorPtr+1)+strlen(operatorPtr+1);  
		pointerToLast=subtract(eq[i][0], operatorPtr-1, operatorPtr+1, endPtr-1, pointerToLast); 
		pointerToLast=normalizeAddition(res, pointerToLast); //outdated?
		int index=0;
		while(pointerToLast>res){
		if(eq[i][1][index]=='-'){
			*pointerToLast*=-1;
			++index;
			continue;
			}
			if(*pointerToLast!=eq[i][1][index]-48){
				cout<<endl;
				cout<<"--------Subtraction-Test-Fail----------------"<<endl;
				cout<<"Predefined expr nr."<<i<<"->"<<eq[i][1]<<endl;
				cout<<"Result for ["<<i<<"]->";
				printArray(res,pointerToLast);
				cout<<endl;
			cout<<"At pointerToLast="<<(int)*pointerToLast<<", eq["<<i<<"][1]["<<index<<"]="<<(int)eq[i][1][index]<<endl;
				cout<<"---------------------------------------------"<<endl;
				return false;
				}
			--pointerToLast;
			++index;
		}
	}
		cout<<"OK"<<endl;
	return true;
	
}


