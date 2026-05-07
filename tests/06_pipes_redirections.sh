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
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== PIPES AND REDIRECTIONS TESTS ===${NC}\n"
test_command "pipe to grep" "echo -e 'hello\\nworld' | grep hello" "hello"
test_command "pipe to sort" "echo -e '3\\n1\\n2' | sort" "1
2
3"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
