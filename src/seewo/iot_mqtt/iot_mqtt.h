#pragma once

#include "iot_defines.h"
class IoTMqttImpl;

class IOT_MQTT_EXPORT IoTMqtt
{
public:
    //构造及析构
    IoTMqtt(const IoTConfig &config);
    ~IoTMqtt();

    //MQTT连接及认证
    //开始连接，失败会自动重连（min, max之间的间隔，第一次重连间隔为min，以后为min*2，直到max）
    void Connect(int minRetryInterval = 2, int maxRetryInterval = 60);
    bool IsConnected();

    //上报日志到grail
    void Postlog2Grail(const GrailLog &log);

    //上报基础信息
    void PostDeviceVersion(const std::string &version);
    void PostDeviceName(const std::string &deviceName);
    void PostConfigVersion(const std::list<TslConfigKey> &config);

    //设置日志回调
    static void SetLogCallback(const MLogCallBack &callback);

    //远程配置回调
    void SetConfigCallback(const OnTslConfig &callback);

    //OTA升级回调
    void SetUpgradeCallback(const OnTslUpgrade &callback);

    /************************************************************************/
    /* 下行（云端 -> 设备）                                                   */
    /************************************************************************/
    void SetPropertySetCallback(const OnTslRequest &callback);  //设置设置属性回调
    void SetPropertyGetCallback(const OnTslRequest &callback);  //设置获取属性回调
    void SetServiceCallback(const OnTslRequest &callback);      //设置服务调用回调
    bool SubscribeCustom(const std::string &topic, const OnCustomTopic &callback);  //订阅自定义主题

    /************************************************************************/
    /* 上行（设备 -> 云端）                                                   */
    /************************************************************************/
    bool PropertyPost(const TslBasic &basic, const TslRequest &req);   //属性上报
    bool EventPost(const TslBasic &basic, const TslRequest &req);                       //事件上报
    bool PropertyGet(const TslBasic &basic, const TslRequest &req, TslResponse &res);   //上行属性获取
    bool ServiceCall(const TslBasic &basic, const TslRequest &req, TslResponse &res);   //上行服务调用
    bool PublishCustom(const std::string &topic, const std::string &traceId, const std::string &params); //发布自定义主题

    /************************************************************************/
    /* 网关类设备                                                            */
    /************************************************************************/
    bool GetSubDevice(const TslBasic &basic, std::list<DeviceAuth> &devs); //获取网关下挂子设备
    bool AddSubDevice(const TslBasic &basic, const DeviceAuth &dev);       //添加网关子设备
    bool DelSubDevice(const TslBasic &basic, const DeviceAuth &dev);       //删除网关子设备

    bool OnlineSubDevice(const TslBasic &basic, const DeviceAuth &dev);    //上线子设备（包括认证）
    bool OfflineSubDevice(const TslBasic &basic, const DeviceAuth &dev);   //下线子设备

private:
    IoTMqttImpl *_impl;
};
