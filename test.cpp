#include "safeint.h"
#include "safeint.cpp"
#include <iostream>
int main(){
	SafeInt<128>a,b,c;
	std::cin>>a;
	std::cin>>b;
    c=a/b;
	std::cout<<c.getVal();
	//c.print();
	return 0;
 }
