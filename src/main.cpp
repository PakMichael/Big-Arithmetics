#include <iostream>
#include <cstring>

using namespace std;

/*
* A[] and B[] should be const and identically arranged to their original values in equationArray
* All function should return pointers to last element in pointee array, not one past(!)
* Instead of in-function normalization, use after-normalization where possible
*
*/
const int MAX_ARRAY_SIZE=256;

//new
int* toIntArray(char* firstInA, char* lastInA, int* firstInB);
void printArray(const int* firstInResult, const int* lastInResult);
int* normalizeAddition(int* firstInResult, int* lastInResult);
int* multiply(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult);
int* add(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult);
int* subtract(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult);
int* divide(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult);
int* bigDivision(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult);
int* copyArray(const int* firstInA, const int* lastInA, int* lastInB);
//
char* getOperatorIndex(char* equationString);
bool isOperator(char characterDec);
bool lessThan(const char* aBeg, const char* aEnd, const char* bBeg, const char* bEnd);
char* reverseArray(char* arrBeg, char* arrEnd);
bool additionOK();
bool subtractionOK();


int main(){
	char equationArray[MAX_ARRAY_SIZE*2+1];  // operandA(<=256) operator(1) operandB(<=256)
	int a[MAX_ARRAY_SIZE];
	int b[MAX_ARRAY_SIZE];	
	
	cin>>equationArray;
	char* operatorPtr=getOperatorIndex(equationArray);
	
	const int* lastInA=toIntArray(equationArray, operatorPtr, a);
	const int* lastInB=toIntArray(operatorPtr+1, operatorPtr+strlen(operatorPtr), b);
	
	int result[MAX_ARRAY_SIZE];
	int* lastInResult=result;
	
	switch(*operatorPtr){
		case '+':
			lastInResult=add(a, lastInA, b, lastInB, result); 
			lastInResult=normalizeAddition(result, lastInResult); //should be depricated? 
			break;
		case '-':
			lastInResult=subtract(a, lastInA, b, lastInB, result);
			break;
		case '/':
			lastInResult=bigDivision(a, lastInA, b, lastInB, result);
			break;
		case '*':
			*result=0;
			lastInResult=multiply(a, lastInA, b, lastInB, result);	
			lastInResult=normalizeAddition(result, lastInResult); //should be depricated? 
			break;
	}
	
	printArray(result, lastInResult);
	system("pause");
}

int* toIntArray(char* firstInA, char* lastInA, int* firstInB){
	while(lastInA-firstInA>0){
		*firstInB=*firstInA-'0';
		++firstInB;
		++firstInA;
	}
	return --firstInB;  
}

int* add(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	const int aLength=lastInA-firstInA;
	const int bLength=lastInB-firstInB;
	int* firstInResult=lastInResult;
	
	if(aLength<bLength){
		lastInResult=add(firstInB, lastInB, firstInA, lastInA, lastInResult); 
		return lastInResult;
	}
		
	while(lastInB>=firstInB){
		*lastInResult=*lastInA+*lastInB;
		--lastInA;
		--lastInB;
		++lastInResult;
	}
	while(lastInA>=firstInA){
		*lastInResult=*lastInA;
		--lastInA;
		++lastInResult;
	}
	--lastInResult; //lastInResult at this point is junkvalue likely >0 
	while(!*lastInResult){
		if(lastInResult==firstInResult)
			break; //remove leading zeros
		--lastInResult;
	}
	return lastInResult;
}

int* normalizeAddition(int* firstInResult, int* lastInResult){
	while(firstInResult<=lastInResult){
		if(*firstInResult>9){
			if(firstInResult==lastInResult){
				++lastInResult;
				*lastInResult=0;
			}
			*(firstInResult+1)+=*firstInResult/10;
			*firstInResult%=10;
		}
		++firstInResult;
	}
	return lastInResult;
	
}

char* getOperatorIndex(char* equationString){
	while(!isOperator(*++equationString));   
	return equationString;
}
 
bool isOperator(char characterDec){
	if(characterDec>='*' & characterDec<='/')return true;
	return false;
}

void printArray(const int* firstInResult, const int* lastInResult){
	while(lastInResult>=firstInResult){
		cout<<(int)*lastInResult<<" ";
		--lastInResult;
	}
	cout<<endl;
}

int* subtract(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	const int aLength=lastInA-firstInA;
	const int bLength=lastInB-firstInB;
	int* firstInResult=lastInResult;
	/*
	* Result is negated if A<B, or
	* A[0]<B[0] when A.Len==B.Len
	* In both of these cases A and B are also switched
	*/
	if(aLength<bLength){
		lastInResult=subtract(firstInB, lastInB, firstInA, lastInA, lastInResult);
		*lastInResult*=-1;
		return lastInResult;
	}else if(aLength==bLength)
		if(*firstInA<*firstInB){
			lastInResult=subtract(firstInB, lastInB, firstInA, lastInA, lastInResult);
			*lastInResult*=-1;
			return lastInResult;
	}
	*lastInResult=0;
	while(lastInB>=firstInB){
		int a=*lastInA;
		--lastInA;	
		if(a+*lastInResult<*lastInB){
			a+=10;
			*(lastInResult+1)=-1;
		}else 
			*(lastInResult+1)=0;
		*lastInResult+=a-*lastInB;
		++lastInResult;
		--lastInB;
	}
	while(lastInA>=firstInA){
		int a=*lastInA;
		// cout<<"here: "<<a<<endl;
		// cout<<"last: "<<*lastInResult<<endl;
		if(lastInA!=firstInA)
			if(*lastInResult<0){
				*lastInResult+=10;
				*(lastInResult+1)=-1;
			}else 
				*(lastInResult+1)=0;
		*lastInResult+=a;
		--lastInA;
		++lastInResult;
	}		
	
	--lastInResult;
	while(!*lastInResult){
		if(lastInResult==firstInResult)
			break; //remove zeros
		--lastInResult;
	}

	return lastInResult;
}


int* divide(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	const int aLength=lastInA-firstInA;
	const int bLength=lastInB-firstInB;
	
	int* firstInResult=lastInResult;
	int result[MAX_ARRAY_SIZE];
	int* resultPtr=result;
	
	// resultPtr=bigDivision(firstInA, firstInA[bLength], firstInB, lastInB, resultPtr); 
	// subtract(firstInA,firstInA[bLength],firstInResult, lastInResult, ...);
 
	return NULL; 
	
}

int* reverseArray(int* arrBeg, int* arrEnd){
	int length=arrEnd-arrBeg+1;
	for(int a=0; a<length/2; a++){
		char tmp=arrBeg[a];
		arrBeg[a]=arrBeg[length-a-1];
		arrBeg[length-a-1]=tmp;
	}
	return arrEnd;
}

int* copyArray(const int* firstInA, const int* lastInA, int* lastInB){
	while(lastInA-firstInA>=0){
		// cout<<"copy: "<<(int)*firstInA<<endl;
		*lastInB=*firstInA;
		++lastInB;
		++firstInA;
	}

	return --lastInB;
}

bool lessThan(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB){
	// cout<<"lse"<<endl;
	// printArray(firstInA, lastInA);
	// printArray(firstInB, lastInB);
	// cout<<"<-lse"<<endl;
	if(lastInA-firstInA>lastInB-firstInB)return false;
	if(lastInA-firstInA<lastInB-firstInB)return true;
	while(firstInA<=lastInA){
		int a=*firstInA;
		int b=*firstInB;
		if(a>b)return false;
		if(a<b)return true;
		++firstInA;
		++firstInB;
	}
	
	return false;
}

// int* bigDivision(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	// const int aLength=lastInA-firstInA;
	// const int bLength=lastInB-firstInB;
	// int* firstInResult=lastInResult;
	
	// int tempResult[MAX_ARRAY_SIZE];
	// int* tmp=lastInResult;
	// int a=0;
	// while(!lessThan(firstInA, lastInA, firstInB, lastInB)){
			// lastInResult=subtract(firstInA, lastInA, firstInB, lastInB, lastInResult);
			// tmp=lastInResult;
			// lastInResult=copyArray(firstInResult, lastInResult, tempResult); //here on out lastInResult points to tempRes
			// lastInA=reverseArray(tempResult, lastInResult);
			// firstInA=tempResult;
			// lastInResult=firstInResult; //reset pointer
			// ++a;
	// }
	// return tmp;

// }
int* bigDivision(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	const int aLength=lastInA-firstInA;
	const int bLength=lastInB-firstInB;
	
	int* firstInResult=lastInResult;
	const int* tmpLastInA=firstInA+bLength; // A>=B !!!

	int finalRes[MAX_ARRAY_SIZE];
	int* finalResPtr=finalRes;
	
	int tempResult[MAX_ARRAY_SIZE];
	int* firstInTemp=tempResult;
	int* lastInTemp=tempResult;
	lastInTemp=copyArray(firstInA, tmpLastInA, tempResult);
	
	while(tmpLastInA<=lastInA){

		int a=0;
		while(!lessThan(firstInTemp, lastInTemp, firstInB, lastInB)){
			lastInResult=subtract(firstInTemp, lastInTemp, firstInB, lastInB, lastInResult);
			lastInTemp=copyArray(firstInResult, lastInResult, tempResult); 
			lastInTemp=reverseArray(firstInTemp, lastInTemp);
			lastInResult=firstInResult; 
			++a;
		}
		*finalResPtr=a;
		++finalResPtr;
		if(lessThan(firstInTemp, lastInTemp, firstInB, lastInB)){
			if(tmpLastInA<lastInA){
				++tmpLastInA;
				++lastInTemp;
				*lastInTemp=*tmpLastInA;
			}else break;
		}
	}
	--finalResPtr;
	finalResPtr=reverseArray(finalRes, finalResPtr);
	lastInResult=copyArray(finalRes, finalResPtr, lastInResult);
	while(!*lastInResult){
		if(lastInResult==firstInResult)
			break; //remove leading zeros
		--lastInResult;
	}
	return lastInResult;

}

int* multiply(const int* firstInA, const int* lastInA, const int* firstInB, const int* lastInB, int* lastInResult){
	const int aLength=lastInA-firstInA;
	const int bLength=lastInB-firstInB;
	
	const int* tempLastInA=lastInA;
	int* tempLastInResult=lastInResult;
	int* biggestLast=lastInResult-1;
	
	while(lastInB>=firstInB){
		while(lastInA>=firstInA){
			if(lastInResult>biggestLast){
				*lastInResult=0;
			}				
			*lastInResult+=(*lastInB)*(*lastInA);
			++lastInResult;
			--lastInA;
		}
		--lastInB;
		lastInA=tempLastInA;
		biggestLast=lastInResult-1;
		if(lastInB>=firstInB)
			lastInResult=++tempLastInResult;

	}
	return --lastInResult;
	
}

