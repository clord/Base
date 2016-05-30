![](Resources/wtfm.jpg)
# Introduction

This documents describes the Next Audio Labs coding standards. At no point does this pretend to be the end-all/be-all of coding standards. Some of it comes from years of learning the craft, some of it is arbitrary and was only chosen because of personal preference.

Either way, it is the law of the land and must be strictly adhered to, unless this document is modified to reflect any changes or evolution.

During the transition to this standard, some of the code might not correctly enforce/use the coding standards. It is understood that if the code and this document differ, this document is the prevailing authority and the code should be modified.

# Overall Philosophy

The main points dictating the overall philosophy for the Next codebase are:

* **Be consistent:** Sticking to this document will help in that respect but in general, stick to one style/method/process. Code should be easy to navigate because it should all be consistent and familiar.
* **Fail early:** If something has gone wrong or is not the way it should be, don't assume calling code will deal with the situation. Fail early and fail hard to prevent unpredictable states or behaviors  (see "Dead Programs Tell No Lies" in [HUN99] page 120).
* **Make your code defensive**: Don't assume any state, any input or any return values. Unless something is documented and guaranteed to work a specific way, test it and assert to make sure it is (see "Assertive Programming" in [HUN99] page 122). Assertions should ALWAYS be on, even in Release builds.
* **Don't let your API be used incorrectly:** Method signatures should be non-ambiguous to make sure users of your classes cannot use them incorrectly. Be verbose, be descriptive and don't allow arguments to have multiple meanings/uses.
* **Don't live with broken windows:** Formatting, naming and any other standards can be a pain sometimes. But committing code that doesn't adhere to the standard or that contains some hack of some sort is an invitation for others to think it's ok to do it too. Fix broken windows before you commit your code (see "Software Entropy" in [HUN99] page 4).
* **Don't repeat yourself:** Duplicated code makes it harder to debug, optimize and read the code. Fixes and optimizations have to be applied in multiple places and inlined copies of the same code could be made easier to read by each calling the same method instead. (see "The Evils of Duplication" in [HUN99] page 26). 
   
# Style & Formatting

### Files

* **Header files** use the `.hpp` extension.
* **Source files** use the `.cpp` extension.

##### All files should have a standard header at the top.

There are two types of files: The ones which are confidential and part of our internal codebase and the ones that are made publicly available under the **MIT license**.

###### Confidential files should use this header:

```
//
//  Copyright (c) 2013-2016 Next Audio Labs, LLC. All rights reserved.
//
//  This file contains confidential and proprietary information of Next
//  Audio Labs, LLC ("Next"). No use is permitted without express written
//  permission of Next. If you are not a party to a Confidentiality/
//  Non-Disclosure Agreement with Next, please immediately delete this
//  file as well as all copies in your possession. For further information,
//  please email info@next.audio.
//
```

###### Publicly released files should use this header:

```
//
//  Copyright (c) 2015-2016 Next Audio Labs, LLC. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
```

### Naming conventions

* **Variables and methods** use the `lowerCamelCase` convention.
* **Class names and namespaces** use the `UpperCamelCase`.
* **Compiler macros** use the `UPPER_CASE_SNAKE` convention.
* **Use meaningful, pronounceable and intention revealing names for methods and variables.**Method names should always read like actions and variables like object names (see "Meaningful Names" in [MAR09] page 17). 
* **Don't use abreviations or single letter names.** Everything should be spelled out.
* **Methods names should explain the arguments used after them.** C++ unfortunately doesn't support named arguments. This makes code very hard to read when looking at a calling method since arguments after the first one do not have any context. For this, we add the description in the method name itself. This can get pretty hard to read past a certian number of arguments which is why methods should ideally only have up to two arguments (See below in the **Coding Conventions** section).
 
```
    // --- Like this
    void processElementAndLogMessagesIn(const Element& element, MessageLog& log)
    {
        integer startIndex = 0;
        for (auto index = startIndex; index < 12; ++index) {
            ...
        }
    }
    
    // --- NOT like this
    void process(const Element& element, MessageLog& log)
    {
        integer idx = 0;
        for (auto i = idx; i < 12; ++i) {
            ...
        }
    }

```

### Whitespace

* **Tabs** are 4 characters and should be spaces only.
* **Line-endings** should be OS X/UNIX (LF).
* **Last line of all files should be a newline.** Some compilers, like clang,complain if that's not the case.
* **Pointer and reference symbols** should be attached to the type:
 
```
    MyClass& myVar;         // --- Like this
    character* otherVar = nullptr;
    MyType& aMethod(MyOtherType& aVar);

    MyClass &myVar;         // --- NOT like this
    character *otherVar = nullptr;
    MyType &aMethod(MyOtherType &aVar);
```
    
### Code Layout

* **`{ }` are always required for blocks**, even single lines or switch statements.
* **class definition and method declaration** use curly brackets on seperate lines:

```
    class MyClass
    {
        ...
    }

    void myMethod(void)
    {
        ...
    }
```

* **statements** use an open curly bracket on the same like as the statement:

```
    if (true) {
        ...
    }
    else {
        ...
    }

    while (1) {
        ...
    }

    for (auto& var : vars) {
        ...
    }

    switch (c) {
        case 0: {
            ...
            break;
        }
        case 1: {
            ...
            break;
        }
        default: {
            ...
        }
    }
```

* **`return` statements** don't use any parenthesis.

```
    // --- Like this
    return localLog.count == 3;
    
    // --- NOT like this
    return (localLog.count == 3);
```
* **Pragmas are used to seperate code sections** both in the headers and the implementation. In headers the order of declaration is:

```
    class MyClass : NxA::Object
    {
        #pragma mark Factory Methods
        ...

        #pragma mark Class Methods
        ...

        #pragma mark Operators
        ...

        #pragma mark Instance Methods  
        ...
    }
```

If the code overrides any methods from parent classes, those are placed after their respective pragma section in reverse order of in-heritence.

```
    class MyClass : NxA::Object
    {
        #pragma mark Factory Methods
        ...
    
        #pragma mark Overriden Object Factory Methods
        ...

        #pragma mark Instance Methods  
        ...

        #pragma mark Overriden Object Instance Methods
        ...
    }
```

* **Don't declare multiple variables on one line**, even if they have the same type.
* **Keep vertical distance short.** Concepts that are closely related should be kept close together. This takes precendence over line length. While being able to compare files side by side is useful is a few limited cases, we prefer to **NOT** to put a hard limit on line length. A soft limit is set at 120 chracters but again, vertical distance for readability is more important that artificially staying below this limit (see "Vertical Distance" in [MAR09] page 80).
* **When local variables are used in `if()`, `for()` or `return` statements**, they should be initialized on the line right above those statements, if possible, with no blank line between the two.

```
    // --- Like this
    auto messages = localLog.messages;
    for (auto message : message) {
        auto text = message.text;
        if (text.length) {
            ...
        }
    }

    auto count = localLog.count;
    printf("%ld", count);
    
    auto result = localLog.warningAsString;
    return result;
    
    // --- NOT like this
    auto count = localLog.count;
    auto messages = localLog.messages;

    for (auto message : message) {
        auto text = message.text;

        if (text.length) {
            ...
        }
    }

    printf("%ld", count);

    auto result = localLog.warningAsString;

    return result;
```

* **Limit Variable Scope.** Similarly to trying to limit vertical distance, objects should not stay around longer than they need to so variables should always be declared as late as possible. Any variables only used inside a given scope should be declared inside that scope, unless the scope is a loop and the variable's value is unaffected by the loop in which case it is more optimal to declare the object outside of the loop.

```
    // --- Like this
    auto formatter = Formatter();
    for (auto& text : strings) {
        auto formattedVersion = formatter.format(test);
        ...
    }
    
    // --- NOT like this
    auto formattedVersion = String::emptyString();
    for (auto& text : strings) {
        auto formatter = Formatter();
        
        formattedVersion = formatter.format(test);
        ...
    }
```

* **Local variables should be used to store most returned values** from methods so that they can be more easily inspected during debugging and to make the code more readable. One clear exception to this is detailed in the **Modern C++** section below where doing this can prevent the compiler from using the move operator.

```
    // --- Like this
    auto formattedText = String::formatString("Hello");
    log.addMessage(formattedText);
        
    // --- NOT like this
    log.addMessage(String::formatString("Hello"));
```

* **Organize code so that it reads top to bottom.** As much as possible, in both the declarations and definitions and within each pragma section described above, the code should be organised so that main methods are found at the top and sub-methods are found underneath them (see "Vertical Ordering" in [MAR09] page 84).

### Includes

* **Header files** should always contains a `#pragma once` statement at the top, underneath the file header.
* **Double quotes** `""` should be used for includes from the same library/module and `<>` for any system external includes.
* **System/external includes** should be placed above regular/same module includes and a blank line should seperate each type of include
* **Include paths** should be fully qualified including the library's base directory and not relative to the file's directory or without any path.
* **Each module/library should have a single include file**, named after the module or library and which includes all the relevant include files for that module/library.
* **Forward declare**, underneath all include statements, when possible instead of including.
* For example, in a file from the `Persistence` library:

```
    // -- This will include all the relevant headers for the Base library.
    #include <Base/Base.hpp>
    
    #include "Persistence/PersitentObject.hpp"

    class PersistentContext;    
```

### Comments

* **Code comments should use `// -- My comment.`** and not the block notation `/* ... */`. This allows for easily commenting out block of code during development.
* **Avoid using comments** (see 'Comments' in the **Code Conventions** section below).

# Code Conventions

### Namespaces

* Always at least use the `NxA` namespace.
* use `NXA_ENTER_NAMESPACE(NxA);` and `NXA_EXIT_NAMESPACE;`
 instead of `namespace { ... }`. These avoid editors like Xcode tying to indent the content of the namespace for no reason.
* `using namespace ...` should be placed underneath the includes and never in header files.

### Operators

* **Avoid overloading operators** unless the behavior is easy to predict and non obscure. More often than not overloading seems clever but affect readability if the assumption made by the reader on how the operator works is incorrect.
* **Don't use C++ stream operators** `<<` or `>>` for input/output. This is a highly unreadable and produces a syntax that looks nothing like no other C++ code. This is a good example of why operator overloading should be avoided in a lot of cases.

### Methods

* **Methods should be small**, have 2 arguments at the most, do only one thing and have no hidden side effects.
* **Pass object arguments by reference** whenever possible.
* **Use const** everywhere it is warranted, both for arguments and methods.
* **Don't pass external vendor types/classes** as arguments outside of a class or method. Any such types should be encapsulated into our own types.

### Memory Management & Pointers

* **Do not use raw pointers** or allocate your own memory.
* **Raw pointers should use and test against `nullptr`** and not NULL or 0 if you do use them for interfacing with third party libraries.
* **Do not use global data.** This can cause issues with multi-threading and is a good rule even if the code is not multi-threaded. It could be later on.
* **Do not use new/delete.** Creating new objects should only use a factory method which returns a `Pointer` to the object.
* **Factory methods should use `make_shared`** to create the new object.
* **In a factory method, pass the raw pointer as the argument** of a `Pointer` constructor to keep the code exception safe.
* **Never store, use or keep a raw pointer to anything.** Object is the only class allowed to do this in its private instance variables.
* **Do not declare anything as having automatic storage.** All objects must be pointed to via a `Pointer` and created via a factory method.
* **Do not use `NullablePointer` as an argument or a return value.** These are meant to be used only inside a given method or inside an `internal` class and not exposed to the outside. This frees any outside code from having to check for valid pointers returned to them as `Pointer` is never invalid.
* **Always use `this->`** for accessing instance variables and instance methods. This make it clear that you are accessing a member of the class and not some local method or variable.
* **Use `internal->`** (without `this->` in that case) for accessing the internal class. This makes it easy to distinguish between the two.

### Miscellaneous

* **Avoid using compiler macros.** 
* **Always use the types in types.h** instead of built in types.
* **Always use pre-increment operator instead of the post increment, when possible.** Pre-increment is often [faster](http://blog2.emptycrate.com/content/why-i-faster-i-c) than post-increment.
* **Boolean tests do not test against `true` or `false`** and should just use `!` or nothing.

```
    // --- Like this
    if (!correct) {
        ...
    }
    else if (finished) {
        ...
    }
        
    // --- NOT like this
    if (correct == false) {
        ...
    }
    else if (finished == true) {
        ...
    }
```

### Comments

* **Avoid using comments** (see "Comments" in [MAR09] page 53). Comments are just lies waiting to happen. You certainly do not have to teach someone reading the code how code works and you do not have to repeat information that is already there.
* **Let the code be the comments** by using descriptive names and break up code into sub-methods instead.

```
    // --- Like this
    decimal timeInSeconds = 0.0f;
    
    if (!foundItems) {
        parseItemsInList(list); 
        
        time = time + 1.0f;
        ...
    }
        
    // --- NOT like this
    // -- Time in seconds
    decimal time = 0.0f;

    // -- If we found some items
    if (!found) {
        integer c = 0;
        
        // -- We go thru every item and parse it
        for (auto& i : list) {
            i->parse();
        }
        
        // -- We increment the time
        time = time + 1.0f;
        ...
    }
```

* **TODO comments are ok**. They can even be commited to source control.

```
    // -- TODO: Optimize this.
```

* **Use comments only to explain context.** When something is non-obvious or might not seem logical at first sight.

```
    TagLib::RIFF::WAV::File file(this->filePath->toUTF8(),
                                 true,
                                 TagLib::AudioProperties::ReadStyle::Fast);
    ...
    
    // -- This is misleading. It doesn't actually save anything to disk.
    // -- Instead, real saving takes place in the file's desctructor. #ugh
    file.save();
```

# Classes

* **All classes** should at least inherit from `NxA:Object`.
* **There should never be any public constructors for classes.** Use factory methods instead.
* **There should never be any private or protected members for classes.** This goes in the internal class.
* **Only declare or use public instance variables in internal classes.**
* **In non-internal classes those should be accessor methods (getters, setters)** to the instance variables contained in the internal/private class.
* **A base class destructor should be either public and virtual**, or protected and nonvirtual.
* **Make your classes orthogonal:** Modifying one system or class should not affect another. This is where encapsulation and interface design are crucial. (see "Orthogonality" in [HUN99] page 34).
* **Minimize coupling between modules:** Any method of an object  should call only methods belonging to itself, any parameters that were passed in to the method, any objects it created or any durectly help component objects. (see "The Law of Demeter for Functions" in [HUN99] page 140).
* **Internal classes should always inherit from at least `InternalObject`.**
* **Internal class files** should be placed in a Internal subdirectory of their public class files.

# Modern C++ support

* **Use constexpr or typed enums** for constants.
* **Use the new iteration form** for `for()` loops instead of using iterators or indexes.

```
    for(auto& subTag : subTags) {
        ...
    }
```

* **Initialize member variables with the member initializer list** and not in the constructor.
* **Internal classes can give instance variables a default default value** in the class declarationto avoid having to set it in every constructor.

```
    struct InternalItem : public InternalObject {
        NXA_GENERATED_DESTRUCTOR_FOR_CLASS(InternalCrate);

        #pragma mark Instance Variables
        integer count = 0;

        ...
    };
```

* **Use Initializer Lists.** Initializer lists are significantly more efficient; reducing object copies and resizing of containers.
* **Enable move operations.** Move operations allow the compiler to avoid extra copies by moving temporary objects instead of copying them in certain cases. Certain coding choices we make (such as declaring our own destructor or assignment operator or copy constructor) prevents the compiler from generating a move constructor.
* **Reduce temporary objects** They can prevent the compiler from using a move operator.
* **Use `auto`.**

# Error Handling

* **Use `nothrow`** to indicate if your method does not throw.
* **Do not use return values as error codes.** Use exception handling instead.
* **Give the user helper methods** like `hasArtist()` to let the user make sure another method like `gerArtist()` will succeed or not.

# Unit Testing

* **Test your software** or your users will.
* **Design to test.**
* While **full blown TDD** is not strictly enforced or required, 100% coverage should be aimed for, especially for all low level classes.
* **Don't comment out unit tests when they fail.** Fix the code.
* **Tests should be placed in a Tests subdirectory** of the classes the tests relate to.
* **Use stubs and mocks** to make sure the tests only exercise the part of the code you want them to.

# Source Control & Versioning

* **Always commit one change at a time.** Don't do huge mega commits with tons of different changes in them. If while developing something you find the need for some other new functionality then stash your changes, commit the new functionality and pick back up the original change afterward.
* **Do not commit code with commented out sections**, or code that doesn't build or code that doesn't pass all the unit tests.
* **Be careful when committing files that are part of a git subtree**. The commit message will be visible in the commit list of the subtree's origin repo whcih may be a public repo.
* **Use [git-flow](http://nvie.com/posts/a-successful-git-branching-model/)**. Many git clients support it natively.
* **Always work in a local branch** and not in the develop branch directly.
![](Resources/git-model@2x.png)
* **Use version numbers** that are in the form x.y.z(b) where x is the main version number (1-~), y is the feature number (0-~), z is the hotfix number (0-~) and b is the build number.
* **Increase the feature number** if the change contains new features with or without bug fixes.
* **Increase the hotfix number** if the change only contains bug fixes.
* **Increase the build number** at every new user-facing build.
* **Unless you have direct push access** you should push your changes and commits via a pull request. Pull requests should only contain commits related to one task and only one task.

# Development Rules

* **Use tracer bullets.** When developing new systems, and especially collections of interconnected systems that depend on each other, try to get a dumbed-down stubbed version of the overall system working right away. Things can be hardcoded to begin with, a lot of functionality could be missing but aim to get a working system as quickly as possible. (see "Tracer Bullets" in [HUN99] page 48).
* **Try to keep existing code running at all times.** Don't embark on a huge task that will break your local codebase for days. Try to brak up the task into smaller ones that can each be implemented while keeping the code, and the unit tests, working.
 
# Compilation

* **All compiler warnings or static analyzer warnings** should be treated as errors.

# References

This is a list of references used throughout this document, in alphabetical order:

[MEY05] __"Effectice C++ Third Edition" by Scott Meyers__ (ISBN 978-0-321-33487-9, [Safari](https://www.safaribooksonline.com/library/view/effective-c-55/0321334876/), [Amazon](http://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876/ref=sr_1_1?ie=UTF8&qid=1431361209&sr=8-1&keywords=9780321334879))

[MAR09] __"Clean Code" by Robert C. Martin.__ (ISBN 978-013-235088-4, [Safari](https://www.safaribooksonline.com/library/view/clean-code/9780136083238/), [Amazon](http://www.amazon.com/Clean-Code-Handbook-Software-Craftsmanship/dp/0132350882/ref=sr_1_1?ie=UTF8&qid=1431316862&sr=8-1&keywords=9780132350884))

[MEY14] __"Effectice Modern C++" by Scott Meyers__ (ISBN 978-1-491-90399-5, [Safari](https://www.safaribooksonline.com/library/view/effective-modern-c/9781491908419/), [Amazon](http://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996/ref=sr_1_1?ie=UTF8&qid=1431361448&sr=8-1&keywords=9781491903995))

[HUN99] __"The Pragmatic Programmer" by Andrew Hunt & David Thomas__ (ISBN 978-0-201-61622-4, [Safari](https://www.safaribooksonline.com/library/view/the-pragmatic-programmer/020161622X/), [Amazon](http://www.amazon.com/Pragmatic-Programmer-Journeyman-Master/dp/020161622X/ref=sr_1_1?s=books&ie=UTF8&qid=1458411634&sr=1-1&keywords=the+pragmatic+programmer))
