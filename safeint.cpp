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
* <tr><th> Date         <th>Version     <th>Author      <th>Description             </tr>
* <tr><td>2024/03/09    <td> 1.0        <td>Hong X.Y.   <td>创建项目                 </tr>
* <tr><td>2024/03/10    <td> 1.1        <td>He Q.Y.     <td>提交架构                 </tr>
* <tr><td>2024/03/17    <td> 1.2        <td>He Q.Y.     <td>完成三则运算和比较        </tr>
* <tr><td>2024/03/18    <td> 1.3        <td>He Q.Y.     <td>逻辑上实现IO             </tr>
* <tr><td>2024/03/18    <td> 1.4        <td>He Q.Y.     <td>基本功能全部实现          </tr>
* <tr><td>2024/03/19    <td> 1.5        <td>He.Q.Y.     <td>修复大量bug              </tr>
* </table>
*/

/**
*  @file safeint.cpp
*  @brief SafeInt类的实现
*  @details 实现了SafeInt类的计算，使用等功能。
*  @mainpage 具体实现
*  @author He Q.Y.
*  @version 1.4
*  @date 2024-3-18
*/
#include "safeint.h"
#include <cmath>
/**
* @brief 从标准的整数构造SafeInt,默认为0
*
* @param _val 标准整数(64bits)
*/
template<int n>
SafeInt<n>::SafeInt(const long long _val){
    val=abs(_val);
    if (_val<0){
       opposite();
    }
}

/**
* @brief bitset构造SafeInt
*
* @param _val 长度为n的bitset，直接拷贝至val
*/
template<int n>
SafeInt<n>::SafeInt(const std::bitset<n>_val){
    val=_val;
}

/**
* @brief 由字符串输入SafeInt
*
* @param s 输入的字符串
*/
template<int n>
void SafeInt<n>::fromstring(const std::string &s){
    bool flag=false;
    for (int i=0;i<s.size();i++){
        if (s[i]<='9'&&s[i]>='0'){
            *this=*this*10;
            *this=*this+s[i]-'0';
        }else{
            if (i==0){
                if (s[i]=='-'){
                    flag=true;
                }else if(s[i]=='+');
                else{
                    printf("Bad Input : %c\n",s[i]);
                    exit(-1);
                }
            }else{
                printf("Bad Input : %c\n",s[i]);
                exit(-1);
            }
        }
    }
    if (flag){
        this->opposite();
    }
}

/**
* @brief 从标准输入输入SafeInt
*/
template<int n>
void SafeInt<n>::read(){
    std::string s;
    char c='\0';
    while (true){
        c=getchar();
        if (c==EOF||c==' '||c=='\n') break;
        s+=c;
    }
    fromstring(s);
}

/**
* @brief 把SafeInt转为字符串
*
* @return 返回一个数字字符串，与SafeInt储存的值一致
*/
template<int n>
std::string SafeInt<n>::tostring() const{
    // s 存储结果
    std::string s;
    // 复制this的值
    SafeInt<n> _a=*this;
    // 取绝对值
    if (_a.getVal().test(n-1))
        _a.opposite();
    //类似快读完成输入
    while (_a!=0){
        s=(char)((_a%10).getVal().to_ulong()+'0')+s;
        _a=_a/10;
    }
    //判断符号
    if (val.test(n-1)) s='-'+s;
    return s;
}

/**
* @brief 向标准输出输出SafeInt的值
*/
template <int n>
void SafeInt<n>::print(){
    printf("%s",tostring().c_str());
}

/**
* @brief 直接获得bitset val的值
*
* @return 返回bitset，即val的直接值
*/
template <int n>
std::bitset<n> SafeInt<n>::getVal() const{
    return val;
}

/**
* @brief 设置bitset val的值
*
* @param _val 新的val值
*/
template <int n>
void SafeInt<n>::setVal(std::bitset<n> _val){
    val=_val;
}

/**
* @brief 这个数设置为自己的相反数
* @details 可以将自己设为自己的相反数，重点在于补码和反码的转换
* 通过与-1或+1，实现转换。对于负数，得到反码后只需要取反得到原码，
* 正数反之亦然
*/
template <int n>
void SafeInt<n>::opposite(){
    //检测原数的符号
    if (!val.test(n-1)){
        //正数，符号位取反同时取反码
        val.flip();
        /*
        a 1的值
        sum 暂存最终的补码
        */
        std::bitset<n>a=1;
        std::bitset<n> sum = val ^ a;  // 异或操作，对应位上的数字相加，不考虑进位
        std::bitset<n> carry = (val & a) << 1;  // 与操作后左移一位，得到进位
        while (carry.any()) {
            std::bitset<n> _sum = sum ^ carry;  // 再次异或操作并左移一位，消除进位
            carry = (sum & carry) << 1;  // 计算新的进位
            sum=_sum;
        }

        //如果未溢出，则更新val
        if (sum.test(n-1)){
            val=sum;
        }
        else
            //溢出，则撤销取反操作
            val.flip();
    }else{
        //负数，则先减去一，得到反码
        /*
        a，b储存1
        _a 存储a的相反数，即-1
        _val 暂存val的原码
        */
        std::bitset<n>a=1,b=1,_a,_val;
        // 取a的相反数，先取反码
        a.flip();
        //类似前面，不再解释
        _a = val ^ a;
        std::bitset<n> carry = (val & a) << 1;
        while (carry.any()) {
            std::bitset<n>__a = _a ^ carry;
            carry = (_a & carry) << 1;
            _a=__a;
        }
        //如果溢出、操作直接结束（理论上不可能）
        if (!_a.test(n-1))return;
        //将进位标志设置为0
        carry=0;
        //同样，模拟加法sum=val+_a=val-1
        std::bitset<n> sum = val ^ _a;  // 异或操作，对应位上的数字相加，不考虑进位
        carry = (val & _a) << 1;  // 与操作后左移一位，得到进位
        while (carry.any()) {
            std::bitset<n>_sum = (sum ^ carry) << 1;  // 再次异或操作并左移一位，消除进位
            carry = (sum & carry) << 1;  // 计算新的进位
            sum=_sum;
        }
        //如果没有溢出，更新val的值
        if (!sum.test(n-1)) val=sum;
        else
            //如果溢出，结束操作
            return;
        val.flip();
    }
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
    std::bitset<n> sum = a.getVal() ^ b.getVal();  // 异或操作，对应位上的数字相加，不考虑进位
    std::bitset<n> carry = (a.getVal() & b.getVal()) << 1;  // 与操作后左移一位，得到进位
    while (carry.any()) {
        std::bitset<n> _sum = sum ^ carry;  // 再次异或操作并左移一位，消除进位
        carry = (sum & carry) << 1;  // 计算新的进位
        sum=_sum;
    }

    SafeInt<n>r=sum;
    // 溢出检测
    //
    return r;
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
    // 减去一个数等于加上它的相反数
    SafeInt<n> _b=b;
    _b.opposite();
    return a+_b;
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
    SafeInt<n> c;
    for (int i=0;i<n;i++){
        if (b.getVal().test(i)){
            c=c+SafeInt<n>(a.getVal()<<i);
        }
    }
    return c;
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
    // 暂存a，b的拷贝值
    SafeInt<n> _a=a,_b=b;
    // 缓存商
    std::bitset<n> c;
    //对_a，_b取绝对值
    if (a.getVal().test(n-1)) _a.opposite();
    if (b.getVal().test(n-1)) _b.opposite();
    // 错位相减
    for (int i=n-2;i>=0;i--){
        if (SafeInt<n>(_a.getVal()>>i)<_b)
            //不够减，当前位置0
            c.set(n-i-1,false);
        else{
            //够减，当前位置1，并将_a减去_b位移后值
            _a= _a-SafeInt<n>(_b.getVal()<<(n-i));
            c.set(n-i-1,true);
        }
    }
    //判断符号并返回最终结果
    bool flag=a.getVal().test(n-1)!=b.getVal().test(n-1);
    SafeInt<n>r=c;
    if (flag) r.opposite();
    return SafeInt<n>(c);
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
SafeInt<n> operator%(const SafeInt<n>& a,const SafeInt<n>& b){
    // 与除法类似
    SafeInt<n> _a=a,_b=b;
    std::bitset<n> c;
    if (a.getVal().test(0)) _a.opposite();
    if (b.getVal().test(0)) _b.opposite();
    for (int i=n-1;i>=1;i--){
        if (SafeInt<n>(_a.getVal()>>i)<_a) c.set(i,false);
        else{
            _a=_a-SafeInt<n>(_b.getVal()<<i);
            c.set(i,true);
        }
    }
    // 如果两数一正一负，则计算_b-_a
    if (a.getVal().test(0)==b.getVal().test(0)) _a=b-_a;
    // 如果两数同负，则模为绝对值模的相反数
    if (!(a.getVal().test(0)||b.getVal().test(0))) _a.opposite();
    return _a;
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
    return a+SafeInt<n>(b);
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
    return a-SafeInt<n>(b);
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
    return a*SafeInt<n>(b);
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
SafeInt<n> operator/(const SafeInt<n>& a,const long long& b){
    return a/SafeInt<n>(b);
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
    return a%SafeInt<n>(b);
}

/**
* @brief 为一个SafeInt和一个标准整数重载求和
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a+b的和
*/
template<int n>
SafeInt<n> operator+(const long long& b, const SafeInt<n>& a){
    return SafeInt<n>(a)+b;
}

/**
* @brief 为一个SafeInt和一个标准整数重载求差
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a-b的差
*/
template<int n>
SafeInt<n> operator-(const long long& b, const SafeInt<n>& a){
    return SafeInt<n>(a)-b;
}

/**
* @brief 为一个SafeInt和一个标准整数重载求积
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a*b的积
*/
template<int n>
SafeInt<n> operator*(const long long& b, const SafeInt<n>& a){
    return SafeInt<n>(a)*b;
}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a/b的商
*/
template<int n>
SafeInt<n> operator/(const long long& b, const SafeInt<n>& a){
    return SafeInt<n>(b)/a;
}

/**
* @brief 为一个SafeInt和一个标准整数重载求商
*
* @param a 第一个标准整数
* @param b 第二个SafeInt
*
* @return 返回a%b的值
*/
template<int n>
SafeInt<n> operator%(const long long& b, const SafeInt<n>& a){
    return SafeInt<n>(b)%a;
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
    std::string s;
    in>>s;
    b.fromstring(s);
    return in;
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
std::ostream& operator<<(std::ostream &out, const SafeInt<n> &b){
    out<<b.tostring();
    return out;
}

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
bool operator<(const SafeInt<n> &a, const SafeInt<n> &b){
    SafeInt<n> c=b-a;
    return c.getVal().test(n-1) &&c!=0;
}

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
bool operator<(const SafeInt<n> &a,const long long &b){
    return a<SafeInt<n>(b);
}

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
bool operator<(const long long &a, const SafeInt<n> &b){
    return SafeInt<n>(a)<b;
}


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
bool operator>(const SafeInt<n> &a, const SafeInt<n> &b){
    SafeInt<n> c=a-b;
    return c.getVal().test(n-1)&&c!=0;
}

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
bool operator>(const SafeInt<n> &a,const long long &b){
    return a>SafeInt<n>(b);
}

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
bool operator>(const long long &a, const SafeInt<n> &b){
    return SafeInt<n>(a)>b;
}

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
bool operator==(const SafeInt<n> &a, const SafeInt<n> &b){
    return a.getVal()==b.getVal();
}

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
bool operator==(const SafeInt<n> &a,const long long &b){
    return a==SafeInt<n>(b);
}


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
bool operator==(const long long &a, const SafeInt<n> &b){
    return b==SafeInt<n>(a);
}


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
bool operator!=(const SafeInt<n> &a, const SafeInt<n> &b){
    return !(a==b);
}

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
bool operator!=(const SafeInt<n> &a,const long long &b){
    return a!=SafeInt<n>(b);
}

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
bool operator!=(const long long &a, const SafeInt<n> &b){
    return b!=SafeInt<n>(a);
}

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
bool operator>=(const SafeInt<n> &a, const SafeInt<n> &b){
    return a>b||a==b;
}

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
bool operator>=(const SafeInt<n> &a,const long long &b){
    return a>b||a==b;
}

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
bool operator>=(const long long &a, const SafeInt<n> &b){
    return a>b||a==b;
}

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
bool operator<=(const SafeInt<n> &a, const SafeInt<n> &b){
    return a<b||a==b;
}

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
bool operator<=(const SafeInt<n> &a,const long long &b){
    return a<b||a==b;
}

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
bool operator<=(const long long &a, const SafeInt<n> &b){
    return a<b||a==b;
}
