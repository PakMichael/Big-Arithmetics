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

int main(){
	char equationArray[MAX_ARRAY_SIZE*2+1];  // operandA(<=256) operator(1) operandB(<=256)
	char result[MAX_ARRAY_SIZE];
	char* pointerToLast=result; //points to LAST element in result; currently no elms, so pointer=&res[0]
	char* operatorPtr;
	char* endPtr;  // point to '\0' of equationArray

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

	while(bEnd>=bBeg){
		int a=*aEnd;
		--aEnd;	
		if(a<*bEnd){
			a+=10;
			--(*aEnd);
		}
		*pointerToLast=a-*bEnd;
		++pointerToLast;
		--bEnd;
	}
	while(aEnd>=aBeg){
		if(*aEnd<0){
			*aEnd+=10;
			--*(aEnd-1);
		}
		*pointerToLast=*aEnd-48;
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

char* bigDivision(char* aBeg, char* aEnd,char* bBeg, char* bEnd, char* pointerToLast){
		 
	return nullptr;

}

 