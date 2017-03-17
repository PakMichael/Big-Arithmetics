#include <iostream>
#include <cstring>

using namespace std;

const int MAX_ARRAY_SIZE=256;
const unsigned MAX_INT_SIZE=-1;  
char MAX_INT_STRING[]="4294967295"; //Should be const??

char* add(const char* aBeg, const char *aEnd, const char* bBeg,const char* bEnd, char* pointerToLast);
char* subtract(const char* aBeg, const char *aEnd, const char* bBeg, const char* bEnd, char* pointerToLast);
char* divide(char* aBeg, char* aEnd, char* bBeg, char* bEnd, char* pointerToLast);
char* bigDivision(const char* aBeg, const char* aEnd, const char* bBeg, const char* bEnd, char* pointerToLast);
char* getOperatorIndex(char* equationString);
bool isOperator(int characterDec);
void printArray(const char* resultBeg,const char* pointerToLast);
char* normalizeAddition(char* resultBeg, char* pointerToLast);
char* copyArray(char * from, char* fromEnd, char* to);
char* reverseArray(char* arrBeg, char* arrEnd);
bool additionOK();
bool subtractionOK();

int main(){
	char equationArray[MAX_ARRAY_SIZE*2+1];  // operandA(<=256) operator(1) operandB(<=256)
	char result[MAX_ARRAY_SIZE];
	char* pointerToLast=result; //points to LAST element in result; currently no elms, so pointer=&res[0]
	char* operatorPtr;
	char* endPtr;  // point to '\0' of equationArray

	// additionOK();
	// subtractionOK();
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
		pointerToLast=bigDivision(equationArray,operatorPtr-1,operatorPtr+1,endPtr-1, pointerToLast);
		break;
}
	printArray(result, pointerToLast);
	system("pause");
};

char* add(const char* aBeg, const char *aEnd, const char* bBeg,const char* bEnd, char* pointerToLast){
	int aLength=aEnd-aBeg;
	int bLength=bEnd-bBeg;
	char* firstPtr=pointerToLast;
	
	if(aLength<bLength){
		pointerToLast=add(bBeg,bEnd,aBeg,aEnd, pointerToLast); 
		return pointerToLast;
	}
		
	while(bEnd>=bBeg){
		*pointerToLast=*aEnd+*bEnd-96;
		--aEnd;
		--bEnd;
		++pointerToLast;
	}
	while(aEnd>=aBeg){
		*pointerToLast=*aEnd-48;
		--aEnd;
		++pointerToLast;
	}
	--pointerToLast;
	while(!*pointerToLast){
		if(pointerToLast==firstPtr)
		break; //remove zeros
		--pointerToLast;
	}
	return pointerToLast;
}

char* getOperatorIndex(char *equationString){
	while(!isOperator(*++equationString));   
	return equationString;
}
 
bool isOperator(int characterDec){
	if(characterDec>'/')return false;
	
	switch(characterDec){
		case '*':       
			// '*' assumed multiplication
			return true;
		case '+':
			// '+' assumed addition
			return true;
		case '-':
			// '-' assumed subtraction
			return true;
		case '/':
			// '/' assumed division
			return true;
	}
	return false;
}

void printArray(const char* resultBeg,const char* pointerToLast){
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
 

char* subtract(const char* aBeg, const char *aEnd, const char* bBeg, const char* bEnd, char* pointerToLast){
	// aBeg is beginning of the string, 
	// aEnd is pointerToOperator-1,
	//	bBeg=pointerToOperator+1,
	//  bEnd is '\0' of string-1
	int aLength=aEnd-aBeg;
	int bLength=bEnd-bBeg;
	char* firstPtr=pointerToLast;
	/*
	* Result is negated if A<B, or
	* A[0]<B[0] when A.Len==B.Len
	* In both of these cases A and B are also switched
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
	*pointerToLast=0;
	while(bEnd>=bBeg){
		int a=*aEnd;
		--aEnd;	
		if(a<*bEnd){
			a+=10;
			*(pointerToLast+1)=-1;
		}else *(pointerToLast+1)=0;
		*pointerToLast+=a-*bEnd;
		++pointerToLast;
		--bEnd;
	}
	while(aEnd>=aBeg){
		int a=*aEnd;
		if(a<0){
			a+=10;
			*(pointerToLast+1)=-1;
		}else *(pointerToLast+1)=0;
		*pointerToLast+=a-48;
		--aEnd;
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

char* reverseArray(char* arrBeg, char* arrEnd){
	int length=arrEnd-arrBeg+1;
	for(int a=0; a<length/2;a++){
		cout<<"reverse: "<<(int)arrBeg[a]<<" "<<(int)arrBeg[length-a-1]<<endl;
		char tmp=arrBeg[a]+48;
		arrBeg[a]=arrBeg[length-a-1]+48;
		arrBeg[length-a-1]=tmp;
	}
	if(length<2)*arrBeg+=48;
	return arrEnd;
}

char* copyArray(char * from, char* fromEnd, char* to){
	while(fromEnd-from>=0){
		cout<<"copy: "<<(int)*from<<endl;
		*to=*from;
		++to;
		++from;
	}
	*to='\0';
	return --to;
}

char* bigDivision(const char* aBeg, const char* aEnd, const char* bBeg, const char* bEnd, char* pointerToLast){
	int aLength=aEnd-aBeg;
	int bLength=bEnd-bBeg;
	if(aLength<bLength)bigDivision(bBeg, bEnd,aBeg,aEnd, pointerToLast);
	char* res=pointerToLast;
	char result[MAX_ARRAY_SIZE];
	do{
			pointerToLast=subtract(aBeg, aEnd, bBeg, bEnd, pointerToLast);
			aEnd=reverseArray(result,copyArray(res, pointerToLast, result));
			aBeg=result;
			pointerToLast=res;
			printArray(aBeg, aEnd);
			cout<<"-----------"<<endl;
	}while(*aBeg>'0');
	pointerToLast=add(aBeg, aEnd, bBeg, bEnd, pointerToLast);
	 
	return pointerToLast;

}

 
bool additionOK(){
	cout<<"PASSING ADDITION TEST...";
	
	char res[MAX_ARRAY_SIZE];
	char eq[][2][50]={
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
	 char eq[][2][50]={
		{"1234-9876","-8642"},
		{"9876-1234", "8642"},
		{"12345-9876","2469"},
		{"98765-1234", "97531"},
		{"10000-10000","0"},
		{"10000-9990","10"}
	};
	for(int i=0;i<6;++i){
		char* operatorPtr=getOperatorIndex(eq[i][0]);
		char* pointerToLast=res;
		char* endPtr=(operatorPtr+1)+strlen(operatorPtr+1);  
		
		pointerToLast=subtract(eq[i][0], operatorPtr-1, operatorPtr+1, endPtr-1, pointerToLast); 
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


