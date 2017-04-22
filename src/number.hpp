#ifndef NUMBER_HPP
#define NUMBER_HPP

const int MAX_ARRAY_SIZE=256;


class Number
{
	int* firstInNumber;
	int* lastInNumber;
	
public:
	Number(const Number &copy);
	Number();
	~Number();
	Number operator+(Number& b);
	Number operator-(Number& b);
	Number operator*(Number& b);
	Number operator/(Number& b)const;
	void operator=(Number& b);
	void operator=(int num);
	void operator=(std::string str);
	int& operator[](int index)const;
	bool operator==(Number& b);
	bool operator>(Number& b);
	bool operator<(Number& b) const;
	bool operator>=(Number& b);
	bool operator<=(Number& b);
	int*& firstPtr();
	int*& lastPtr();
	int length() const;
	void print();
	void reverse(Number &num)const;
};

#endif