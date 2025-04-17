# Find Qt6 Test module
find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

# Add a test executable
add_executable(AppStartTest
    appstarttest.cpp
)

# Link against Qt6 libraries
target_link_libraries(AppStartTest PRIVATE Qt6::Test Qt6::Widgets)

# Add the test to CTest
add_test(NAME AppStartTest COMMAND AppStartTest)