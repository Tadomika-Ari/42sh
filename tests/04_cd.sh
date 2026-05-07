#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_cd_test"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
mkdir -p "$TEST_DIR/subdir"
test_command() {
    local description="$1"
    local command="$2"
    local expected="$3"
    echo -n "Testing: $description ... "
    output=$(echo "$command" | $SHELL_PATH 2>&1)
    if [ "$output" = "$expected" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== CD BUILTIN TESTS ===${NC}\n"
test_command "cd to directory" "cd $TEST_DIR; pwd" "$TEST_DIR"
test_command "cd to subdirectory" "cd $TEST_DIR; cd subdir; pwd" "$TEST_DIR/subdir"
test_command "cd to parent" "cd $TEST_DIR/subdir; cd ..; pwd" "$TEST_DIR"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
