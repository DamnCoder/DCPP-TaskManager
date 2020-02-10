set(SOURCES
    test_lambda_tasks.cpp
    )

add_executable(test_lambda_tasks ${SOURCES})
target_link_libraries(test_lambda_tasks PUBLIC dcpp_mttaskmanager CONAN_PKG::gtest)

add_test(NAME TestLambdaTasks COMMAND $<TARGET_FILE:test_lambda_tasks>)
set_target_properties(test_lambda_tasks PROPERTIES FOLDER "TestLambdaTasks")
