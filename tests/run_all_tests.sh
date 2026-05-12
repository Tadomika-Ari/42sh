#!/bin/bash

echo -e "\n╔════════════════════════════════════════╗"
echo -e   "║   42SH TESTS                           ║"
echo -e   "║   by:                                  ║"
echo -e   "║      - Alcibiade S.                    ║"
echo -e   "║      - Galya P.                        ║"
echo -e   "║      - Lucas E.                        ║"
echo -e   "║      - Ugo P.                          ║"
echo -e   "║      - Alessandro P.                   ║"
echo -e   "╚════════════════════════════════════════╝\n"

TESTS_DIR="./tests"
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
GREEN='\033[0;32m'
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

total_passed=0
total_failed=0

for test_file in "${test_files[@]}"; do
    if [ -f "$TESTS_DIR/$test_file" ]; then
        echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
        echo -e "${YELLOW}Running: $test_file${NC}\n"

        output=$(bash "$TESTS_DIR/$test_file")
        echo "$output"

        clean_output=$(echo "$output" | sed -r 's/\x1B\[[0-9;]*[A-Za-z]//g')
        passed=$(echo "$clean_output" | awk -F': ' '/^Passed:/ {print $2}' | tail -n 1)
        failed=$(echo "$clean_output" | awk -F': ' '/^Failed:/ {print $2}' | tail -n 1)

        passed=${passed:-0}
        failed=${failed:-0}

        total_passed=$((total_passed + passed))
        total_failed=$((total_failed + failed))

        echo ""
    fi
done

total_tests=$((total_passed + total_failed))

echo -e "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}All tests completed!${NC}"
echo -e "${GREEN}Total passed: $total_passed${NC}"
echo -e "${RED}Total failed: $total_failed${NC}"
echo -e "${YELLOW}Total tests: $total_tests${NC}"
