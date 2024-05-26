/*
* MenuTest.c
* Unit tests for the pause menu.
*/
#include "MenuTest.h"

/* Test Initialization of Pause Menu */
void test_MenuPauseInit(void) {
    Menu* menu = MenuPauseInit();
    
    CU_ASSERT_PTR_NOT_NULL(menu);
    CU_ASSERT_STRING_EQUAL(menu->title, "Menu");
    CU_ASSERT_EQUAL(menu->numOptions, 6);
    CU_ASSERT_EQUAL(menu->selectedOption, 0);
    
    const char* expectedOptions[6] = {"Resume", "Restart", "Save", "Load", "Settings", "Quit"};
    for (int i = 0; i < 6; i++) {
        CU_ASSERT_STRING_EQUAL(menu->options[i], expectedOptions[i]);
    }
    
    free(menu->options);
    free(menu);
}

/* Test Resetting of Pause Menu */
void test_MenuPauseReset(void) {
    Menu* menu = MenuPauseInit();
    menu->selectedOption = 3;
    MenuPauseReset(menu);
    CU_ASSERT_EQUAL(menu->selectedOption, 0);
    
    free(menu->options);
    free(menu);
}

/* Test Moving Up in Pause Menu */
void test_MenuPauseUp(void) {
    Menu* menu = MenuPauseInit();
    
    menu->selectedOption = 0;
    MenuPauseUp(menu);
    CU_ASSERT_EQUAL(menu->selectedOption, 5);

    menu->selectedOption = 3;
    MenuPauseUp(menu);
    CU_ASSERT_EQUAL(menu->selectedOption, 2);
    
    free(menu->options);
    free(menu);
}

/* Test Moving Down in Pause Menu */
void test_MenuPauseDown(void) {
    Menu* menu = MenuPauseInit();
    
    menu->selectedOption = 5;
    MenuPauseDown(menu);
    CU_ASSERT_EQUAL(menu->selectedOption, 0);

    menu->selectedOption = 2;
    MenuPauseDown(menu);
    CU_ASSERT_EQUAL(menu->selectedOption, 3);
    
    free(menu->options);
    free(menu);
}
