#---------------------------------------------------------------------------------------
# Check env variable for python
#---------------------------------------------------------------------------------------
if(DEFINED PYTHON3_PATH AND EXISTS ${PYTHON3_PATH})
    set(PYTHON3_PATH ${PYTHON3_PATH})
else()
    set(PYTHON3_PATH "/usr/bin")
endif()

#---------------------------------------------------------------------------------------
# Check env variable for project type
#---------------------------------------------------------------------------------------
if(DEFINED PROJECT_TYPE)
    set(PROJECT_TYPE ${PROJECT_TYPE})
else()
    set(PROJECT_TYPE "Sidekick_Factory")
endif()

#---------------------------------------------------------------------------------------
# Check env variable for output config
#---------------------------------------------------------------------------------------
if(DEFINED PROJECT_OUTPUT_PATH)
    set(BUILD_OUTPUT_DIR  ${PROJECT_OUTPUT_PATH})
else()
    set(BUILD_OUTPUT_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_TYPE}/build_outputs)
endif()
