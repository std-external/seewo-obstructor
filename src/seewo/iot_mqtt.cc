#include "iot_mqtt.h"
#include <fstream>
#include <optional>
#include <print>
#include <thread>
#include <vector>

#include "blook/blook.h"

#include "Windows.h"
#include "blook/hook.h"
#include "wingdi.h"

#include "./iot_mqtt/iot_defines.h"
#include "./iot_mqtt/iot_mqtt.h"

#include "nlohmann/json.hpp"

#include "wintoastlib.h"
using namespace WinToastLib;

/**
void SetPropertySetCallback(const OnTslRequest &callback);  //设置设置属性回调
void SetPropertyGetCallback(const OnTslRequest &callback);  //设置获取属性回调
void SetServiceCallback(const OnTslRequest &callback);      //设置服务调用回调
bool SubscribeCustom(const std::string &topic, const OnCustomTopic &callback);
//订阅自定义主题

bool PropertyPost(const TslBasic &basic, const TslRequest &req); //属性上报 bool
EventPost(const TslBasic &basic, const TslRequest &req); //事件上报 bool
PropertyGet(const TslBasic &basic, const TslRequest &req, TslResponse &res);
//上行属性获取 bool ServiceCall(const TslBasic &basic, const TslRequest &req,
TslResponse &res);   //上行服务调用 bool PublishCustom(const std::string &topic,
const std::string &traceId, const std::string &params); //发布自定义主题
*/

namespace seeob::seewo {

void showMainToast();
bool console_window_hidden = true;
struct WinToastEventHandler : public IWinToastHandler {
  void toastActivated() const override {}
  void toastActivated(int actionIndex) const override {
    if (actionIndex == 0) {
      console_window_hidden = !console_window_hidden;
      ShowWindow(GetConsoleWindow(), console_window_hidden ? SW_HIDE : SW_SHOW);
      showMainToast();
    }
  }

  void toastDismissed(WinToastDismissalReason state) const override {}

  void toastFailed() const override {}
} winToastEventHandler;

void showMainToast() {
  WinToastTemplate templ(WinToastTemplate::WinToastTemplateType::Text01);
  templ.setTextField(L"seewo-obstructor 正在运行！",
                     WinToastTemplate::FirstLine);

  templ.addAction(console_window_hidden ? L"显示窗口" : L"隐藏窗口");
  WinToast::instance()->showToast(templ, &winToastEventHandler);
}

static std::shared_ptr<blook::InlineHook> setPropertySetHook;
static std::shared_ptr<blook::InlineHook> setPropertyGetHook;
static std::shared_ptr<blook::InlineHook> setServiceHook;
static std::shared_ptr<blook::InlineHook> propertyPostHook;
static std::shared_ptr<blook::InlineHook> eventPostHook;
static std::shared_ptr<blook::InlineHook> propertyGetHook;
static std::shared_ptr<blook::InlineHook> serviceCallHook;
static std::shared_ptr<blook::InlineHook> publishCustomHook;

bool process_tls_request(std::string_view name, const std::string &topic,
                         const TslBasic &basic, const TslRequest &_req,
                         TslResponse &_res) {
  auto req = const_cast<TslRequest &>(_req);
  auto res = const_cast<TslResponse &>(_res);

  std::println(R"([IotMqtt] {}: 
    topic: {}
    req: {}
    res: {}
)",
               name, topic, req.str(), res.str());

  if (req.method == "thing.service.deviceSpeedLimit") {
    // 1TB -> 137438953472B
    req.params = "{\"downSpeed\":\"137438953472\",\"openLimitFlag\":\"open\","
                 "\"upSpeed\":\"137438953472\"}";
  }

  if (req.method == "thing.service.freezeBypassControl") {
    req.params = R"#({
   "enabled" : true,
   "timeRanges" : [
      {
         "endTime" : "23:59",
         "startTime" : "00:00"
      }
   ]
})#";
  }

  if (req.method == "thing.service.screenSaverSetting") {
    req.params = R"#(
    {
   "data" : {
      "picture" : [
      ],
      "text" : null
   },
   "effectiveEndTime" : null,
   "effectiveStartTime" : 2000000000000,
   "materialSource" : "?,
   "pictureSizeType" : 0,
   "playMode" : 0,
   "settingId" : "",
   "status" : false,
   "switchInterval" : 0,
   "triggerInterval" : 2700000
})#";
  }

  return true;
}

static size_t __fastcall onSetPropertySet(void *a, void *b,
                                          const OnTslRequest &callback) {
  std::println("[IotMqtt] SetPropertySetCallback hooked.");
  return setPropertySetHook->trampoline_t<decltype(onSetPropertySet)>()(
      a, b,
      [=](const std::string &topic, const TslBasic &basic,
          const TslRequest &req, TslResponse &res) {
        if (process_tls_request("SetPropertySet", topic, basic, req, res)) {
          return callback(topic, basic, req, res);
        }
      });
}

static size_t __fastcall onSetPropertyGet(void *a, void *b,
                                          const OnTslRequest &callback) {
  std::println("[IotMqtt] SetPropertyGetCallback hooked.");
  return setPropertyGetHook->trampoline_t<decltype(onSetPropertyGet)>()(
      a, b,
      [=](const std::string &topic, const TslBasic &basic,
          const TslRequest &req, TslResponse &res) {
        if (process_tls_request("SetPropertyGet", topic, basic, req, res)) {
          return callback(topic, basic, req, res);
        }
      });
}

static size_t __fastcall onSetService(void *a, void *b,
                                      const OnTslRequest &callback) {
  std::println("[IotMqtt] SetServiceCallback hooked.");
  return setServiceHook->trampoline_t<decltype(onSetService)>()(
      a, b,
      [=](const std::string &topic, const TslBasic &basic,
          const TslRequest &req, TslResponse &res) {
        if (process_tls_request("SetService", topic, basic, req, res)) {
          return callback(topic, basic, req, res);
        }
      });
}

static bool __fastcall onPropertyPost(void *a, void *b, const TslBasic &basic,
                                      const TslRequest &req) {
  std::println("[IotMqtt] PropertyPost: {}", req.str());
  return propertyPostHook->trampoline_t<decltype(onPropertyPost)>()(a, b, basic,
                                                                    req);
}

static bool __fastcall onEventPost(void *a, void *b, const TslBasic &basic,
                                   const TslRequest &_req) {
  auto req = const_cast<TslRequest &>(_req);
  std::println("[IotMqtt] EventPost: {}", req.str());

  if (req.method == "thing.event.softwareReport.post") {
    req.params = R"#({
        "lists" :
        [
                {
                        "installDir" : "C:\\Program Files (x86)\\Seewo\\EasiAgent",
                        "name" : "EasiAgent",
                        "production" : "Seewo",
                        "version" : "0.0.1.136"
                },
                {
                        "installDir" : "C:\\ProgramData\\Seewo\\Easiupdate",
                        "name" : "EasiUpdate",
                        "production" : "Seewo",
                        "version" : "1.1.3.403"
                },
                {
                        "installDir" : "C:\\ProgramData\\Seewo\\Easiupdate3\\Easiupdate3",
                        "name" : "EasiUpdate3",
                        "production" : "seewo",
                        "version" : "3.5.0.909"
                }
        ]
})#";
  }

  if (req.method == "thing.event.softwareUsedReport.post") {
    req.params = R"#({{
        "lists" :
        [],
        "ssoInfo" :
        {
                "appId" : "",
                "nickName" : "",
                "userId" : ""
        }
})#";
  }

  if (req.method == "thing.event.hardwareReport.post") {
    /*
    {
        "lists" :
        [
                {
                        "name" : "osName",
                        "value" : "Windows 11"
                },
    */

    auto json = nlohmann::json::parse(req.params);

    // disksList
    auto it =
        std::ranges::find_if(json["lists"], [](const nlohmann::json &item) {
          return item["name"] == "disksList";
        });

    if (it != json["lists"].end()) {
      it->at("value") = "{\n   \"C:\" : 110050,\n   \"D:\" : 69344}";
    }

    // diskType
    it = std::ranges::find_if(json["lists"], [](const nlohmann::json &item) {
      return item["name"] == "diskType";
    });

    if (it != json["lists"].end()) {
      it->at("value") = "{\n   \"C:\" : 1,\n   \"D:\" : 1}";
    }

    // camera
    it = std::ranges::find_if(json["lists"], [](const nlohmann::json &item) {
      return item["name"] == "camera";
    });

    if (it != json["lists"].end()) {
      it->at("value") = "[]";
    }
  }

  auto blacklist = {"thing.event.windowReportDetectionV2.post",
                    "thing.event.postWebrtcCameraList.post"};

  if (std::ranges::contains(blacklist, req.method)) {
    return true;
  }

  return eventPostHook->trampoline_t<decltype(onEventPost)>()(a, b, basic,
                                                              _req);
}

static bool __fastcall onPropertyGet(void *a, void *b, const TslBasic &basic,
                                     const TslRequest &req, TslResponse &res) {
  auto bres = propertyGetHook->trampoline_t<decltype(onPropertyGet)>()(
      a, b, basic, req, res);

  if (req.method == "thing.property.get") {
    auto params = nlohmann::json::parse(req.params);

    auto attrs = params["attrs"];
    auto firstAttrString = attrs[0].get<std::string>();

    if (firstAttrString == "enablePowerOnLock") {
      res.data = R"#({
   "enablePowerOnLock" : false
})#";
    }

    if (firstAttrString == "servicesPermission") {
      res.data = R"#({
   "servicesPermission" : {
      "freeze" : false
})#";
    }

    if (firstAttrString == "adminPassword") {
      static bool adminPasswordBroadcasted = false;
      auto json = nlohmann::json::parse(res.data);
      auto password = json["adminPassword"].get<std::string>();
      if (!adminPasswordBroadcasted) {
        WinToastTemplate templ(WinToastTemplate::WinToastTemplateType::Text02);
        templ.setTextField(L"管家密码", WinToastTemplate::TextField::FirstLine);
        templ.setTextField(std::filesystem::path(password).filename().wstring(),
                           WinToastTemplate::TextField::SecondLine);
        WinToast::instance()->showToast(templ, &winToastEventHandler);
        adminPasswordBroadcasted = true;
      }
    }

    if (firstAttrString == "lockStreamPassword") {
      static bool lockStreamPasswordBroadcasted = false;
      auto json = nlohmann::json::parse(res.data);
      auto password = json["lockStreamPassword"].get<std::string>();
      if (!lockStreamPasswordBroadcasted) {
        WinToastTemplate templ(WinToastTemplate::WinToastTemplateType::Text02);
        templ.setTextField(L"锁屏密码", WinToastTemplate::TextField::FirstLine);
        templ.setTextField(std::filesystem::path(password).filename().wstring(),
                           WinToastTemplate::TextField::SecondLine);
        WinToast::instance()->showToast(templ, &winToastEventHandler);
        lockStreamPasswordBroadcasted = true;
      }
    }
  }

  std::println("[IotMqtt] PropertyGet \n\treq: {}\n\tres: {}", req.str(),
               res.str());
  return bres;
}

static bool __fastcall onServiceCall(void *a, void *b, const TslBasic &basic,
                                     const TslRequest &req, TslResponse &res) {
  std::println("[IotMqtt] ServiceCall: {}", req.str());
  auto bres = serviceCallHook->trampoline_t<decltype(onServiceCall)>()(
      a, b, basic, req, res);
  std::println("[IotMqtt] ServiceCall response: {}", res.str());
  return bres;
}

static bool __fastcall onPublishCustom(void *a, void *b,
                                       const std::string &topic,
                                       const std::string &traceId,
                                       const std::string &params) {
  std::println("[IotMqtt] PublishCustom: topic: {}, traceId: {}, params: {}",
               topic, traceId, params);
  return publishCustomHook->trampoline_t<decltype(onPublishCustom)>()(
      a, b, topic, traceId, params);
}

void IotMqtt::install() {
  auto proc = blook::Process::self();
  auto iotMqtt = proc->modules()["iot_mqtt.dll"];

  WinToast::instance()->setAppName(L"seewo-obstructor");
  WinToast::instance()->setAppUserModelId(L"seewo-obstructor'ID");
  WinToast::instance()->initialize();

  if (!iotMqtt) {
    std::println("[IotMqtt] Failed to get iot_mqtt.dll module");
    return;
  }

  if (auto setPropertySetCallback = iotMqtt->exports(
          "?SetPropertySetCallback@IoTMqtt@@QAEXABV?$function@$$A6AXABV?$basic_"
          "string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUTslBasic@@"
          "ABUTslRequest@@AAUTslResponse@@@Z@std@@@Z")) {
    setPropertySetHook = setPropertySetCallback.value().inline_hook();
    setPropertySetHook->install(onSetPropertySet);
  }

  if (auto setPropertyGetCallback = iotMqtt->exports(
          "?SetPropertyGetCallback@IoTMqtt@@QAEXABV?$function@$$A6AXABV?$basic_"
          "string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUTslBasic@@"
          "ABUTslRequest@@AAUTslResponse@@@Z@std@@@Z")) {
    setPropertyGetHook = setPropertyGetCallback.value().inline_hook();
    setPropertyGetHook->install(onSetPropertyGet);
  }

  if (auto setServiceCallback = iotMqtt->exports(
          "?SetServiceCallback@IoTMqtt@@QAEXABV?$function@$$A6AXABV?$basic_"
          "string@"
          "DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUTslBasic@@"
          "ABUTslRequest@@AAUTslResponse@@@Z@std@@@Z")) {
    setServiceHook = setServiceCallback.value().inline_hook();
    setServiceHook->install(onSetService);
  }

  if (auto propertyPost = iotMqtt->exports(
          "?PropertyPost@IoTMqtt@@QAE_NABUTslBasic@@ABUTslRequest@@@Z")) {
    propertyPostHook = propertyPost.value().inline_hook();
    propertyPostHook->install(onPropertyPost);
  }

  if (auto eventPost = iotMqtt->exports(
          "?EventPost@IoTMqtt@@QAE_NABUTslBasic@@ABUTslRequest@@@Z")) {
    eventPostHook = eventPost.value().inline_hook();
    eventPostHook->install(onEventPost);
  }

  if (auto propertyGet =
          iotMqtt->exports("?PropertyGet@IoTMqtt@@QAE_NABUTslBasic@@"
                           "ABUTslRequest@@AAUTslResponse@@@Z")) {
    propertyGetHook = propertyGet.value().inline_hook();
    propertyGetHook->install(onPropertyGet);
  }

  if (auto serviceCall =
          iotMqtt->exports("?ServiceCall@IoTMqtt@@QAE_NABUTslBasic@@"
                           "ABUTslRequest@@AAUTslResponse@@@Z")) {
    serviceCallHook = serviceCall.value().inline_hook();
    serviceCallHook->install(onServiceCall);
  }

  if (auto publishCustom = iotMqtt->exports(
          "?PublishCustom@IoTMqtt@@QAE_NABV?$basic_string@DU?$char_traits@D@"
          "std@@V?$allocator@D@2@@std@@00@Z")) {
    publishCustomHook = publishCustom.value().inline_hook();
    publishCustomHook->install(onPublishCustom);
  }

  showMainToast();
};
}; // namespace seeob::seewo