#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
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
        echo -e "  Expected: ${YELLOW}$expected${NC}"
        echo -e "  Got:      ${YELLOW}$output${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== BASIC COMMANDS TESTS ===${NC}\n"
test_command "echo without arguments" "echo" ""
test_command "echo with text" "echo hello" "hello"
test_command "echo with multiple args" "echo hello world" "hello world"
test_command "pwd command" "pwd" "$(pwd)"
test_command "multiple commands" "echo test; echo ok" "test
ok"
test_command "echo with quotes" "echo 'hello world'" "hello world"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
