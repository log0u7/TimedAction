#include <TimedAction.h>

static void callback() {}

int main() {
    TimedAction ta(1000, callback);
    ta.check();
    ta.reset();
    ta.disable();
    ta.enable();
    ta.setInterval(500);

    TimedAction ta2(100, 2000, callback);
    ta2.check();

    return 0;
}
