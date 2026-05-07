#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
echo -e "${YELLOW}=== UNSETENV TESTS ===${NC}\n"
echo -n "Testing: unsetenv removes var ... "
output=$(echo "setenv TEST_UNSET value; unsetenv TEST_UNSET; env | grep TEST_UNSET" | $SHELL_PATH 2>&1)
if [ -z "$output" ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    ((TESTS_PASSED++))
else
    echo -e "${RED}✗ FAILED${NC}"
    ((TESTS_FAILED++))
fi
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
