#include "include/log.h"
namespace iron {

Logger::Logger(const std::string& name):m_name(name) {
    // 初始化日志器

}

void Logger::addAppender(LogAppender::ptr appender){
    if (appender) {
        m_appenders.push_back(appender); // 将日志输出地址添加到列表中
    }
}// 添加日志输出地址

void Logger::delAppender(LogAppender::ptr appender){
    for(auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if (*it == appender) {
            m_appenders.erase(it); // 从列表中删除指定的日志输出地址
            break;
        }
    }
} // 删除日志输出地址

void Logger::log(LogEvent::ptr event, LogLevel::Level level){
    if(level >= m_level) {
        for(auto& appender : m_appenders) {
            appender->log(event, level); // 遍历日志输出地址列表，将日志事件发送到每个地址
        }
    }
}
    
void Logger::Debug(LogEvent::ptr event){

} // 调试日志

void Logger::Info(LogEvent::ptr event){

} // 信息日志

void Logger::Warn(LogEvent::ptr event){

} // 警告日志

void Logger::Error(LogEvent::ptr event){

} // 错误日志

void Logger::Fatal(LogEvent::ptr event){

} // 致命错误日志


}