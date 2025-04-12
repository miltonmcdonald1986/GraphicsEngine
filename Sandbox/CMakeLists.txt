################################################################################
# Specify the locations of all source files for this project                   #
################################################################################

#file(GLOB_RECURSE SANDBOX_SRC
#    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
#    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
#)

################################################################################
# Create filters for each directory                                            #
################################################################################

#foreach(FILE IN LISTS SANDBOX_SRC)
#    get_filename_component(PATH "${FILE}" PATH)
#    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${PATH}")
#    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
#    source_group("${FILTER}" FILES "${FILE}")
#endforeach()

################################################################################
# Create the executable that we will run                                       #
################################################################################

#add_executable(Sandbox ${SANDBOX_SRC})

################################################################################
# Additional include directories                                               #
################################################################################

#target_include_directories(Sandbox PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/src
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/App
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/Widget
#)

################################################################################
# Libraries                                                                    #
################################################################################

#target_link_libraries(Sandbox PRIVATE glfw)
#target_link_libraries(Sandbox PRIVATE GraphicsEngine)
#target_link_libraries(Sandbox PRIVATE glm::glm)
#target_link_libraries(Sandbox PRIVATE imgui::imgui)

################################################################################
# Define subsystem and entry point for Windows                                 #
################################################################################

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#	target_link_options(Sandbox PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
#endif()

################################################################################
# Use shared output directory for this project                                 #
################################################################################

#set_target_properties(Sandbox PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
#    LIBRARY_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
#    ARCHIVE_OUTPUT_DIRECTORY ${SHARED_OUTPUT_DIR}
#)

################################################################################
# In Windows, copy the dlls into the target dir as a post build event          #
################################################################################

#if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#	
#	set(DLL_DIR_DEBUG "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/bin")
#	set(DLL_DIR_RELEASE "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin")
#
#	# Because of Visual Studio multigenerator setup, we have to copy these one at a time (can't wrap them in a for loop using file glob).
#
#	set(FMT_DLL_PATH "$<IF:$<CONFIG:Debug>,${DLL_DIR_DEBUG}/fmtd.dll,${DLL_DIR_RELEASE}/fmt.dll>")
#	add_custom_command(TARGET Sandbox POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FMT_DLL_PATH} $<TARGET_FILE_DIR:Sandbox>)	
#	
#	set(GLFW_DLL_PATH "$<IF:$<CONFIG:Debug>,${DLL_DIR_DEBUG}/glfw3.dll,${DLL_DIR_RELEASE}/glfw3.dll>")
#	add_custom_command(TARGET Sandbox POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLFW_DLL_PATH} $<TARGET_FILE_DIR:Sandbox>)	
#	
#	set(SPDLOG_DLL_PATH "$<IF:$<CONFIG:Debug>,${DLL_DIR_DEBUG}/spdlogd.dll,${DLL_DIR_RELEASE}/spdlog.dll>")
#	add_custom_command(TARGET Sandbox POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPDLOG_DLL_PATH} $<TARGET_FILE_DIR:Sandbox>)
#
#endif()

################################################################################
# Set the debugger's working directory to the out dir                          #
################################################################################

#set(VS_SHARED_OUTPUT_DIR "${SHARED_OUTPUT_DIR}/$<CONFIG>")
#if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
#
#	set_target_properties(Sandbox PROPERTIES
#		VS_DEBUGGER_WORKING_DIRECTORY "${VS_SHARED_OUTPUT_DIR}"
#	)
#	
#endif()
