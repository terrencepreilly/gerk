/* file minunit_example.c */

#include <stdio.h>
#include <string>
#include <vector>

#include "tests/minunit.h"
#include "board.h"
#include "key.h"
#include "layer.h"
#include "key_type.h"
#include "tests/test_button.h"
using namespace std;

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
    Key key = Key("");
    mu_assert(
        (char *) "isStatic true if there is no key value.",
        key.isStatic()
    );
    return 0;
}

static char * test_get_key_value() {
    Key key = Key("C");
    mu_assert(
        (char *) "We can get the key's value.",
        key.getValue().compare("C") == 0
    );
    return 0;
}

static char * test_key_can_point_to_layer() {
    Key key = Key("");
    vector<vector<string>> values;
    vector<string> row1;
    row1.push_back("1");
    row1.push_back("");
    vector<string> row2;
    row2.push_back("2");
    row2.push_back("3");
    values.push_back(row1);
    values.push_back(row2);
    Layer layer = Layer(values);
    key.setLayer(&layer);
    mu_assert(
        (char *) "We can get the layer assigned.",
        key.getLayer() == &layer
    );
    return 0;
}

static char * test_named_constructors_for_different_key_types() {
    vector<vector<string>> values;
    vector<string> row(1, "a");
    values.push_back(row);
    Layer *layer = new Layer(values);
    Key *key1 = Key::temporaryKey(layer);
    mu_assert(
        (char *) "Should have type TEMPORARY",
        key1->getType() == TEMPORARY
    );
    Key *key3 = Key::switchKey(layer);
    mu_assert(
        (char *) "Should have type SWITCH",
        key3->getType() == SWITCH
    );
    Key *key5 = new Key("M");
    mu_assert(
        (char *) "Should have type VALUE",
        key5->getType() == VALUE
    );
    return 0;
}

/* Tests layers. */
static char * test_layer_creates_keys() {
    vector<string> row1;
    row1.push_back("7");
    row1.push_back("8");
    row1.push_back("9");
    vector<vector<string>> values(1, row1);
    Layer layer = Layer(values);
    mu_assert(
        (char *) "The value of the first key should be 7.",
        layer.getKey(0, 0)->getValue() == "7"
    );
    return 0;
}

static char * test_layer_dimensions() {
    vector<string> row1(3, "");
    vector<vector<string>> values(2, row1);
    Layer layer = Layer(values);
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
    vector<string> blankRow(2, "");
    vector<vector<string>> l1Values(2, blankRow);
    Layer layer1 = Layer(l1Values);

    vector<vector<string>> l2Values(2, blankRow);
    Layer layer2 = Layer(l2Values);

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
    vector<string> row1;
    row1.push_back("1");
    row1.push_back("2");
    vector<vector<string>> firstValues(1, row1);
    Layer *firstLayer = new Layer(firstValues);

    vector<string> row2;
    row2.push_back("0");
    row2.push_back("");
    vector<vector<string>> secondValues(1, row2);
    Layer *secondLayer = new Layer(secondValues);
    firstLayer->setLayerTemporarySwitch(secondLayer, 0, 1);
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
    vector<string> blankRow(2, "");
    vector<vector<string>> mainValues(2, blankRow);
    Layer *mainLayer = new Layer(mainValues);

    vector<vector<string>> secondValues(2, blankRow);
    Layer *secondLayer = new Layer(secondValues);

    vector<vector<string>> thirdValues(2, blankRow);
    Layer *thirdLayer = new Layer(thirdValues);
    mainLayer->setLayerTemporarySwitch(secondLayer, 0, 1)
             ->setLayerTemporarySwitch(thirdLayer, 1, 1);
    return 0;
}

/* Tests Boards */

static char * test_board_can_have_layer() {
    vector<string> blankRow(2, "");
    vector<vector<string>> values(1, blankRow);
    Layer layer = Layer(values);
    Board * b = (new Board(&layer))
          ->setButton(0, 0, new TestButton(0, 0))
          ->setButton(0, 1, new TestButton(0, 0));
    b->runKeys();
    return 0;
}

/* Tests Buttons */

static char * test_button_array_set_in_board() {
    vector<string> blankRow(2, "");
    vector<vector<string>> values(1, blankRow);
    Layer layer = Layer(values);
    Board *b = new Board(&layer);
    Button *firstButton = new TestButton(0, 0);
    b->setButton(0, 0, firstButton)
     ->setButton(0, 1, new TestButton(0, 1));

    mu_assert(
        (char *) "The button should have been set.",
        b->getButton(0, 0) == firstButton
    );

    return 0;
}

static char * test_button_can_be_mocked() {
    Button *b = new TestButton(2, 3);
    mu_assert(
        (char *) "We should be able to call non-virtual button methods.",
        b->getRow() == 2
    );
    // We should be able to call child methods. (if we cast.)
    ((TestButton *)b)->setRising();
    mu_assert(
        (char *) "virtual methods should resolve to children.",
        b->risingEdge()
    );
    return 0;
}


/* Integration Test.
 * This is how it will likely be used.
 */
static char * test_create_board() {
    // Create leaves in the layer tree.
    vector<string> blankRow(2, "");
    vector<vector<string>> tempUpValues(2, blankRow);
    Layer *tempUpLayer = new Layer(tempUpValues);

    // Create the branches, setting links.
    vector<vector<string>> mainValues(2, blankRow);
    Layer *mainLayer = (new Layer(mainValues))
        ->setLayerTemporarySwitch(tempUpLayer, 1, 1);

    // Create a board to manage layers and execute keystrokes.
    Board board = Board(mainLayer);
    return 0;
}

static char * test_switch_board_temp_layers() {
    // Create the layers.
    vector<string> blankRow(2, "");
    vector<vector<string>> layer2Values(1, blankRow);
    Layer *layer2 = new Layer(layer2Values);

    vector<vector<string>> layer1Values(1, blankRow);
    Layer *layer1 = (new Layer(layer1Values))
                  ->setLayerTemporarySwitch(layer2, 0, 1);

    // Create the board.
    Board *board = new Board(layer1);

    // Set the buttons.
    TestButton *valueButton = new TestButton(0, 0);
    TestButton *switchButton = new TestButton(0, 1);
    board->setButton(0, 0, valueButton)
         ->setButton(0, 1, switchButton);

    // Set the button to falling.
    switchButton->setFalling();

    // Run keys.
    board->runKeys();

    // Check to make sure the layer has changed.
    mu_assert(
        (char *) "The layer should be the second.",
        board->getCurrentLayer() == layer2
    );
    mu_assert(
        (char *) "The board should know its in a temporary mode.",
        board->inTemporaryLayer()
    );

    // Switch to rising again.
    switchButton->setRising();

    board->runKeys();

    mu_assert(
        (char *) "Letting the key up should bring us back.",
        board->getCurrentLayer() == layer1
    );
    mu_assert(
        (char *) "We should no longer be in the temp. layer.",
        ! (board->inTemporaryLayer())
    );

    return 0;
}

static char * test_switch_board_layers() {
    // Create the layers.
    vector<string> blankRow(2, "");
    vector<vector<string>> layer2Values(1, blankRow);
    Layer *layer2 = new Layer(layer2Values);

    vector<vector<string>> layer1Values(1, blankRow);
    Layer *layer1 = (new Layer(layer1Values))
                  ->setLayerSwitch(layer2, 0, 1);
    layer2->setLayerSwitch(layer1, 0, 1);

    // Create the board.
    Board *board = new Board(layer1);

    // Set the buttons.
    TestButton *valueButton = new TestButton(0, 0);
    TestButton *switchButton = new TestButton(0, 1);
    board->setButton(0, 0, valueButton)
         ->setButton(0, 1, switchButton);

    // Set to falling and run keys
    switchButton->setFalling();
    board->runKeys();

    mu_assert(
        (char *) "We should have switched to the next layer.",
        board->getCurrentLayer() == layer2
    );

    switchButton->setRising();
    board->runKeys();

    mu_assert(
        (char *) "We should not have switched after letting up.",
        board->getCurrentLayer() == layer2
    );
    return 0;
}

static char * all_tests() {
    mu_run_test(test_key_is_static);
    mu_run_test(test_get_key_value);
    mu_run_test(test_key_can_point_to_layer);
    mu_run_test(test_named_constructors_for_different_key_types);
    mu_run_test(test_layer_creates_keys);
    mu_run_test(test_layer_dimensions);
    mu_run_test(test_set_layer_up_and_down_keys);
    mu_run_test(test_temporary_layers_added_symmetrically_automatically);
    mu_run_test(test_can_chain_layer_setting);
    mu_run_test(test_board_can_have_layer);
    mu_run_test(test_button_array_set_in_board);
    mu_run_test(test_button_can_be_mocked);
    mu_run_test(test_create_board);
    mu_run_test(test_switch_board_temp_layers);
    mu_run_test(test_switch_board_layers);
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
