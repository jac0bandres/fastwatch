#include "fastwatch.h"
#include "node_modules/node-addon-api/napi.h"
#include <cstdint>
#include <format>
#include <iostream>

Napi::ThreadSafeFunction tsfn;
Napi::ObjectReference eventEnumMapRef;

void fastwatch_c_callback(const char* path, fastwatch_event_t event) {
    tsfn.BlockingCall([=](Napi::Env env, Napi::Function jsCallback) {
        Napi::Object eventEnumMap = eventEnumMapRef.Value();
        Napi::Value eventValue = eventEnumMap.Get(event);

        jsCallback.Call({
            Napi::String::New(env, path),
            eventValue
        });
    });
}

Napi::Object CreateEventEnum(Napi::Env env) {
    Napi::Object eventEnum = Napi::Object::New(env);
    eventEnum.Set("CREATE", Napi::Number::New(env, static_cast<int>(FASTWATCH_EVENT_CREATED)));
    eventEnum.Set("MODIFY", Napi::Number::New(env, static_cast<int>(FASTWATCH_EVENT_MODIFIED)));
    eventEnum.Set("DELETE", Napi::Number::New(env, static_cast<int>(FASTWATCH_EVENT_DELETED)));
    eventEnum.Set("MOVE", Napi::Number::New(env, static_cast<int>(FASTWATCH_EVENT_MOVED)));
    return eventEnum;
}

Napi::Object CreateEventEnumMap(Napi::Env env, Napi::Object eventEnum) {
    Napi::Object eventEnumMap = Napi::Object::New(env);
    Napi::Array propertyNames = eventEnum.GetPropertyNames();

    for (uint32_t i = 0; i < propertyNames.Length(); ++i) {
        Napi::Value key = propertyNames.Get(i);
        Napi::Value value = eventEnum.Get(key);
        eventEnumMap.Set(value, key);
    }

    return eventEnumMap;
}

Napi::Value Watch(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (!info[0].IsString() || !info[1].IsFunction()) {
        Napi::TypeError::New(env, "Expected (string, function)").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string path = info[0].As<Napi::String>();
    Napi::Function callback = info[1].As<Napi::Function>();

    tsfn = Napi::ThreadSafeFunction::New(
        env, callback, "fastwatch_callback", 0, 1
    );

    fastwatch_watch(path.c_str(), 1, fastwatch_c_callback);
    
    return env.Undefined();
}

Napi::Value Stop(const Napi::CallbackInfo& info) {
    fastwatch_stop();
    if (tsfn) {
        tsfn.Release();
    }
    return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::Object eventEnum = CreateEventEnum(env);
    Napi::Object eventEnumMap = CreateEventEnumMap(env, eventEnum);
    eventEnumMapRef = Napi::Persistent(eventEnumMap);

    exports.Set("watch", Napi::Function::New(env, Watch));
    exports.Set("stop", Napi::Function::New(env, Stop));
    exports.Set("EventType", CreateEventEnum(env));
    return exports;
}

NODE_API_MODULE(fastwatch, Init);