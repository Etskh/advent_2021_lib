#pragma once

#include <node.h>
#include <string>

#include "Types.hpp"

namespace Parsers {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
using v8::MaybeLocal;

Local<Object> GetArrayFromArgs(const FunctionCallbackInfo<Value>& args, int index);

bool IsIt(Isolate* isolate, const char* left, v8::Local<v8::String>& right);

types::EDirectionCommand ToDirection(Isolate* isolate, v8::Local<v8::String>& string);

template<class T>
bool GetValue(Isolate* isolate, const Local<Object>& input, T& output)
{
    printf("Not implemented!\n");
    return false;
}

template<> bool GetValue(Isolate* isolate, const Local<Object>& input, int& output);
template<> bool GetValue(Isolate* isolate, const Local<Object>& input, double& output);
template<> bool GetValue(Isolate* isolate, const Local<Object>& input, types::CommandLine& output);
template<> bool GetValue(Isolate* isolate, const Local<Object>& input, std::wstring& output);
template<> bool GetValue(Isolate* isolate, const Local<Object>& input, types::BingoBoardSets& output);

template<class T>
bool ArrayTo(Isolate* isolate, const Local<Object>& input, std::vector<T>& output)
{
    if(isolate == nullptr)
    {
        printf("Error: isolate is null\n");
        return false;
    }
    const auto context = isolate->GetCurrentContext();
    const Local<String> sizeStr = Local<String>(String::NewFromUtf8(isolate, "length").ToLocalChecked());
    MaybeLocal<Number> sizeNum = input->Get(context, sizeStr).ToLocalChecked()->ToNumber(context);
    size_t size = static_cast<size_t>(sizeNum.ToLocalChecked()->Value());

    for(int i=0; i<size; i++) {
        Local<Object> lineObject = input->Get(context, i).ToLocalChecked()->ToObject(context).ToLocalChecked();
        T t;

        GetValue(isolate, lineObject, t);

        output.push_back(t);
    }

    return true;
}


} // end parsers