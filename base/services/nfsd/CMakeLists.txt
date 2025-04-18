remove_definitions(-D_WIN32_WINNT=0x502 -DWINVER=0x502)
add_definitions(-D_WIN32_WINNT=0x601)
add_definitions(-DNTDDI_VERSION=0x06010000)

include_directories(
    ${REACTOS_SOURCE_DIR}/dll/3rdparty/libtirpc/tirpc
    ${REACTOS_SOURCE_DIR}/drivers/filesystems/nfs
    ${REACTOS_SOURCE_DIR}/dll/np/nfs)

list(APPEND SOURCE
    acl.c
    callback_server.c
    callback_xdr.c
    daemon_debug.c
    delegation.c
    ea.c
    getattr.c
    idmap.c
    lock.c
    lookup.c
    mount.c
    name_cache.c
    namespace.c
    nfs41_client.c
    nfs41_compound.c
    nfs41_daemon.c
    nfs41_ops.c
    nfs41_rpc.c
    nfs41_server.c
    nfs41_session.c
    nfs41_superblock.c
    nfs41_xdr.c
    open.c
    pnfs_debug.c
    pnfs_device.c
    pnfs_io.c
    pnfs_layout.c
    readdir.c
    readwrite.c
    recovery.c
    service.c
    setattr.c
    symlink.c
    upcall.c
    util.c
    volume.c
    precomp.h)

add_executable(nfsd ${SOURCE} nfsd.rc)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # Disable warning C4477 (printf format warnings)
    target_compile_options(nfsd PRIVATE /wd4477)
else()
    # FIXME: Tons of warnings.
    target_compile_options(nfsd PRIVATE "-w")
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(nfsd PRIVATE -Wno-incompatible-function-pointer-types)
endif()

target_link_libraries(nfsd oldnames)

set_module_type(nfsd win32cui)
add_importlibs(nfsd advapi32 iphlpapi kernel32_vista libtirpc msvcrt shell32 ws2_32 wldap32 kernel32 ntdll)
add_pch(nfsd precomp.h SOURCE)

add_cd_file(TARGET nfsd DESTINATION reactos/system32 FOR all)
add_cd_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/netconfig" DESTINATION reactos/system32/drivers/etc FOR all)
add_cd_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/ms-nfs41-idmap.conf" DESTINATION reactos/system32/drivers/etc FOR all)
add_registry_inf(nfsd_reg.inf)
