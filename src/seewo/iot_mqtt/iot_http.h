#pragma once
#include "iot_defines.h"

class IoTHttpImpl;

#define IDEN_ANDROID_SN     "android-sn"    //大板-添加安卓的SN
#define IDEN_ANDROID_MAC    "android-mac"   //大板-添加安卓的MAC列表
#define IDEN_PC_SN          "pc-sn"         //PC-添加PC的SN
#define IDEN_PC_MAC         "pc-mac"        //PC-添加PC的MAC列表
#define IDEN_UID            "uid"           //添加设备的UID

class IOT_MQTT_EXPORT IoTHttp
{
public:
    /**
    * @brief    构造函数
    * @param    uri 认证API地址
    *
    * @return   无
    */
    IoTHttp(const std::string &uri);
    ~IoTHttp();

    /**
    * @brief    添加设备的唯一标识符，存在多个标识唯一标识符可多次调用（如安卓的mac列表及安卓sn都需要用来区分设备的唯一标识）
    * @param    type   类型，默认有IDEN_ANDROID_SN等定义，也可自定义如device-id
    * @param    values 标识符值集（有多个时，如mac列表）
    *
    * @return   无
    */
    void AddIdentifier(const std::string &type, const std::list<std::string> &values);

    /**
    * @brief    设备注册
    * @param    [in]  product 产品认证信息
    * @param    [out] device  设备认证信息
    *
    * @return   true-成功 false-失败
    */
    bool DeviceRegister(const ProductAuth &product, DeviceAuth &device);

private:
    IoTHttpImpl *_impl;
};
