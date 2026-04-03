#include <criterion/criterion.h>

Test(hello_word, expected_message)
{
    const char *message = "Hello word";

    cr_assert_str_eq(message, "Hello word");
}
