
#ifndef LOG_4_CPP
#define LOG_4_CPP

#include<log4cpp/Category.hh>
#include<iostream>
#include <string.h> //strrchr()��������ͷ�ļ�

//��־���ȼ�
enum Priority {
    ERROR,
    WARN,
    INFO,
    DEBUG
};

//�õ���ģʽ��װlog4cpp
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
    Oeasylog();  //����ģʽ�����캯��˽�л�

 private:
	std::string m_logfilename;
    static Oeasylog *m_plog;
    log4cpp::Category &m_category_ref;
};

//*****************************************************
//ע�⣺
//�ļ��� __FILE__ ,������ __func__ ���к�__LINE__ �Ǳ�����ʵ�ֵ�
//����C++ͷ�ļ��ж���� 
//ǰ����������string���ͣ���__LINE__�����Σ�������ҪתΪstring����
//******************************************************

//���������ļ��к� ->ת��Ϊstring����
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


//����һ������־����� �ļ��� ������ �к� �ĺ궨��
#define suffix(msg)  std::string("")\
        .append(FILENAME(__FILE__)).append("(").append(__FUNCTION__)\
        .append(":").append(int2string(__LINE__))\
        .append("): ").append(std::string(msg)).c_str()

static Oeasylog &logInstance = Oeasylog::getInstance();


//���̲��򻯺���������ʽ
#define LogError(msg) logInstance.Error(suffix(msg))
#define LogWarn(msg) logInstance.Warn(suffix(msg))
#define LogInfo(msg) logInstance.Info(suffix(msg))
#define LogDebug(msg) logInstance.Debug(suffix(msg))

#endif
