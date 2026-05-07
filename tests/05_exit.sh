#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
echo -e "${YELLOW}=== EXIT BUILTIN TESTS ===${NC}\n"
echo -n "Testing: exit 0 returns 0 ... "
echo "exit 0" | $SHELL_PATH > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "${GREEN}✓ PASSED${NC}"
    ((TESTS_PASSED++))
else
    echo -e "${RED}✗ FAILED${NC}"
    ((TESTS_FAILED++))
fi
echo -n "Testing: exit 42 returns 42 ... "
echo "exit 42" | $SHELL_PATH > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 42 ]; then
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
