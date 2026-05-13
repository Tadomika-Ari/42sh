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
echo -e "${YELLOW}=== VARIABLES TESTS ===${NC}\n"
test_command "set variable" "VAR=hello; echo \$VAR" "hello"
test_command "variable with spaces" "VAR='hello world'; echo \$VAR" "hello world"
test_command "variable concatenation" "A=hello; B=world; echo \$A\$B" "helloworld"
test_command "variable with numbers" "NUM=42; echo \$NUM" "42"
test_command "unset variable" "echo \$UNDEFINED_VAR" ""
test_command "variable with underscore" "MY_VAR=test; echo \$MY_VAR" "test"
test_command "overwrite variable" "VAR=old; VAR=new; echo \$VAR" "new"
test_command "variable in command" "PATH_TEST=/tmp; echo \$PATH_TEST" "/tmp"
test_command "multiple variables" "A=1; B=2; C=3; echo \$A \$B \$C" "1 2 3"
test_command "variable in quotes" "MSG=hello; echo \"\$MSG\"" "hello"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
exit $TESTS_FAILED
