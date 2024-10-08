cmake_minimum_required(VERSION 3.9)

# UI Tests

## Checkbox
add_executable(checkbox.ui.test EXCLUDE_FROM_ALL checkbox.ui.test.cpp)
target_link_libraries(checkbox.ui.test PRIVATE CaTerm)
target_compile_options(checkbox.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Spinners
add_executable(spinners.ui.test EXCLUDE_FROM_ALL spinners.ui.test.cpp)
target_link_libraries(spinners.ui.test PRIVATE CaTerm)
target_compile_options(spinners.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Passive Layout Wrapper
add_executable(passive.ui.test EXCLUDE_FROM_ALL passive.ui.test.cpp)
target_link_libraries(passive.ui.test PRIVATE CaTerm)
target_compile_options(passive.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Fixed Wrapper
add_executable(fixed.ui.test EXCLUDE_FROM_ALL fixed.ui.test.cpp)
target_link_libraries(fixed.ui.test PRIVATE CaTerm)
target_compile_options(fixed.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Layout Sorting
add_executable(layout_sort.ui.test EXCLUDE_FROM_ALL layout_sort.ui.test.cpp)
target_link_libraries(layout_sort.ui.test PRIVATE CaTerm)
target_compile_options(layout_sort.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Line Edit Widget
add_executable(line_edit.ui.test EXCLUDE_FROM_ALL line_edit.ui.test.cpp)
target_link_libraries(line_edit.ui.test PRIVATE CaTerm)
target_compile_options(line_edit.ui.test PRIVATE -Wall -Wextra -Wpedantic)

## Slider
add_executable(slider.ui.test EXCLUDE_FROM_ALL slider.ui.test.cpp)
target_link_libraries(slider.ui.test PRIVATE CaTerm)
target_compile_options(slider.ui.test PRIVATE -Wall -Wextra -Wpedantic)

add_custom_target(
    caterm.ui.tests
    DEPENDS
        checkbox.ui.test
        spinners.ui.test
        passive.ui.test
        fixed.ui.test
        layout_sort.ui.test
        slider.ui.test
        line_edit.ui.test
)

# Unit Tests
add_executable(caterm.unit.tests EXCLUDE_FROM_ALL
    catch2.main.cpp
    glyph_string.unit.test.cpp
    canvas.unit.test.cpp
    unique_queue.unit.test.cpp
)
target_compile_options(caterm.unit.tests PRIVATE -Wall -Wextra -Wpedantic)

# Catch2::Catch2 relies on signals-light to define it.
target_link_libraries(caterm.unit.tests PRIVATE CaTerm Catch2::Catch2)
