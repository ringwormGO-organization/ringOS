#pragma once

void Panic(const char* panicMessage);
void Panic(const char* panicMessage, unsigned long int code);
void MorePanic();

#define PANIC(b) (Panic(b))

#define ASSERT_NOMSG(x, msg) (!(x) ? PANIC(msg) : static_cast<void>(const_cast<char*>(msg)))
#define ASSERT_MSG(x) (!(x) ? PANIC("Assertion failed: " #x) : static_cast<void>(x))

#define GET_MACRO(_1,_2,NAME,...) NAME
#define ASSERT(...) GET_MACRO(__VA_ARGS__, ASSERT_NOMSG, ASSERT_MSG)(__VA_ARGS__)