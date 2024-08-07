set(UTIL_FILE_NAME ob_log_miner_test_utils.cpp)

function(logminer_unittest case)
  if(ARGC EQUAL 1)
    add_executable(${case} ${case}.cpp ${UTIL_FILE_NAME})
  else()
    add_executable(${ARGV} ${UTIL_FILE_NAME})
  endif()
  if (case MATCHES "^test_.*")
    add_test(${case} ${case})
    set_tests_properties(${case} PROPERTIES TIMEOUT 300)
  endif()
  target_link_libraries(${case} PRIVATE oblogminer_obj_dev gtest gmock)
  target_include_directories(${case}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/unittest ${CMAKE_SOURCE_DIR}/deps/oblib/unittest)
endfunction()

logminer_unittest(test_ob_log_miner_args)
logminer_unittest(test_ob_log_miner_br_filter)
logminer_unittest(test_ob_log_miner_record)
logminer_unittest(test_ob_log_miner_record_converter)
logminer_unittest(test_ob_log_miner_utils)
logminer_unittest(test_ob_log_miner_analyzer_checkpoint)
logminer_unittest(test_ob_log_miner_progress_range)
logminer_unittest(test_ob_log_miner_file_meta)
logminer_unittest(test_ob_log_miner_file_index)
logminer_unittest(test_ob_log_miner_file_manager)