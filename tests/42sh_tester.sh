#!/bin/bash

mkdir -p tests

cat > tests/01_basic_commands.sh << 'EOF'
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
echo -e "${YELLOW}=== BASIC COMMANDS TESTS ===${NC}\n"
test_command "echo without arguments" "echo" ""
test_command "echo with text" "echo hello" "hello"
test_command "echo with multiple args" "echo hello world" "hello world"
test_command "pwd command" "pwd" "$(pwd)"
test_command "multiple commands" "echo test; echo ok" "test
ok"
test_command "echo with quotes" "echo 'hello world'" "hello world"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
EOF

cat > tests/02_setenv.sh << 'EOF'
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
echo -e "${YELLOW}=== SETENV/ENV TESTS ===${NC}\n"
test_command "env shows variables" "setenv TEST_VAR hello; env | grep TEST_VAR" "TEST_VAR=hello"
test_command "setenv multiple" "setenv VAR1 value1; setenv VAR2 value2; env | grep VAR1" "VAR1=value1"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
EOF

cat > tests/03_unsetenv.sh << 'EOF'
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
EOF

cat > tests/04_cd.sh << 'EOF'
#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_cd_test"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
mkdir -p "$TEST_DIR/subdir"
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
echo -e "${YELLOW}=== CD BUILTIN TESTS ===${NC}\n"
test_command "cd to directory" "cd $TEST_DIR; pwd" "$TEST_DIR"
test_command "cd to subdirectory" "cd $TEST_DIR; cd subdir; pwd" "$TEST_DIR/subdir"
test_command "cd to parent" "cd $TEST_DIR/subdir; cd ..; pwd" "$TEST_DIR"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
EOF

cat > tests/05_exit.sh << 'EOF'
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
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
EOF

cat > tests/06_pipes_redirections.sh << 'EOF'
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
EOF

cat > tests/07_wildcards.sh << 'EOF'
#!/bin/bash
SHELL_PATH="./42sh"
TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="/tmp/42sh_wildcard_test"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
mkdir -p "$TEST_DIR"
touch "$TEST_DIR/file1.txt" "$TEST_DIR/file2.txt" "$TEST_DIR/file3.sh"
test_command() {
    local description="$1"
    local command="$2"
    local expected_pattern="$3"
    echo -n "Testing: $description ... "
    output=$(echo "$command" | $SHELL_PATH 2>&1)
    if echo "$output" | grep -q "$expected_pattern"; then
        echo -e "${GREEN}✓ PASSED${NC}"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗ FAILED${NC}"
        ((TESTS_FAILED++))
    fi
}
echo -e "${YELLOW}=== WILDCARDS TESTS ===${NC}\n"
test_command "* wildcard" "ls $TEST_DIR/*" "file1.txt"
test_command "*.txt wildcard" "ls $TEST_DIR/*.txt" "file1.txt"
test_command "? wildcard" "ls $TEST_DIR/file?.txt" "file1.txt"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
rm -rf "$TEST_DIR"
exit $TESTS_FAILED
EOF

cat > tests/08_operators.sh << 'EOF'
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
echo -e "${YELLOW}=== OPERATORS TESTS ===${NC}\n"
test_command "logical AND true" "echo test && echo ok" "test
ok"
test_command "logical AND false" "false && echo no" ""
test_command "logical OR true" "echo yes || echo no" "yes"
test_command "logical OR false" "false || echo yes" "yes"
echo -e "\n${YELLOW}=== SUMMARY ===${NC}"
echo -e "Passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed: ${RED}$TESTS_FAILED${NC}"
exit $TESTS_FAILED
EOF

cat > tests/run_all_tests.sh << 'EOF'
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
EOF

chmod +x tests/*.sh

echo "✓ Setup Epitech 42sh!"
echo "Run: bash tests/run_all_tests.sh"