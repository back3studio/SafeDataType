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
* <tr><th> Date         <th>Version     <th>Author      <th>Description。   </tr>
* <tr><td>2024/03/09    <td> 1.0        <td>Hong X.Y.   <td>创建项目         </tr>
* <tr><td>2024/03/10    <td> 1.1        <td>He Q.Y.     <td>提交架构         </tr>
* <tr><td>2024/03/17    <td> 1.2        <td>He Q.Y.     <td>完成三则运算和比较 </tr>
* <tr><td>2024/03/18    <td> 1.3        <td>He Q.Y.     <td>逻辑上实现IO      </tr>
* </table>
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
    // n 符号标志，b 读入其他符号标志
    bool n=false,b=true;
    //遍历s
    for (char a:s){
        if (a<='9'&&a>='0'){
            // 如果输入为数字，正常读入,应计得绝对值
            *this=*this+(a-'0');
            *this=*this*10;
        }else{
            // 特殊符号，如果出现在开头,即b为1，试着确定符号
            if (a=='-'&&b){
                // 首个字符为- 标记为负数
                n=true;
            }else if(a!='+'||(!b)){
                // 如果首个字符不为+或-或出现特殊字符于数字中间，则结束输入，置0
                val=0;
                return;
            }
        }
        //标记为不首个字符
        b=false；
    ｝
    if (n){
        //如果为负数、取相反数
        this->opposite();
    }
}

/**
* @brief 从标准输入输入SafeInt
*/
template<int n>
void SafeInt<n>::read(){
    // n 符号标志，b 读入其他符号标志
    bool n=false,b=true;
    // a 输入的字符
    char a;
    //重复输入
    while (true){
        a=getchar();
        if (a<='9'&&a>='0'){
            // 如果输入为数字，正常读入,应计得绝对值
            *this=*this+(a-'0');
            *this=*this*10;
        }else{
            // 特殊符号，如果出现在开头,即b为1，试着确定符号
            if (a=='-'&&b){
                // 首个字符为- 标记为负数
                n=true;
            }else if(a!='+'||(!b)){
                // 如果首个字符不为+或-或出现特殊字符于数字中间，则结束输入
                if (a!='\n'&&a!=' '){
                    //读入非正常的特殊字符，异常结束，置0
                    val=0;
                    n=0;
                }
                break;
            }
        }
        //标记为非首字符
        b=false；
    ｝
    if (n){
        //如果为负数、取相反数
        this->opposite();
    }
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
    if (_a[0])
        _a.opposite();
    //类似快读完成输入
    while (_a!=0){
        s=((_a%10).getVal().to_ulong()+'0')+s;
        _a=_a/10;
    }
    //判断符号
    if (val[0]) s='-'+s;
    return s;
}

/**
* @brief 向标准输出输出SafeInt的值
*/
tmeplate <int n>
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
    if (!val[0]){
        //正数，符号位取反同时取反码
        val.flip();
        /*
        a 1的值
        _val 暂存补码的值
        */
        std::bitset<n>a=1,_val;
        // 进位标志
        bool car=0;
        // 模拟加法，_val=val+1
        for (int i=n-1;i>=0;i--){
            _val[i]=val[i]!=a[i]!=car;
            car=val[i]&&a[i]&&car;
        }
        //如果未溢出，则更新val
        if (_val[0])val=_val;
        else 
            //溢出，则撤销取反操作
            val.flip()
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
        // 进位标志
        bool car=0;
        //类似前面，不再解释
        for (int i=n-1;i>=0;i--){
            _a[i]=a[i]!=b[i]!=car;
            car=a[i]&&b[i]&&car;
        }
        //如果溢出、操作直接结束（理论上不可能）
        if (!a[0])return;
        //将进位标志设置为0
        car=0;
        //同样，模拟加法_val=val+_a=val-1
        for (int i=n-1;i>=0;i--){
            _val[i]=val[i]!=_a[i]!=car;
            car=val[i]&&_a[i]&&car;
        }
        //如果没有溢出，更新val的值
        if (!val[0]) val=_val;
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
    std::bitset<n> c
    // 进位标志
    bool car=0,c2=0;
    // 模拟加法，c=a+b
    for (int i=n-1;i>=0;i--){
        c[i]=a[i]!=b[i]!=car;
        c2=car;
        car=a[i]&&b[i]&&car;
    }
    SafeInt<n>r=c;
    //溢出检测
    if (c[0]!=(a[0]!=b[0]!=c2)){
        c=0;
        c.flip();
        c[0]=a[0]!=b[0]!=c2;
        if (c[0]){
            c[0]=0;
            r=c;
            r.opposite();
        }
    }
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
        if (b[n-i-1]){
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
    return SafeInt<n>(a)/b;
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
    return SafeInt<n>(a)/b;
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
// n 符号标志，b 读入其他符号标志
    bool n=false,b=true;
    // a 输入的字符
    char a;
    //重复输入
    while (true){
        in>>a;
        if (a<='9'&&a>='0'){
            // 如果输入为数字，正常读入,应计得绝对值
            *this=*this+(a-'0');
            *this=*this*10;
        }else{
            // 特殊符号，如果出现在开头,即b为1，试着确定符号
            if (a=='-'&&b){
                // 首个字符为- 标记为负数
                n=true;
            }else if(a!='+'||(!b)){
                // 如果首个字符不为+或-或出现特殊字符于数字中间，则结束输入
                if (a!='\n'&&a!=' '){
                    //读入非正常的特殊字符，异常结束，置0
                    val=0;
                    n=0;
                }
                break;
            }
        }
        //标记为非首字符
        b=false；
    ｝
    if (n){
        //如果为负数、取相反数
        this->opposite();
    }
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
    return c.getVal()[0] &&c!=0;
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
    return return SafeInt<n>(a)<b;
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
    return c.getVal()[0]&&c!=0;
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
    return !(a==b)
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
