#include <skypat/skypat.h>

#define _Bool bool
extern "C" {
#include <string.h>
#include <stdlib.h>
#include <core/Runtime.h>
#include <core/Stack.h>
#include <dataTypes/vector_p.h>
#include <dataTypes/Value.h>
#include <dataTypes/Label.h>
#include <instance/ControlInstrInst.h>
}
#undef _Bool

SKYPAT_F(Runtime_control_br, br_if_true)
{
    Stack stack = new_Stack();
    char* moduleName = (char*) malloc(sizeof(char) * 5);
    strcpy(moduleName, "Test");
    Label label = new_Label(0, 1, 2);
    vector_p resultTypes = new_vector_p(ValueType, NULL);
    ValueType resultType = Value_i32;
    vector_push_back(resultTypes, &resultType);
    vector_push_back(resultTypes, &resultType);
    label_set_resultTypes(label, resultTypes);
    push_Label(stack, label);
    push_Label(stack, new_Label(0, 3, 4));
    ControlInstrInst* control = new_ControlInstrInst();
    uint32_t* address = (uint32_t*) malloc(sizeof(uint32_t));
    *address = 1;
    vector_push_back(control->indices, address);

    // Check
    push_Value(stack, new_i32Value(1));
    push_Value(stack, new_i32Value(2));
    push_Value(stack, new_i32Value(3));
    push_Value(stack, new_i32Value(1));
    EXPECT_EQ(runtime_br_if(stack, control), 0);
    Value* result = NULL;
    EXPECT_EQ(pop_Value(stack, &result), 0);
    EXPECT_EQ(result->type, Value_i32);
    EXPECT_EQ(result->value.i32, 2);
    free(result);
    EXPECT_EQ(pop_Value(stack, &result), 0);
    EXPECT_EQ(result->type, Value_i32);
    EXPECT_EQ(result->value.i32, 1);
    free(result);

    // clean
    free_Stack(stack);
    free_ControlInstrInst(control);
}

SKYPAT_F(Runtime_control_br, br_if_false)
{
    Stack stack = new_Stack();
    char* moduleName = (char*) malloc(sizeof(char) * 5);
    strcpy(moduleName, "Test");
    Label label = new_Label(0, 1, 2);
    vector_p resultTypes = new_vector_p(ValueType, NULL);
    ValueType resultType = Value_i32;
    vector_push_back(resultTypes, &resultType);
    vector_push_back(resultTypes, &resultType);
    label_set_resultTypes(label, resultTypes);
    push_Label(stack, label);
    push_Label(stack, new_Label(0, 3, 5));
    ControlInstrInst* control = new_ControlInstrInst();
    uint32_t* address = (uint32_t*) malloc(sizeof(uint32_t));
    *address = 1;
    vector_push_back(control->indices, address);

    // Check
    push_Value(stack, new_i32Value(1));
    push_Value(stack, new_i32Value(2));
    push_Value(stack, new_i32Value(3));
    push_Value(stack, new_i32Value(0));
    EXPECT_EQ(runtime_br_if(stack, control), 0);
    Value* result = NULL;
    EXPECT_EQ(pop_Value(stack, &result), 0);
    EXPECT_EQ(result->type, Value_i32);
    EXPECT_EQ(result->value.i32, 3);
    free(result);
    EXPECT_EQ(label_get_instrIndex(stack_cur_label(stack)), 4);

    // clean
    free_Stack(stack);
    free_ControlInstrInst(control);
}
