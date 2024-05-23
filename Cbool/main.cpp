#include <stdio.h>
#include "Bool.h"

class MyClass
{
public:
	MyClass();
	~MyClass();

private:
	int a;
	int b;
	int c;
	int d;
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

int main() 
{
	CBool TestFlag;
	CBool TestFlag1;
	{
		CBool TestFlag2( true, "a" );
		CBool TestFlag3( true, "b" );
	}
	CBool TestFlag4;
	CBool TestFlag5;


	TestFlag = true;
	TestFlag.SetName( "テストフラグ" );

	TestFlag.ToString();

	if ( TestFlag == false ){
		printf( "%s = %s\n", TestFlag.GetName().c_str(), TestFlag.ToString().c_str() );
	}
	if ( TestFlag.Get() ){
		printf( "%s = %s\n", TestFlag.GetName().c_str(), TestFlag.ToString().c_str() );
	}

	return 0;
}
