#ifndef safe_int_h
#define safe_int_h
template<int n>
class SafeInt{
	public:
	SafeInt(long long val=0);
	SafeInt(char* val);
	SafeInt& operator=(const SafeInt& val);
	private:
	char val[n];
	
};
#endif
