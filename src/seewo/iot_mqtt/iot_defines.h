#pragma once
#include <format>
#include <functional>
#include <list>
#include <map>
#include <string>

typedef void (*MLogCallBack)(const char *file, int line, const char *func,
                             int severity, const char *content);

#if defined(_WIN32) && !defined(__CYGWIN__)
#ifdef IOT_MQTT_EXPORTS
#define IOT_MQTT_EXPORT __declspec(dllexport)
#else
#define IOT_MQTT_EXPORT __declspec(dllimport)
#endif
#else
#ifdef IOT_MQTT_EXPORTS
#define IOT_MQTT_EXPORT __attribute__((visibility("default")))
#else
#define IOT_MQTT_EXPORT
#endif
#endif

#define IOT_SDK_VERSION "1.1.4"
#define IN
#define OUT

/************************************************************************/
/* HTTP                                                                 */
/************************************************************************/
/**
 * @brief 产品认证信息
 */
struct ProductAuth {
  std::string productKey;    /// 产品key
  std::string productSecret; /// 产品密钥
};

/**
 * @brief 设备认证信息
 */
struct DeviceAuth {
  std::string productKey;   /// 产品key
  std::string deviceId;     /// 设备ID
  std::string deviceSecret; /// 设备密钥
};

/************************************************************************/
/* MQTT                                                                 */
/************************************************************************/

/**
 * @brief 错误信息
 *
 */
enum IOT_ERROR {
  IOT_ERROR_SUCCESS = 0,    /// 成功
  IOT_ERROR_SERIALIZE_FAIL, /// 序列化参数失败
  IOT_ERROR_PUBLISH_FAIL,   /// 发布失败，连接断开或发布失败
  IOT_ERROR_METHOD_NOT_MATCH, /// 方法不匹配，如获取属性填的其他方法等（废弃）
  IOT_ERROR_TIMEOUT,            /// 超时
  IOT_ERROR_DESERIALIZE_FAIL,   /// 反序列化失败
  IOT_ERROR_METHOD_NOT_SUPPORT, /// 方法不支持
  IOT_ERROR_TOPIC_ERROR,        /// TOPIC错误
  IOT_ERROR_IOT_ISNOT_CONNECT,  /// 发布失败，没有连接上IoT平台
  IOT_ERROR_MQTT_EXCEPT,        /// MQTT客户端发生异常
  IOT_ERROR_REGISTER_FAILED,    /// 动态注册失败
  IOT_ERROR_RECONNECT_TIMEOUT,  /// 重连时间超过120s
  IOT_ERROR_START = 170000      /// SDK段起始错误码
};

/**
 * @brief 消息类型
 *
 */
enum IOT_LOG_TYPE {
  IOT_LOG_DEV = 1, /// 设备行为分析（上下线）
  IOT_LOG_UP = 2,  /// 上行消息分析
  IOT_LOG_DOWN = 3 /// 下行消息分析
};

/**
 * @brief 运行的环境
 *
 */
enum IOT_ENV_TYPE {
  IOT_ENV_DEV = 0, /// 开发环境
  IOT_ENV_TEST,    /// 测试环境
  IOT_ENV_PRO      /// 线上环境
};

/**
 * @brief 上报日志信息
 *
 */
struct GrailLog {
  /// 默认会生成，没有特殊要求，不需要赋值
  uint64_t timestamp =
      0; /// 时间戳，[default]从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)，不建议重新赋值
  std::string module; /// 模块名，[default]为空默认为iotSDK

  /// 设备信息
  std::string deviceId; /// 设备ID  [default]为空则会默认赋值为网关/主设备ID
  std::string
      productKey; /// 产品Key [default]为空则会默认赋值为网关/主设备产品Key

  /// 内容信息
  std::string
      code; ///[*必填*] 处理结果状态码，设备端错误码段应该为171000 - 179999段
  std::string message; /// 错误消息
  std::string traceId; ///[*必填*] 全链路日志ID
  std::string method;  ///[*必填*] 方法
  std::string content; /// 内容，可以为 data、params或自定义
  IOT_LOG_TYPE logType =
      IOT_LOG_TYPE::IOT_LOG_UP; ///[*必填*] 消息类型（收到为下行，发送为上行）
};

/**
 * @brief 基础信息
 *
 */
struct TslBasic {
  std::string traceId; /// 请求唯一ID
  std::string version; /// 协议版本
  std::string deviceId; /// 设备ID（请求时，如果是网关的子设备则需要填写）

  inline std::string str() const {
    return std::format("TslBasic {{traceId={}, version={}, deviceId={}}}",
                       traceId, version, deviceId);
  }
};

/**
 * @brief 请求参数
 *
 */
struct TslRequest {
  std::string
      method; /// 服务名，可填全名，如：thing.service.powerSwitch；也可填定义的标识符名，如：powerSwitch
  std::string params; /// 参数 JSON Object

  inline std::string str() const {
    return std::format("TslRequest {{method={}, params={}}}", method, params);
  }
};

/**
 * @brief 回应
 *
 */
struct TslResponse {
  std::string code = "170000"; /// 回应码，000000表示成功，17属于SDK段错误码
  std::string message = "null"; /// 回应码描述
  std::string data = "null";    /// 响应 JSON Object

  inline std::string str() const {
    return std::format("TslResponse {{code={}, message={}, data={}}}", code,
                       message, data);
  }
};

/**
 * @brief 上报配置版本信息
 *
 */
struct TslConfigKey {
  std::string key = ""; /// 配置key
  int version = 0;      /// 配置版本

  inline std::string str() const {
    return std::format("TslConfigKey {{key={}, version={}}}", key, version);
  }
};

/**
 * @brief 下发配置信息
 *
 */
struct TslConfigItem {
  TslConfigKey key;
  std::string values = ""; /// 配置值

  inline std::string str() const {
    return std::format("TslConfigItem {{key={}, values={}}}", key.str(),
                       values);
  }
};

/**
 * @brief OTA升级版本信息
 *
 */
struct TslUpdate {
  std::string versionCode = ""; /// 版本号
  std::string policyTag = "";   /// 策略tag
  std::string appKey = "";      /// 萌友appKey

  inline std::string str() const {
    return std::format("TslUpdate {{versionCode={}, policyTag={}, appKey={}}}",
                       versionCode, policyTag, appKey);
  }
};

/**
 * @brief 请求回调（同步、异步）
 * @param [IN]const std::string &    MQTT主题完整路径
 * @param [IN]const TslBasic &       请求的基础信息，详见TslBasic 定义
 * @param [IN]const TslRequest &     请求参数，详见TslRequest 定义
 * @param [OUT]TslResponse&          处理结果，详见TslResponse定义
 *
 * @return 无
 *
 */
typedef std::function<void(IN const std::string &, IN const TslBasic &,
                           IN const TslRequest &, OUT TslResponse &)>
    OnTslRequest;

/**
 * @brief 自定义TOPIC订阅的回调
 * @param [IN]const std::string& 主题路径
 * @param [IN]const std::string& traceId
 * @param [IN]const std::string& params
 *
 * @return 无
 *
 */
typedef std::function<void(IN const std::string &, IN const std::string &,
                           IN const std::string &)>
    OnCustomTopic;

/**
 * @brief 连接状态通知，内部会自动重连，不需要外部重连
 * @param [IN]const bool & 是否为连接上，true-连接成功 false-断开连接
 *
 * @return 无
 *
 */
typedef std::function<void(IN const bool &)> OnConnectState;

/**
 * @brief 下发配置列表回调
 * @param [IN]const Configs & 配置列表
 *
 * @return 无
 *
 */
typedef std::function<void(IN const std::list<TslConfigItem> &)> OnTslConfig;

/**
 * @brief OTA升级回调
 * @param [IN]const Configs & 配置列表
 *
 * @return 无
 *
 */
typedef std::function<void(IN const TslUpdate &)> OnTslUpgrade;

/**
 * @brief 连接配置信息
 *
 */
struct IoTConfig {
  std::string host;       /// broker地址
  std::string version;    /// 本地固件版本
  std::string deviceName; /// 设备名称，可为空

  DeviceAuth device;       /// 设备认证信息
  OnConnectState callback; /// 连接状态回调
};

/// 下行方法
const std::string
    DOWN_METHOD_PROPERTY_SET("thing.property.set"); /// 下行属性设置
const std::string
    DOWN_METHOD_PROPERTY_GET("thing.property.get");      /// 下行属性获取
const std::string DOWN_METHOD_SERVICE("thing.service."); /// 下行服务调用

/// 上行方法
const std::string
    UP_METHOD_PROPERTY_POST("thing.property.post"); /// 上行属性上报
const std::string UP_METHOD_PROPERTY_GET("thing.property.get"); /// 上行属性获取
const std::string UP_METHOD_SERVICE("thing.service.");  /// 上行服务调用
const std::string UP_METHOD_EVENT_POST("thing.event."); /// 上行事件上报

/// 网关类
const std::string UP_METHOD_SUB_GET("thing.sub.get"); /// 获取网关下挂子设备
const std::string UP_METHOD_SUB_ADD("thing.sub.add"); /// 添加网关子设备
const std::string UP_METHOD_SUB_DEL("thing.sub.del"); /// 删除网关子设备
const std::string UP_METHOD_SUB_CONNECT("thing.sub.connect"); /// 子设备上线
const std::string
    UP_METHOD_SUB_DISCONNECT("thing.sub.disconnect"); /// 子设备下线

/// 标准功能
const std::string
    UP_METHOD_BASIC_POST("thing.event.basic.post"); /// 标准基础信息上报
const std::string
    DOWN_SERVICE_CONFIG_PUSH("thing.service.configPush"); /// 下发配置
const std::string
    UP_METHOD_CONFIG_POST("thing.event.config.post"); /// 配置版本上报
const std::string DOWN_SERVICE_UPGRADE("thing.service.upgrade"); /// 下发升级
