/** @mainpage   SafeInt Library
* <table>
* <tr><th> Project <td> SafeInt
* <tr><th> Author  <td> He Q.Y. Hong X.Y.
* </table>
* @section  项目描述
* 利用bitset实现安全的高精度整数
*
* @section 功能描述
* 可以设置SafeInt的位数，并且进行四则运算，完成高精度操作
*
* @section 用法描述
* @par 示例
* @code
* #include <iostream.h>
* #include "safeint.h"
* int main(){
*     SafeInt<128> a,b,c;
*     a.read();
*     b.fromString("123456");
*     std::cin>>c;
*     SafeInt<128> d=a*b/c;
*     SafeInt<128> n=a+b-c;
*     SafeInt<128> m=(a+b)%c;
*     d.write();
*     printf("\n%s\n",n.tostring().c_str());
*     std::cout<<m<<std::endl;
*     return 0;
* }
* @endcode
* @section 更新日志
* <table>
* <tr><th> Date         <th>Version     <th>Author      <th>Description </tr>
* <tr><td>2024/03/09    <td> 1.0        <td>Hong X.Y.   <td>创建项目    </tr>
* <tr><td>2024/03/10    <td> 1.1        <td>He Q.Y.     <td>提交架构    </tr>
* <tr><td>2024/03/17    <td> 1.2        <td>He Q.Y.     <td>完成部分实现</tr>
* </table>
*/
#include "safeint.h"
/**
* @brief 从标准的整数构造SafeInt,默认为0
*
* @param _val 标准整数(64bits)
*/
template<int n>
SafeInt<n>::SafeInt(const long long _val){

}

/**
* @brief bitset构造SafeInt
*
* @param _val 长度为n的bitset，直接拷贝至val
*/
template<int n>
SafeInt<n>::SafeInt(const std::bitset<n>_val){

}

/**
* @brief 由字符串输入SafeInt
*
* @param s 输入的字符串
*/
template<int n>
void SafeInt<n>::fromstring(const std::string &s){

}

/**
* @brief 从控制台输入SafeInt
*/
template<int n>
void SafeInt<n>::read(){

}

/**
* @brief 把SafeInt转为字符串
*
* @return 返回一个数字字符串，与SafeInt储存的值一致
*/
template<int n>
std::string SafeInt<n>::tostring() const{

}

/**
* @brief 输出SafeInt的值
*/
tmeplate <int n>
void SafeInt<n>::print(){

}

/**
* @brief 直接获得bitset val的值
*
* @return 返回bitset，即val的直接值
*/
template <int n>
std::bitset<n> SafeInt<n>::getVal() const{

}

/**
* @brief 设置bitset val的值
*
* @param _val 新的val值
*/
template <int n>
void SafeInt<n>::setVal(std::bitset<n> _val){

}

/**
* @brief 这个数设置为自己的相反数
*/
template <int n>
void SafeInt<n>::opposite(){

}

/**
* @brief 为两个SafeInt重载求和
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求差
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求乘积
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求商
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为两个SafeInt重载求模
*
* @param a 第一个SafeInt
* @param b 第二个SafeInt
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%const SafeInt<n>& a,const SafeInt<n>& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求和
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求差
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求积
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const SafeInt<n>& a,const long long& b){

}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const SafeInt<n>& a,const long long& b

}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个SafeInt
* @param b 第二个标准整数
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const SafeInt<n>& a,const long long& b){

}
/**
* @brief 从输入流输入SafeInt
*
* @param in 输入流
* @param b 储存输入的数
*
* @return 返回输入后的输入流
*/
template<int n>
std::istream& operator>>(std::istream &in, SafeInt<n> &b){

}

/**
* @brief 向输出流输出SafeInt
*
* @param out 输出流
* @param b 要被输出的数
*
* @return 返回输出后的输出流
*/
template<int n>
std::ostream& operator<<(std::ostream &in, const SafeInt<n> &b){

}
