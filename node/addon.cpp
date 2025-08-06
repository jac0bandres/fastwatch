#include "fastwatch.h"
#include "node_modules/node-addon-api/napi.h"

Napi::ThreadSafeFunction tsfn;

void fastwatch_c_callback(const char* path, const char* event) {
    tsfn.BlockingCall([=](Napi::Env env, Napi::Function jsCallback) {
        jsCallback.Call({
            Napi::String::New(env, path),
            Napi::String::New(env, event)
        });
    });
}

Napi::Value Start(const Napi::CallbackInfo& info) {
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

    fastwatch_start(path.c_str(), 1, fastwatch_c_callback);
    
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
    exports.Set("start", Napi::Function::New(env, Start));
    exports.Set("stop", Napi::Function::New(env, Stop));
    return exports;
}

NODE_API_MODULE(fastwatch, Init);