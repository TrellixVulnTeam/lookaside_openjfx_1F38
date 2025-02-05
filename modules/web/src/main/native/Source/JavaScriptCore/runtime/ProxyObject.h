/*
 * Copyright (C) 2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ProxyObject_h
#define ProxyObject_h

#include "JSGlobalObject.h"
#include "JSObject.h"

namespace JSC {

class ProxyObject : public JSNonFinalObject {
public:
    typedef JSNonFinalObject Base;

    const static unsigned StructureFlags = Base::StructureFlags | OverridesGetOwnPropertySlot | TypeOfShouldCallGetCallData | InterceptsGetOwnPropertySlotByIndexEvenWhenLengthIsNotZero;

    static ProxyObject* create(ExecState* exec, Structure* structure, JSValue target, JSValue handler)
    {
        VM& vm = exec->vm();
        ProxyObject* proxy = new (NotNull, allocateCell<ProxyObject>(vm.heap)) ProxyObject(vm, structure);
        proxy->finishCreation(vm, exec, target, handler);
        return proxy;
    }

    static Structure* createStructure(VM& vm, JSGlobalObject* globalObject, JSValue prototype)
    {
        return Structure::create(vm, globalObject, prototype, TypeInfo(ProxyObjectType, StructureFlags), info(), NonArray | MayHaveIndexedAccessors);
    }

    DECLARE_EXPORT_INFO;

    JSObject* target() { return m_target.get(); }
    JSValue handler() { return m_handler.get(); }

    static void put(JSCell*, ExecState*, PropertyName, JSValue, PutPropertySlot&);
    static void putByIndex(JSCell*, ExecState*, unsigned propertyName, JSValue, bool shouldThrow);
    void putByIndexCommon(ExecState*, JSValue thisValue, unsigned propertyName, JSValue putValue, bool shouldThrow);

private:
    ProxyObject(VM&, Structure*);
    void finishCreation(VM&, ExecState*, JSValue target, JSValue handler);

    static bool getOwnPropertySlot(JSObject*, ExecState*, PropertyName, PropertySlot&);
    static bool getOwnPropertySlotByIndex(JSObject*, ExecState*, unsigned propertyName, PropertySlot&);
    static CallType getCallData(JSCell*, CallData&);
    static ConstructType getConstructData(JSCell*, ConstructData&);
    static bool deleteProperty(JSCell*, ExecState*, PropertyName);
    static bool deletePropertyByIndex(JSCell*, ExecState*, unsigned propertyName);
    static bool preventExtensions(JSObject*, ExecState*);
    static bool isExtensible(JSObject*, ExecState*);
    static void visitChildren(JSCell*, SlotVisitor&);

    bool getOwnPropertySlotCommon(ExecState*, PropertyName, PropertySlot&);
    bool performInternalMethodGetOwnProperty(ExecState*, PropertyName, PropertySlot&);
    bool performHasProperty(ExecState*, PropertyName, PropertySlot&);
    template <typename DefaultDeleteFunction>
    bool performDelete(ExecState*, PropertyName, DefaultDeleteFunction);
    template <typename PerformDefaultPutFunction>
    void performPut(ExecState*, JSValue putValue, JSValue thisValue, PropertyName, PerformDefaultPutFunction);
    bool performPreventExtensions(ExecState*);
    bool performIsExtensible(ExecState*);

    WriteBarrier<JSObject> m_target;
    WriteBarrier<Unknown> m_handler;
    bool m_isCallable : 1;
    bool m_isConstructible : 1;
};

} // namespace JSC

#endif // JSPromise_h
