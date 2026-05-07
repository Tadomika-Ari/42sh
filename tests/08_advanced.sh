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
echo -e "${YELLOW}=== ADVANCED FEATURES TESTS ===${NC}\n"
test_command "if true" "if true; then echo yes; fi" "yes"
test_command "if false" "if false; then echo yes; fi" ""
test_command "if-else true" "if true; then echo yes; else echo no; fi" "yes"
test_command "for loop basic" "for i in 1 2 3; do echo \$i; done" "1
2
3"
test_command "while loop" "i=0; while [ \$i -lt 3 ]; do echo \$i; i=\$((i+1)); done" "0
1
2"
test_command "function definition" "myfunc() { echo hello; }; myfunc" "hello"
test_command "function with params" "greet() { echo hello \$1; }; greet world" "hello world"
test_command "case statement" "case 2 in 1) echo one ;; 2) echo two ;; esac" "two"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
exit $TESTS_FAILED
