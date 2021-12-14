#include <vector>
#include <node.h>

#include "solutions/Solutions.hpp"
#include "Parsers.hpp"

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Number;

template<class T> void Algorithm(const v8::FunctionCallbackInfo<Value>& args, double (*method)(const std::vector<T>&))
{
    if(method == nullptr)
    {
        printf("Method is null\n");
        return;
    }
    const Local<Object> array = Parsers::GetArrayFromArgs(args, 0);
    std::vector<T> input;
    bool success = Parsers::ArrayTo(args.GetIsolate(), array, input);
    if(!success)
    {
        printf("Couldnt change to array. Exiting\n");
        return;
    }
    double answer = (*method)(input);
    args.GetReturnValue().Set(Number::New(args.GetIsolate(), answer));
}


template<class T> void Algorithm2(const v8::FunctionCallbackInfo<Value>& args, double (*method)(const T&))
{
    if(method == nullptr)
    {
        printf("Method is null\n");
        return;
    }
    const Local<Object> firstArg = args[0]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked();
    T input;
    bool success = Parsers::GetValue(args.GetIsolate(), firstArg, input);
    if(!success)
    {
        printf("Couldnt change to correct type. Exiting\n");
        return;
    }
    double answer = (*method)(input);
    args.GetReturnValue().Set(Number::New(args.GetIsolate(), answer));
}

#define NODE_GLUE_METHOD(exports, name, func, type) NODE_SET_METHOD(exports, name, [](const FunctionCallbackInfo<v8::Value>& args){ Algorithm<type>(args, func); })
#define NODE_GLUE_METHOD2(exports, name, func, type) NODE_SET_METHOD(exports, name, [](const FunctionCallbackInfo<v8::Value>& args){ Algorithm2<type>(args, func); })



void Initialize(Local<Object> exports) {
    NODE_GLUE_METHOD(exports, "getDepth", Solutions::getDepth, double);
    NODE_GLUE_METHOD(exports, "getDepthByWindow", Solutions::getDepthByWindow, double);
    NODE_GLUE_METHOD(exports, "getPositionProduct", Solutions::getPositionProduct, types::CommandLine);
    NODE_GLUE_METHOD(exports, "getPositionWithAim", Solutions::getPositionWithAim, types::CommandLine);
    NODE_GLUE_METHOD(exports, "getBitAverageThing", Solutions::getBitAverageThing, int);
    NODE_GLUE_METHOD2(exports, "getWinningBingoBoard", Solutions::getWinningBingoBoard, types::BingoBoardSets);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}  // namespace demo