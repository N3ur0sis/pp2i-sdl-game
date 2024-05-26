/*
* MainTest.c
*/
#include "MenuTest.h"

void test_MenuPauseInit(void);
void test_MenuPauseReset(void);
void test_MenuPauseUp(void);
void test_MenuPauseDown(void);

/* Main function to run the tests */
int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("Pause Menu Test Suite", 0, 0);
    
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of MenuPauseInit", test_MenuPauseInit)) ||
        (NULL == CU_add_test(pSuite, "test of MenuPauseReset", test_MenuPauseReset)) ||
        (NULL == CU_add_test(pSuite, "test of MenuPauseUp", test_MenuPauseUp)) ||
        (NULL == CU_add_test(pSuite, "test of MenuPauseDown", test_MenuPauseDown))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}