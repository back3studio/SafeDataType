/**
*  @file safeint.h
*  @brief SafeInt类的头文件
*  @details 定义了SafeInt类用于存储高精度整数，SafeInt核心使用bitset储存信息
*  @mainpage 概况
*  @author He Q.Y.
*  @version 1.4
*  @date 2024-3-18
*/
#ifndef safe_int_h
#define safe_int_h
#include <bitset>
#include <string>
#include <iostream>
/** @class SafeInt
* @brief SafeInt高精度整数类
* @param  n 高精度整数的位数
* SafeInt 安全的高精度整数类，可以完成四则运算，其可以储存的范围为(-2^n,2^n-1),不会溢出
*/
template<int n>
class SafeInt{
	public:
	/**
	* @brief 从标准的整数构造SafeInt,默认为0
	*
	* @param _val 标准整数(64bits)
	*/
	SafeInt(const long long _val=0);

	/**
	* @brief bitset构造SafeInt
	*
	* @param _val 长度为n的bitset，直接拷贝至val
	*/
	SafeInt(const std::bitset<n>_val);

	/**
	* @brief 由字符串输入SafeInt
	*
	* @param s 输入的字符串
	*/
	void fromstring(const std::string &s);

    /**
    * @brief 从标准输入输入SafeInt
    */
	void read();

	/**
	* @brief 把SafeInt转为字符串
	*
	* @return 返回一个数字字符串，与SafeInt储存的值一致
	*/
	std::string tostring() const;

	/**
	* @brief 向标准输出输出SafeInt的值
	*/
	void print();

	/**
	* @brief 直接获得bitset val的值
	*
	* @return 返回bitset，即val的直接值
	*/
	std::bitset<n> getVal() const;

    /**
    * @brief 设置bitset val的值
    *
    * @param _val 新的val值
    */
	void setVal(std::bitset<n> _val);

	/**
    * @brief 这个数设置为自己的相反数
	*/
	void opposite();

	private:
	/** @var val
	* SafeInt的数据核心值
	*/
	std::bitset<n> val;
};

/**
* @brief 为两个SafeInt重载求和
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const SafeInt<n>& b);

/**
* @brief 为两个SafeInt重载求差
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const SafeInt<n>& b);

/**
* @brief 为两个SafeInt重载求乘积
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const SafeInt<n>& b);

/**
* @brief 为两个SafeInt重载求商
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const SafeInt<n>& b);

/**
* @brief 为两个SafeInt重载求模
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const SafeInt<n>& a,const SafeInt<n>& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求和
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const long long& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求差
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const long long& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求积
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const long long& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const long long& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const SafeInt<n>& a,const long long& b);

/**
* @brief 为一个SafeInt和一个标准整数重载求和
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const long long& b, const SafeInt<n>& a);

/**
* @brief 为一个SafeInt和一个标准整数重载求差
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const long long& b, const SafeInt<n>& a);

/**
* @brief 为一个SafeInt和一个标准整数重载求积
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const long long& b, const SafeInt<n>& a);

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const long long& b, const SafeInt<n>& a);

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const long long& b, const SafeInt<n>& a);

/**
* @brief 从输入流输入SafeInt
*
* @param in 输入流
* @param b 储存输入的数
*
* @return 返回输入后的输入流
*/
template<int n>
std::istream& operator>>(std::istream &in, SafeInt<n> &b);

/**
* @brief 向输出流输出SafeInt
*
* @param out 输出流
* @param b 要被输出的数
*
* @return 返回输出后的输出流
*/
template<int n>
std::ostream& operator<<(std::ostream &out, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否小于b
*     @retval true a<b
*     @retval false a<=b
*/
template<int n>
bool operator<(const SafeInt<n> &a, const SafeInt<n> &b);
/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否小于b
*     @retval true a<b
*     @retval false a<=b
*/
template<int n>
bool operator<(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否小于b
*     @retval true a<b
*     @retval false a<=b
*/
template<int n>
bool operator<(const long long &a, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否大于b
*     @retval true a>b
*     @retval false a<=b
*/
template<int n>
bool operator>(const SafeInt<n> &a, const SafeInt<n> &b);
/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否大于b
*     @retval true a>b
*     @retval false a<=b
*/
template<int n>
bool operator>(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否大于b
*     @retval true a>b
*     @retval false a<=b
*/
template<int n>
bool operator>(const long long &a, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否等于b
*     @retval true a==b
*     @retval false a!=b
*/
template<int n>
bool operator==(const SafeInt<n> &a, const SafeInt<n> &b);
/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否等于b
*     @retval true a==b
*     @retval false a!=b
*/
template<int n>
bool operator==(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否等于b
*     @retval true a==b
*     @retval false a!=b
*/
template<int n>
bool operator==(const long long &a, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否不等于b
*     @retval true a!=b
*     @retval false a==b
*/
template<int n>
bool operator!=(const SafeInt<n> &a, const SafeInt<n> &b);
/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否不等于b
*     @retval true a!=b
*     @retval false a==b
*/
template<int n>
bool operator!=(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否不等于b
*     @retval true a!=b
*     @retval false a==b
*/
template<int n>
bool operator!=(const long long &a, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否大于等于b
*     @retval true a>=b
*     @retval false a<b
*/
template<int n>
bool operator>=(const SafeInt<n> &a, const SafeInt<n> &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否大于等于b
*     @retval true a>=b
*     @retval false a<b
*/
template<int n>
bool operator>=(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否大于等于b
*     @retval true a>=b
*     @retval false a<b
*/
template<int n>
bool operator>=(const long long &a, const SafeInt<n> &b);

/**
* @brief 比较两个SafeInt的大小
* 
* @param a 第一个SafeInt
* @param b 第二个SafeInt
* 
* @return 返回a是否小于等于b
*     @retval true a<=b
*     @retval false a>b
*/
template<int n>
bool operator<=(const SafeInt<n> &a, const SafeInt<n> &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个SafeInt
* @param b 第二个标准整数
* 
* @return 返回a是否小于等于b
*     @retval true a<=b
*     @retval false a>b
*/
template<int n>
bool operator<=(const SafeInt<n> &a,const long long &b);

/**
* @brief 比较一个SafeInt和标准整数的大小
* 
* @param a 第一个标准整数
* @param b 第二个SafeInt
* 
* @return 返回a是否小于等于b
*     @retval true a<=b
*     @retval false a>b
*/
template<int n>
bool operator<=(const long long &a, const SafeInt<n> &b);

#endif
