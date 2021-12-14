#include "Parsers.hpp"

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


bool Parsers::IsIt(Isolate* isolate, const char* left, v8::Local<v8::String>& right)
{
    return right->StringEquals(Local<String>(String::NewFromUtf8(isolate, left).ToLocalChecked()));
}

types::EDirectionCommand Parsers::ToDirection(Isolate* isolate, v8::Local<v8::String>& string)
{
    if(IsIt(isolate, "forward", string)) {
        return types::FORWARD;
    }
    else if(IsIt(isolate, "down", string)) {
        return types::DOWN;
    }
    else if(IsIt(isolate, "up", string)) {
        return types::UP;
    }

    return types::UNKNOWN;
}


template<> bool Parsers::GetValue(Isolate* isolate, const Local<Object>& input, int& output)
{
    // Context
    const v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    // TODO: Do some checking
    output = input->ToNumber(context).ToLocalChecked()->Value();
    
    return true;
}

template<> bool Parsers::GetValue(Isolate* isolate, const Local<Object>& input, double& output)
{
    // Context
    const v8::Local<v8::Context> context = isolate->GetCurrentContext();
    output = input->ToNumber(context).ToLocalChecked()->Value();
    return true;
}

template<> bool Parsers::GetValue(Isolate* isolate, const Local<Object>& input, std::wstring& output)
{
    const int BUFFER_SIZE = 128;
    uint16_t buffer[BUFFER_SIZE];

    // Context
    const v8::Local<v8::Context> context = isolate->GetCurrentContext();
    int length = input->ToString(isolate->GetCurrentContext()).ToLocalChecked()->Write(isolate, buffer, 0, BUFFER_SIZE);

    for(size_t i=0; i<length; i++)
    {
        output[i] = buffer[i];
    }

    return true;
}

template<> bool Parsers::GetValue(Isolate* isolate, const Local<Object>& input, types::BingoBoardSets& output)
{
    // input

    return false;
}

template<> bool Parsers::GetValue(Isolate* isolate, const Local<Object>& input, types::CommandLine& output)
{
    // Names for the commands
    static const Local<String> commandKey = Local<String>(String::NewFromUtf8(isolate, "command").ToLocalChecked());
    static const Local<String> valueKey = Local<String>(String::NewFromUtf8(isolate, "value").ToLocalChecked());

    // Context
    const v8::Local<v8::Context> context = isolate->GetCurrentContext();

    // Get command
    Local<String> commandString = input->Get(context, commandKey).ToLocalChecked()->ToString(context).ToLocalChecked();
    types::EDirectionCommand command = ToDirection(isolate, commandString);

    // Get value
    double value = input->Get(context, valueKey).ToLocalChecked()->ToNumber(context).ToLocalChecked()->Value();

    // And return
    output = std::make_pair(command, value);
    return true;
}

Local<Object> Parsers::GetArrayFromArgs(const FunctionCallbackInfo<Value>& args, int index)
{
    Local<Object> array;
    Isolate* isolate = args.GetIsolate();
    if(args.kArgsLength < index)
    {
        printf("Args length < %d; exiting\n", index);
        return array;
    }

    if(!args[index]->IsArray())
    {
        printf("Argument #%d isn't an array\n", index);
        return array;
    }
    
    return args[index]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
}
