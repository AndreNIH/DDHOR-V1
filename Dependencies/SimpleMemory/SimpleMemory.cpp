#include "SimpleMemory.h"

sm_dword_t sm::internal::process_id()
{
	return sm_convert<sm_dword_t>(GetCurrentProcessId());
}

sm_handle_t sm::internal::process()
{
	return sm_convert<sm_handle_t>(GetCurrentProcess());
}

sm_address_t sm::internal::module_address(const char* moduleName)
{
	return sm_convert<sm_address_t>(GetModuleHandleA(moduleName));
}

sm_address_t sm::internal::base_address()
{
	return sm::internal::module_address(0);
}

SM_PROTECT sm::internal::protect(sm_address_t address, sm_size_t size, SM_PROTECT protect)
{
	SM_PROTECT _protect;
	VirtualProtect((LPVOID)address, (SIZE_T)size, (DWORD)protect, (PDWORD)&_protect);
	return _protect;
}
