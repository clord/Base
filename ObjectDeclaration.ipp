//
//  Copyright (c) 2015-2017 Next Audio Labs, LLC. All rights reserved.
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

#define nxa_internal static_cast<Internal*>(this->get())
#define NXA_INTERNAL_OBJECT_FOR(other) static_cast<Internal*>(other.get())

protected:
    // -- Forward declarations
    friend WeakReference<NXA_OBJECT_CLASS, NXA_OBJECT_INTERNAL_CLASS>;
    using Internal = NXA_OBJECT_INTERNAL_CLASS;
    friend Internal;

    // -- Protected Constructors & Destructors
    NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other);

public:
    #define NXA_STRINGIFY_SUB_MACRO(arg...) #arg
    #define NXA_STRINGIFY(arg...) NXA_STRINGIFY_SUB_MACRO(arg)
    static constexpr auto staticClassNameConst = NXA_STRINGIFY(NXA_OBJECT_CLASS);
    #undef NXA_STRINGIFY
    #undef NXA_STRINGIFY_SUB_MACRO

    // -- Constructors & Destructors
    NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS&);
    NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&&);
    NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&);
    ~NXA_OBJECT_CLASS();

    // -- Static Methods
    static const character* staticClassName()
    {
        return NXA_OBJECT_CLASS::staticClassNameConst;
    }

    // -- Operators
    NXA_OBJECT_CLASS& operator=(NXA_OBJECT_CLASS&&);
    NXA_OBJECT_CLASS& operator=(const NXA_OBJECT_CLASS&);
    bool operator==(const NXA_OBJECT_CLASS& other) const;
    inline bool operator!=(const NXA_OBJECT_CLASS& other) const
    {
        return !this->operator==(other);
    }

    // -- Instance Methods
    #if !defined(NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME)
        const character* className() const;
    #endif
    boolean classNameIs(const character* className) const;

    String description(const DescriberState&) const;
    String description() const;

    // -- Clean up any defines that were used.
    #undef NXA_OBJECT
    #undef NXA_OBJECT_CLASS
    #undef NXA_OBJECT_BASE_CLASS
    #undef NXA_OBJECT_INTERNAL_CLASS
    #undef NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

    #undef NXA_CAT_SUB_MACRO
    #undef NXA_CAT

    // -- Since this should placed at the beginning of the class definition,
    // -- we restore the private setting for subsequent content.
private:
