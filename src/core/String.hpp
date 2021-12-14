#pragma once

#include <string>

/*

The goal is to have a set of classes that act as
pipeable objects with const-correctness, and will
conserve memory and performance by holding onto references
in the parent pipeable object in the current scope

The interfaces are light and have only references to
parent types, instantiated without a parent pipeable


String data = "1, 2, 3, 0, 4";

String dataWithoutZero = data
    .Split(",") // Creates an Array<String>
    .To<_number_>() // Creates an Array<_number_>
    .Filter([](data){ data != 0}) // Creates an Array<_number_>
    .Join(","); // Creates a String


Array<Type>
    Join -> String
    Map -> (same)
    Filter -> (same)
    Reduce -> Type
    ForEach -> void
    To<Type> -> Array<Type>

String
    Split -> Array<String>
    To<Type> -> Type (ends pipeline)
    Replace -> String

*/
class Pipeable
{
public:
    
};


template<class T>
class Pipelined : public T
{
public:
    Pipelined(Pipeable* parent);
    virtual ~Pipelined() {}

private:
    Pipeable* _parent;
};

template<class T>
Pipelined<T>::Pipelined(Pipeable* parent)
    : _parent(parent)
{
    // empty
}


class String : public Pipeable
{
public:
    typedef unsigned int Index;
    static enum Encoding {
        ASCII,
        UTF16,
    };

    String();
    String(const char* str);
    String(const String& copy); 
    ~String();

    String& operator=(const Pipelined<String>& string);

    Pipelined<String>& Replace(const char* dis, const char* dat) const;
};


int main() {

    String data = "x y";

    String helloworld = data
        .Replace("x", "hello")
        .Replace("y", "world");

    return 0;
}