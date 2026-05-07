#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_tests"
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
test_file() {
    local description="$1"
    local command="$2"
    local file="$3"
    local expected="$4"
    echo -n "Testing: $description ... "
    rm -f "$file"
    echo "$command" | $SHELL_PATH > /dev/null 2>&1
    if [ -f "$file" ] && [ "$(cat "$file")" = "$expected" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC}"
        echo -e "  Expected: ${YELLOW}$expected${NC}"
        echo -e "  Got:      ${YELLOW}$(cat "$file" 2>/dev/null || echo 'FILE NOT FOUND')${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== REDIRECTIONS AND PIPES TESTS ===${NC}\n"
test_file "redirect output >" "echo hello > $TEST_DIR/test1.txt" "$TEST_DIR/test1.txt" "hello"
test_command "pipe echo to grep" "echo -e 'hello\\nworld' | grep hello" "hello"
test_command "pipe multiple" "echo 'test test' | grep test" "test test"
test_command "pipe with sort" "echo -e '3\\n1\\n2' | sort" "1
2
3"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
echo -e "Total:  $((TESTS_PASSED + TESTS_FAILED))"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
