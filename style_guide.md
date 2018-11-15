# Style Guide

### Brackets
*Open brackets should **ALWAYS** start on a new line*

 ```c++
main
{
  for(unsigned int i=0; i<10; i++)
  {
    ...
  }
}
```

 *Always use { } brackets*
 ```c++
 //don't do this
if(flag)
  myFunc();

//always use { }
if(flag)
{
  myFunc();
}
 ```

### Classes
*First character of each word should be capital*

```c++
MyClass
```

*In the .cpp all functions should be in alphabetical order similar to the header file*
```c++
MyClass::MyClass()
{
}

~MyClass::MyClass()
{
}

int MyClass::getA()
{
}

void MyClass::setA()
{
}
```

### Constructos
*Don't use the variable initialization in the header file. Class member variables should be initialized within the .cpp file*

```c++
//don't do this!!! (MyClass.h)
class MyClass
{
  int x;
  int y;

  public:
    MyClass() : x(x), y(y);
}

//instead do this (MyClass.h)
class MyClass
{
  int x;
  int y;
  public:
    MyClass(int x, int y);
}

//MyClass.cpp
MyClass::MyClass(int x, int y)
{
  this->x = x;
  this->y = y;
}

```


### Functions
*First character of each word should be capital but **NOT** the first character*

```c++
void myFunction()
{

}
```

*When calling function with a lot of parameters, lines can get pretty long. So put each argument on a new line. The closing bracket should be on a new line too*
```c++
//don't do this
myInterestingFunc(myValueName1, myValueName2, myValueName3, myValueName4);

//do this instead
myInterestingFunc(
  myValueName1,
  myValueName2,
  myValueName3,
  myValueName4
);
```

*If Passing an object it should be passed as a reference when ever possible. Try not use a pointer for the parameters*
```
void myFunc(MyObject& obj)
{

}
```

### Variables
*First character of each word should be capital but **NOT** the first character*

 ```c++
 int myValue = 3;
 ```

### Constants
*const or constexpr variables should be in all uppercase with an underscore between each word*

```c++
const int NUMBER_OF_PLAYERS = 10;
```

### File Naming
*All files must have the first character of each word capital. Also each .cpp file should have a corresponding .h file*
```
MyClass.cpp
MyClass.h
```

### Header Files
*Never use ```using``` in a header file*

* *The private variables should always be at the top before public. The order of variables doesn't matter, but they should always be on a new line*
* *public should have this order*
  * *variables*
  * *constructor*
  * *destructor*
  * *functions (in alphabetical order)*

```
class MyClass
{
  int b;
  int a;

  public :
    int gloablVal = 10;

    MyClass();
    ~MyClass();
    int getA();
    void setA();

  protected :
    int c;
};
```

### Spacing Indent
*Use **2 spaces** for indenting and don't use tabs*
```c++
function myFunc()
{
  int a = 1;
  for(unsigned int i=0; i<10; i++)
  {
    std::cout << a << std::endl;
  }
}
```

### Arithmetic
*Use round brackets to make it obvious how the values are being used*
```c++
//don't do this
float result = 10 + 5 / 2 * 4;

//always use brackets
float result = 10 + ((5 / 2) * 4);
```

### Namespaces
*Namespaces should be all lowercase and use and underscore between each word. Always declare the namespace in the header file*
```c++
namespace my_project
{
  class MyClass
  {
    public:
      static const double PI = 3.14159;
  }
}
```

### Avoid Compiler Macros
*If possible never use #define for variables*

```c++
//don't do this
#define PI 3.14159;
```
