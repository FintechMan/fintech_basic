#ifndef __FINTECH_BASIC_COM_NONCOPYABLE_H__
#define __FINTECH_BASIC_COM_NONCOPYABLE_H__

/**
 * 实现原理：
 * 1. 构造方法用来初始化类的对象，与父类的其它成员不同，它不能被子类继承；（子类可以继承父类所有的成员变量和成员方法，但不继承父类的构造方法）。
 *    因此，在创建子类对象时，为了初始化从父类继承来的数据成员，系统需要调用其父类的构造方法。
 * 2. 拷贝构造函数执行的是逐个成员初始化，如果子类没有显式定义拷贝构造函数，则在默认的拷贝构造函数中，会执行父类的拷贝构造函数对父类的对象进行初始化；
 * 3. 继承自NonCopyable的类在执行拷贝操作时会调用基类的拷贝操作，但是基类的拷贝操作是显式delete的，因此无法调用，引发编译错误。
 *    将构造函数和析构函数显式定义，使用编译器默认生成的函数，当子类需要定义构造函数的时候不至于通不过编译。
*/
class NonCopyable 
{

public:

	NonCopyable() = default;
	~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
