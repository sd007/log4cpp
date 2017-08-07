#include<iostream>
#include "log4cpp.h"
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/Priority.hh>

using namespace std;

#define MAX_LOGSIZE 1024*1024
#define LOGFILE_SIZE 50

Oeasylog* Oeasylog::m_plog = NULL;

//获取log指针
Oeasylog& Oeasylog::getInstance() {
	if ( m_plog == NULL ) {
		m_plog = new Oeasylog;
	}

	return *m_plog;
}


//销毁
void Oeasylog::destory() {
	if (m_plog) {
		m_plog->m_category_ref.info("log4cpp destroy");
		m_plog->m_category_ref.shutdown();
		delete m_plog;
	}
}


//构造函数
Oeasylog::Oeasylog(): 
m_category_ref(log4cpp::Category::getRoot()) ,
m_logfilename (std::string("log4cpp.log"))
{
	//自定义输出格式
	log4cpp::PatternLayout *pattern_one =
		new log4cpp::PatternLayout;
	pattern_one->setConversionPattern("%d: %p %c %x:%m%n");

	log4cpp::PatternLayout *pattern_two =
		new log4cpp::PatternLayout;
	pattern_two->setConversionPattern("%d: %p %c %x:%m%n");

	//获取屏幕输出
	log4cpp::OstreamAppender *os_appender = 
		new log4cpp::OstreamAppender("osAppender",&std::cout);
	os_appender->setLayout(pattern_one);

	//获取文件日志输出 
	//http://blog.csdn.net/wyb19890515/article/details/7187057
	
	log4cpp::FileAppender *file_appender = 
		new log4cpp::RollingFileAppender("RollingFileAppender", m_logfilename, MAX_LOGSIZE, LOGFILE_SIZE);
	file_appender->setLayout(pattern_two);

	m_category_ref.setPriority(log4cpp::Priority::DEBUG);
	m_category_ref.addAppender(os_appender);
	m_category_ref.addAppender(file_appender);

	m_category_ref.info("log4cpp created!");
}


//设置优先级
void Oeasylog::setPriority(Priority priority) {
	switch (priority) {
	case (ERROR):
		m_category_ref.setPriority(log4cpp::Priority::ERROR);
		break;

	case (WARN):
		m_category_ref.setPriority(log4cpp::Priority::WARN);
		break;

	case (INFO):
		m_category_ref.setPriority(log4cpp::Priority::INFO);
		break;

	case (DEBUG):
		m_category_ref.setPriority(log4cpp::Priority::DEBUG);
		break;

	default:
		m_category_ref.setPriority(log4cpp::Priority::DEBUG);
		break;    
	}
}

void Oeasylog::Error(const char* msg) {
	m_category_ref.error(msg);
}

void Oeasylog::Warn(const char* msg) {
	m_category_ref.warn(msg);
}

void Oeasylog::Info(const char* msg) {
	m_category_ref.info(msg);
}

void Oeasylog::Debug(const char* msg) {
	m_category_ref.debug(msg);
}

void Oeasylog::setLogFilename( const std::string& fileName /*= "log4cpp.log"*/ )
{
	m_logfilename = fileName;
}
