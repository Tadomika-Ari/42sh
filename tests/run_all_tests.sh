#!/bin/bash
echo -e "\n╔════════════════════════════════════════╗"
echo -e "║   42SH EPITECH TEST SUITE              ║"
echo -e "║   env, setenv, unsetenv, cd, exit     ║"
echo -e "╚════════════════════════════════════════╝\n"
TESTS_DIR="./tests"
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'
if [ ! -f "./42sh" ]; then
    echo -e "${RED}Error: ./42sh binary not found${NC}"
    exit 1
fi
test_files=(
    "01_basic_commands.sh"
    "02_setenv.sh"
    "03_unsetenv.sh"
    "04_cd.sh"
    "05_exit.sh"
    "06_pipes_redirections.sh"
    "07_wildcards.sh"
    "08_operators.sh"
)
for test_file in "${test_files[@]}"; do
    if [ -f "$TESTS_DIR/$test_file" ]; then
        echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
        echo -e "${YELLOW}Running: $test_file${NC}\n"
        bash "$TESTS_DIR/$test_file"
        echo ""
    fi
done
echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}All tests completed!${NC}\n"
