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
    echo -n "Testing: $description ... "
    output=$(echo "$command" | $SHELL_PATH 2>&1)
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== ERROR HANDLING TESTS ===${NC}\n"
test_command "non-existent command" "nonexistentcommand123"
test_command "command not found" "/nonexistent/path/command"
test_command "unclosed quotes" "echo 'hello"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
exit $TESTS_FAILED
