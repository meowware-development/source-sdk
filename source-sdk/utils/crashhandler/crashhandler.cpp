#include "crashhandler.hpp"
#include "../format/format.hpp"
#include <unordered_map>

void utils::crashhandler::Initalize()
{
	AddVectoredExceptionHandler(0, ExceptionHandler);
}

static std::unordered_map<DWORD, const char*> exceptionText = {
	{EXCEPTION_ACCESS_VIOLATION, "Acces violation"},
	{EXCEPTION_ARRAY_BOUNDS_EXCEEDED, "Array bounds were exceeded"},
	{EXCEPTION_BREAKPOINT, "A breakpoint was hit"},
	{EXCEPTION_DATATYPE_MISALIGNMENT, "Misaligned datatype"},
	{EXCEPTION_FLT_DENORMAL_OPERAND, "Denormal floating point operand"},
	{EXCEPTION_FLT_DIVIDE_BY_ZERO, "Float division by zero"},
	{EXCEPTION_FLT_INEXACT_RESULT, "Inexact floating point result"},
	{EXCEPTION_FLT_INVALID_OPERATION, "Invalod floating point operation"},
	{EXCEPTION_FLT_OVERFLOW, "Floating point overflow"},
	{EXCEPTION_FLT_STACK_CHECK, "Stack overflown by the result of a floating point operation"},
	{EXCEPTION_FLT_UNDERFLOW, "Floating point underflow"},
	{EXCEPTION_ILLEGAL_INSTRUCTION, "Illegal instruction"},
	{EXCEPTION_IN_PAGE_ERROR, "Tried to access a non-present page"},
	{EXCEPTION_INT_DIVIDE_BY_ZERO, "Division by zero"},
	{EXCEPTION_INT_OVERFLOW, "Integer overflow"},
	{EXCEPTION_NONCONTINUABLE_EXCEPTION, "Non-continuable exception, tried to resume"},
	{EXCEPTION_PRIV_INSTRUCTION, "Can't execute instruction in current machine mode"},
	{EXCEPTION_SINGLE_STEP, "A trace trap or other single-instruction mechanism signaled that one instruction has been executed"},
	{EXCEPTION_STACK_OVERFLOW, "Stack overflow"}
};

LONG WINAPI utils::crashhandler::ExceptionHandler(EXCEPTION_POINTERS* exception)
{
	MessageBoxA(0, FORMAT("Exception occured at 0x{:X}!\nEAX: 0x{:X}\nECX: 0x{:X}\nESP: 0x{:X}\nEIP: 0x{:X}\nException: {}",
		reinterpret_cast<DWORD>(exception->ExceptionRecord->ExceptionAddress), exception->ContextRecord->Eax, exception->ContextRecord->Ecx, exception->ContextRecord->Esp,
		exception->ContextRecord->Eip, exceptionText[exception->ExceptionRecord->ExceptionCode]), "Exception occured!", MB_ICONERROR);

	// Continue handler search.
	return 0;
}
