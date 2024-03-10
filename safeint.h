#ifndef safe_int_h
#define safe_int_h
#include <bitset>
#include <string>
template<int n>
class SafeInt{
	public:
	SafeInt(long long val=0);
	SafeInt(const std::bitset<n>&val);
	void read();
	std::string tostring();
	void print();
	std::bitset<n> getVal() const;
	void setVal(std::bitset<n> val);
	private:
	std::bitset<n> val;
};
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const SafeInt<n>& b);
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const SafeInt<n>& b);
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const SafeInt<n>& b);
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const SafeInt<n>& b);

template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const long long& b);
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const long long& b);
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const long long& b);
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const long long& b);
#endif
/*
int main(){
	SafeInt<1024> a,b;
	a.read();
	b.read();
	SafeInt<1024> c;
	c=a+b;
	c.print();
	return 0;
}
input:
9223372036854775807
9223372036854775807
output:
18446744073709551614

input:
18446744073709551614
18446744073709551614
output:
36893488147419103228
*/
