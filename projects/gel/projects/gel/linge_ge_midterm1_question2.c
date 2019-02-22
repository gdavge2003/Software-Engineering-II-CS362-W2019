// Linge Ge - CS362 - Midterm 1 - Question 2

struct container {};

void add (int n, container* c); /* adds n to c */
int get (int n, container* c); /* returns 1 if n is in c, 0 otherwise */
// NOTE: made a slight assumption for remove(), that it returns 0 if n is not in c.
// The original specification didn't make sense..
int remove (int n, container* c); /* returns 1 if n was in c; 0 otherwise */
container* newContainer(); /* returns a new container if memory avail */
void removeAll(int n, container* c); /* removes all instances of the number n from c*/.
int size(container* c);/* returns the number of elements in c*/

int main() {
    // Test case 1: positive tests
    int result1, result2, result3, resultSize, resultSize2;
    container* container1 = newContainer();

    add(-1, container1); // positive run
    add(0, container1); // positive run
    add(1, container1); // positive run
    result1 = remove(0, container1); // positive run
    result2 = remove(1, container1); // positive run
    result3 = get(-1, container1); // positive run
    resultSize = size(container1); // positive run - accounts for correct size changes

    assert(result1, 1); // positive: removal successful
    assert(result2, 1); // positive: removal successful
    assert(result3, 1); // positive: get successful
    assert(resultSize, 1); // size should be consistent if all above is successful


    // Test case 2: negative tests
    container* container2 = newContainer();

    add(1, container2);
    add(1, container2);
    add(1, container2);
    add(0, container2);
    removeAll(1, container2); // removes all the 1s
    result1 = get(1, container2); // negative test - no more 1s should be there
    result2 = remove(1, container2); // negative test - no more 1s should be there
    resultSize = size(container2);

    assert(result1, 0); // positive test for removeAll(), negative test for get()
    assert(result2, 0); // positive test for removeAll(), negative test for remove()
    assert(resultSize, 1); // positive test if all above is successful


    // Test case 3: some edge cases
    container* container3 = newContainer();

    add(-1, container3);
    add(-1, container3);
    add(-1, container3);
    removeAll(0, container3); // negative test - shouldn't remove anything
    resultSize = size(container3);

    remove(-1, container3);
    remove(-1, container3);
    result1 = remove(-1, container3); // positive - should have removed last value remaining
    result2 = get(-1, container3); // negative - shouldn't get anything
    resultSize2 = size(container3);

    assert(resultSize, 3); // positive test for add(), negative test for removeAll()
    assert(result1, 1); // positive test - removes the last remaining 1 value;
    assert(result2, 0); // negative test - get shouldn't get anything since all values removed
    assert(resultSize2, 0); // positive test - confirm empty container

    return 0;
}