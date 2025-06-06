
add_definitions(
    -DENTRY_PREFIX=STI_
    -DPROXY_DELEGATION
    -DWINE_REGISTER_DLL)

spec2def(sti.dll sti.spec)
add_rpcproxy_files(sti_wia.idl)

list(APPEND SOURCE
    sti.c
    sti_main.c)

list(APPEND PCH_SKIP_SOURCE
    guid.c)

add_library(sti MODULE
    ${SOURCE}
    ${PCH_SKIP_SOURCE}
    sti.rc
    ${CMAKE_CURRENT_BINARY_DIR}/proxy.dlldata.c
    ${CMAKE_CURRENT_BINARY_DIR}/sti_wia_p.c
    ${CMAKE_CURRENT_BINARY_DIR}/sti.def)

set_module_type(sti win32dll)
target_link_libraries(sti wine uuid ${PSEH_LIB})
add_importlibs(sti ole32 oleaut32 rpcrt4 advapi32 msvcrt kernel32 ntdll)
add_pch(sti precomp.h "${PCH_SKIP_SOURCE}")
add_cd_file(TARGET sti DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(sti) # CORE-5743: No ARRAY_SIZE and CONST_VTABLE
