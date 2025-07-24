#pragma once 
#include <string>
#include <list>
#include <cstdint>
#include <memory>

namespace iron {
// 日志
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr; // 智能指针类型
    LogEvent();
private:
    const char* filename=nullptr; // 文件名
    int32_t line=0; // 行号 固定位数整数
    uint32_t elapse=0; // 程序运行时间（毫秒） 无符号32位整数
    uint32_t threadId=0; // 线程ID 无符号32位整数
    uint32_t fiberId=0; // 协程ID
    time_t time=0; // 时间戳
    std::string content; // 日志内容
};

class LogLevel {
public:
    enum Level {
        DEBUG = 1, // 调试
        INFO,      // 信息
        WARN,      // 警告
        ERROR,     // 错误
        FATAL      // 致命错误
    };
};

//日志输出
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr; // 智能指针类型

    virtual ~LogAppender(); // 虚析构函数

    void log(LogEvent::ptr event, LogLevel::Level level);
private:
    LogLevel::Level level; // 日志级别
};    


//日志格式化
class LogFormatter {     
public:
    typedef std::shared_ptr<LogFormatter> ptr; // 智能指针类型

    std::string format(LogEvent::ptr event); // 格式化日志事件
private:     
};    

//日志器
class Logger {   
public:
    typedef std::shared_ptr<Logger> ptr; // 智能指针类型

    
    Logger(const std::string& name="root"); // 构造函数
    void log(LogEvent::ptr event, LogLevel::Level level);

    void Debug(LogEvent::ptr event); // 调试日志
    void Info(LogEvent::ptr event); // 信息日志
    void Warn(LogEvent::ptr event); // 警告日志
    void Error(LogEvent::ptr event); // 错误日志
    void Fatal(LogEvent::ptr event); // 致命错误日志

    void addAppender(LogAppender::ptr appender); // 添加日志输出地址
    void delAppender(LogAppender::ptr appender); // 删除日志输出地址
    LogLevel::Level getLevel() const { return level; } // 获取日志级别
    void setLevel(LogLevel::Level level) { this->level = level; } // 设置日志级别
private:
    std::string name; // 日志器名称
    LogLevel::Level level; // 日志级别
    std::list<LogAppender::ptr> appenders; // 日志输出地址列表
};

class StdoutLogAppender : public LogAppender {// 输出到标准输出
public:
};

class FileLogAppender : public LogAppender {// 输出到文件
public:
};

}