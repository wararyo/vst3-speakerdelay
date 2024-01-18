cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

project(SpeakerDelay
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "SpeakerDelay VST 3 Plug-in"
)

set(vst3sdk_SOURCE_DIR ${PROJECT_SOURCE_DIR}/vst3sdk)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(SpeakerDelay
    source/version.h
    source/cids.h
    source/processor.h
    source/processor.cpp
    source/controller.h
    source/controller.cpp
    source/entry.cpp
    source/ringbuffer.h
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(SpeakerDelay
        PRIVATE
            resource/editor.uidesc
    )
    target_link_libraries(SpeakerDelay
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(SpeakerDelay
        RESOURCES
            "resource/editor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (SpeakerDelay
    RESOURCES
        resource/97491C1715D25CD88BD653FB26EDE4BA_snapshot.png
        resource/97491C1715D25CD88BD653FB26EDE4BA_snapshot_2.0x.png
)

target_link_libraries(SpeakerDelay
    PRIVATE
        sdk
)

smtg_target_configure_version_file(SpeakerDelay)

if(SMTG_MAC)
    smtg_target_set_bundle(SpeakerDelay
        BUNDLE_IDENTIFIER com.covelline.SpeakerDelay
        COMPANY_NAME ""
    )
    smtg_target_set_debug_executable(SpeakerDelay
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(SpeakerDelay PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SpeakerDelay)

        smtg_target_set_debug_executable(SpeakerDelay
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
