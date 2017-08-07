
#ifndef LOG_4_CPP
#define LOG_4_CPP

#include<log4cpp/Category.hh>
#include<iostream>
#include <string.h> //strrchr()函数所需头文件

//日志优先级
enum Priority {
    ERROR,
    WARN,
    INFO,
    DEBUG
};

//用单例模式封装log4cpp
class Oeasylog {
 public: 
    static Oeasylog& getInstance();
    static void destory();
	void setLogFilename( const std::string& fileName = "log4cpp.log");
    void setPriority(Priority priority);
    void Error(const char* msg);
    void Warn(const char* msg);
    void Info(const char* msg);
    void Debug(const char* msg);

 private:
    Oeasylog();  //单例模式：构造函数私有化

 private:
	std::string m_logfilename;
    static Oeasylog *m_plog;
    log4cpp::Category &m_category_ref;
};

//*****************************************************
//注意：
//文件名 __FILE__ ,函数名 __func__ ，行号__LINE__ 是编译器实现的
//并非C++头文件中定义的 
//前两个变量是string类型，且__LINE__是整形，所以需要转为string类型
//******************************************************

//整数类型文件行号 ->转换为string类型
inline std::string int2string(int line) {
    std::ostringstream oss;
    oss << line;
    return oss.str();
}

#ifdef WIN32
#define FILENAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define FILENAME(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif


//定义一个在日志后添加 文件名 函数名 行号 的宏定义
#define suffix(msg)  std::string("")\
        .append(FILENAME(__FILE__)).append("(").append(__FUNCTION__)\
        .append(":").append(int2string(__LINE__))\
        .append("): ").append(std::string(msg)).c_str()

static Oeasylog &logInstance = Oeasylog::getInstance();


//缩短并简化函数调用形式
#define LogError(msg) logInstance.Error(suffix(msg))
#define LogWarn(msg) logInstance.Warn(suffix(msg))
#define LogInfo(msg) logInstance.Info(suffix(msg))
#define LogDebug(msg) logInstance.Debug(suffix(msg))

#endif
