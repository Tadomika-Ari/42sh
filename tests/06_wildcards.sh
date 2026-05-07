#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_glob_test"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
mkdir -p "$TEST_DIR"
touch "$TEST_DIR/file1.txt"
touch "$TEST_DIR/file2.txt"
touch "$TEST_DIR/file3.sh"
test_command() {
    local description="$1"
    local command="$2"
    local expected_pattern="$3"
    echo -n "Testing: $description ... "
    output=$(echo "$command" | $SHELL_PATH 2>&1)
    if echo "$output" | grep -q "$expected_pattern"; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== WILDCARDS TESTS ===${NC}\n"
test_command "* wildcard" "ls $TEST_DIR/*" "file1.txt"
test_command "*.txt wildcard" "ls $TEST_DIR/*.txt" "file1.txt"
test_command "? wildcard" "ls $TEST_DIR/file?.txt" "file1.txt"
test_command "[12] character class" "ls $TEST_DIR/file[12].txt" "file1.txt"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
