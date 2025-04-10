file(GLOB_RECURSE SANDBOX_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Create filters for App, Widget, etc.
foreach(FILE IN LISTS SANDBOX_SRC)
    get_filename_component(PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${PATH}")
    string(REPLACE "/" "\\" FILTER "${REL_PATH}")
    source_group("${FILTER}" FILES "${FILE}")
endforeach()

add_executable(Sandbox ${SANDBOX_SRC})

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/App
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Widget
)

target_link_libraries(Sandbox PRIVATE glfw)
target_link_libraries(Sandbox PRIVATE GraphicsEngine)
target_link_libraries(Sandbox PRIVATE glm::glm)
target_link_libraries(Sandbox PRIVATE imgui::imgui)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	target_link_options(Sandbox PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()

# In Windows, copy the dlls into the target directory as a post-build event.
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	
	# Copy the GraphicsEngine dll to the Sandbox output directory.
	add_custom_command(TARGET Sandbox POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:GraphicsEngine> 	# Path to the DLL
			$<TARGET_FILE_DIR:Sandbox>   	# Path to the executable directory
	)
	
	# Copy the dependency dlls as well.
	file(GLOB DLL_FILES "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin/*.dll")
	message("Dll file: ${DLL_FILES}")
	foreach(DLL ${DLL_FILES})
		add_custom_command(TARGET Sandbox POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${DLL} $<TARGET_FILE_DIR:Sandbox>
		)
	endforeach()
	
endif()