#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_builtins_test"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
mkdir -p "$TEST_DIR"
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
echo -e "${YELLOW}=== BUILTINS TESTS ===${NC}\n"
test_command "echo -n (no newline)" "echo -n hello" "hello"
test_command "echo -e with newline" "echo -e 'hello\\nworld'" "hello
world"
test_command "pwd command" "pwd" "$(pwd)"
test_command "cd and pwd" "cd $TEST_DIR && pwd" "$TEST_DIR"
test_command "cd to home" "cd ~ && pwd" "$HOME"
test_command "exit 0" "exit 0" ""
test_command "unset variable" "VAR=test; unset VAR; echo \$VAR" ""
test_command "export variable" "export TESTVAR=value; echo \$TESTVAR" "value"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
