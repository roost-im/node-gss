#include "gss.h"

namespace node_gss {

v8::Handle<v8::Value> ImportName(const v8::Arguments& args) {
  v8::HandleScope scope;

  if (args.Length() < 3) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New(
        "Wrong number of arguments")));
    return scope.Close(v8::Undefined());
  }

  gss_buffer_desc buffer;
  if (!NodeBufferAsGssBuffer(args[0], &buffer)) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New(
        "Expected Buffer as first argument")));
    return scope.Close(v8::Undefined());
  }

  if (!OidHandle::HasInstance(args[1])) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New(
        "Expected OID as second argument")));
    return scope.Close(v8::Undefined());
  }
  OidHandle* oid = node::ObjectWrap::Unwrap<OidHandle>(args[1]->ToObject());

  if (!NameHandle::HasInstance(args[2])) {
    v8::ThrowException(v8::Exception::TypeError(v8::String::New(
        "Expected NameHandle as third argument")));
    return scope.Close(v8::Undefined());
  }
  NameHandle* name = node::ObjectWrap::Unwrap<NameHandle>(args[2]->ToObject());

  OM_uint32 minor;
  OM_uint32 major = gss_import_name(&minor, &buffer, oid->get(), &name->get());
  
  v8::Local<v8::Object> ret = v8::Object::New();
  ret->Set(v8::String::NewSymbol("major"), v8::Integer::New(major));
  ret->Set(v8::String::NewSymbol("minor"), v8::Integer::New(minor));
  return scope.Close(ret);
}

void NameInit(v8::Handle<v8::Object> exports) {
  exports->Set(v8::String::NewSymbol("importName"),
               v8::FunctionTemplate::New(ImportName)->GetFunction());
}

}  // namespace node_gss
