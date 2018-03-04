/* file minunit_example.c */

#include <stdio.h>
#include <string.h>
#include "tests/minunit.h"
#include "board.h"
#include "key.h"
#include "layer.h"
#include "key_type.h"

/*

Syntax:
   static char * <test-name>() {
       mu_assert(<message>, <bool>);
       return 0;
   }

   static char * all_tests() {
       mu_run_test(<test-name>);
       return 0;
   }

*/


int tests_run = 0;

/* Tests keys. */
static char * test_key_is_static() {
    Key key = Key(3, 5, NULL);
    mu_assert(
        (char *) "isStatic true if there is no key value.",
        key.isStatic()
    );
    return 0;
}

static char * test_get_key_value() {
    Key key = Key(2, 1, (char*)"C");
    mu_assert(
        (char *) "We can get the key's value.",
        strcmp(key.getValue(), "C") == 0
    );
}

static char * test_key_can_point_to_layer() {
    Key key = Key(2, 1, NULL);
    const char *values[2][2] = {
        {"1", NULL},
        {"2", "3"},
    };
    Layer layer = Layer((char **) &values, 2, 2);
    key.setLayer(&layer);
    mu_assert(
        (char *) "We can get the layer assigned.",
        key.getLayer() == &layer
    );
    return 0;
}

static char * test_named_constructors_for_different_key_types() {
    const char *values[1][1] = {
        {"a"}
    };
    Layer *layer = new Layer((char **) &values, 1, 1);
    Key *key1 = Key::temporaryKey(layer, 0, 0);
    mu_assert(
        (char *) "Should have type TEMPORARY",
        key1->getType() == TEMPORARY
    );
    Key *key3 = Key::switchKey(layer, 0, 0);
    mu_assert(
        (char *) "Should have type SWITCH",
        key3->getType() == SWITCH
    );
    Key *key5 = new Key(0, 0, "M");
    mu_assert(
        (char *) "Should have type VALUE",
        key5->getType() == VALUE
    );
}

/* Tests layers. */
static char * test_layer_creates_keys() {
    const char *values[4][3] = {
        {"7", "8", "9"},
        {"4", "5", "6"},
        {"1", "2", "3"},
        {NULL, "0", NULL}
    };
    Layer layer = Layer((char **) &values, 4, 3);
    mu_assert(
        (char *) "",
        layer.getKey(0, 0)->getValue() == "7"
    );
    return 0;
}

static char * test_layer_dimensions() {
    const char *values[2][3] = {
        {"A", "B", "C"},
        {"D", NULL, "E"}
    };
    Layer layer = Layer((char **) &values, 2, 3);
    mu_assert(
        (char *) "We can see how many rows there are.",
        layer.getRowSize()
    );
    mu_assert(
        (char *) "We can see how many columns there are.",
        layer.getColumnSize()
    );
    return 0;
}

static char * test_set_layer_up_and_down_keys() {
    const char *l1Values[2][2] = {
        {"a", "b"},
        {NULL, "c"},
    };
    Layer layer1 = Layer((char **) &l1Values, 2, 2);
    const char *l2Values[2][2] = {
        {"a", "b"},
        {NULL, "c"},
    };
    Layer layer2 = Layer((char **) &l2Values, 2, 2);

    layer1.setLayerTemporarySwitch(&layer2, 1, 0);
    mu_assert(
        (char *) "Layer1 key at 1, 0 should hold layer 2.",
        layer1.getKey(1, 0)->getLayer() == &layer2
    );
    mu_assert(
        (char *) "Key is of type TEMPORARY",
        layer1.getKey(1, 0)->getType() == TEMPORARY
    );
    mu_assert(
        (char *) "Layer2 key at 1, 0 should hold layer 1.",
        layer2.getKey(1, 0)->getLayer() == &layer1
    );
    mu_assert(
        (char *) "Key should be of type TEMPORARY",
        layer2.getKey(1, 0)->getType() == TEMPORARY
    );
    return 0;
}

static char *test_temporary_layers_added_symmetrically_automatically() {
    const char *firstValues[1][2] = {
        {"1", NULL}
    };
    Layer *firstLayer = new Layer((char **) &firstValues, 1, 2);
    const char *secondValues[1][2] = {
        {"0", NULL}
    };
    Layer *secondLayer = new Layer((char **) &secondValues, 1, 2);
    firstLayer->setLayerTemporarySwitch(secondLayer, 1, 0);
    mu_assert(
        (char *) "The first key should have been assigned as normal.",
        firstLayer->getKey(0, 1)->getType() == TEMPORARY
    );
    mu_assert(
        (char *) "The second layer key should be assigned automatically.",
        secondLayer->getKey(0, 1)->getType() == TEMPORARY
    );
    mu_assert(
        (char *) "The second layer key should be pointing at the first.",
        secondLayer->getKey(0, 1)->getLayer() == firstLayer
    );
    return 0;
}

static char *test_can_chain_layer_setting() {
    const char *mainValues[2][2] = {
        { "1", NULL },
        { "0", NULL }
    };
    Layer *mainLayer = new Layer((char **) &mainValues, 2, 2);
    const char *secondValues[2][2] = {
        { "0", NULL },
        { "1", NULL }
    };
    Layer *secondLayer = new Layer((char **) &secondValues, 2, 2);
    const char *thirdValues[2][2] = {
        { "+", NULL },
        { ".", NULL }
    };
    Layer *thirdLayer = new Layer((char **) &thirdValues, 2, 2);
    mainLayer->setLayerTemporarySwitch(secondLayer, 0, 1)
             ->setLayerTemporarySwitch(thirdLayer, 1, 1);
    return 0;
}

/* Tests Boards */

static char * test_board_can_have_layer() {
    const char *values[1][2] = {
        {"A", "B"}
    };
    Layer layer = Layer((char **) &values, 1, 2);
    Board b = Board(&layer);
    b.runKeys();
    return 0;
}


/* Integration Test.
 * This is how it will likely be used.
 */
static char * test_create_board() {
    // Create leaves in the layer tree.
    const char *tempUpValues[2][2] = {
        {"A", "B"},
        {"C", NULL}
    };
    Layer *tempUpLayer = new Layer((char **) &tempUpValues, 2, 2);

    // Create the branches, setting links.
    const char *mainValues[2][2] = {
        {"a", "b"},
        {"c", NULL}
    };
    Layer *mainLayer = (new Layer((char **) &mainValues, 2, 2))
        ->setLayerTemporarySwitch(tempUpLayer, 1, 1);

    // Create a board to manage layers and execute keystrokes.
    Board board = Board(mainLayer);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_key_is_static);
    mu_run_test(test_layer_creates_keys);
    mu_run_test(test_layer_dimensions);
    mu_run_test(test_get_key_value);
    mu_run_test(test_key_can_point_to_layer);
    mu_run_test(test_named_constructors_for_different_key_types);
    mu_run_test(test_set_layer_up_and_down_keys);
    mu_run_test(test_board_can_have_layer);
    mu_run_test(test_create_board);
    mu_run_test(test_can_chain_layer_setting);
    mu_run_test(test_temporary_layers_added_symmetrically_automatically);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
