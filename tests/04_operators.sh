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
echo -e "${YELLOW}=== OPERATORS TESTS ===${NC}\n"
test_command "logical AND true" "echo test && echo ok" "test
ok"
test_command "logical AND false" "false && echo should_not_print" ""
test_command "logical OR first true" "echo test || echo not_called" "test"
test_command "logical OR second executes" "false || echo executed" "executed"
test_command "command substitution" "echo \$(echo hello)" "hello"
test_command "arithmetic 1+1" "echo \$((1 + 1))" "2"
test_command "arithmetic 5*3" "echo \$((5 * 3))" "15"
test_command "single quotes" "VAR=test; echo '\$VAR'" "\$VAR"
test_command "double quotes expand" "VAR=test; echo \"\$VAR\"" "test"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
exit $TESTS_FAILED
