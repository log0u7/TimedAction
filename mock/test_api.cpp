#include <cassert>
#include <TimedAction.h>

static bool callback_called = false;
static unsigned call_count = 0;

static void increment() {
    call_count++;
}

static void mark_called() {
    callback_called = true;
}

int main() {
    // Test 1: default constructor, first check should not trigger (previous=0, interval>0)
    {
        call_count = 0;
        _mock_millis_counter = 0;
        TimedAction ta(1000, increment);
        ta.check();
        assert(call_count == 0);
    }

    // Test 2: check after interval triggers callback
    {
        call_count = 0;
        _mock_millis_counter = 0;
        TimedAction ta(1000, increment);
        _mock_millis_counter = 1500;
        ta.check();
        assert(call_count == 1);
    }

    // Test 3: second check before next interval does nothing
    {
        call_count = 0;
        _mock_millis_counter = 0;
        TimedAction ta(1000, increment);
        _mock_millis_counter = 1500;
        ta.check();
        assert(call_count == 1);
        ta.check(); // no time passed since last check
        assert(call_count == 1);
    }

    // Test 4: constructor with custom previous
    {
        call_count = 0;
        _mock_millis_counter = 500;
        TimedAction ta(200, 1000, increment);
        _mock_millis_counter = 1500;  // 1000ms since previous=500
        ta.check();
        assert(call_count == 1);
    }

    // Test 5: disable() prevents callback
    {
        callback_called = false;
        _mock_millis_counter = 0;
        TimedAction ta(1000, mark_called);
        ta.disable();
        _mock_millis_counter = 2000;
        ta.check();
        assert(callback_called == false);
    }

    // Test 6: enable() after disable() restores functionality
    {
        callback_called = false;
        _mock_millis_counter = 0;
        TimedAction ta(1000, mark_called);
        ta.disable();
        ta.enable();
        _mock_millis_counter = 1500;
        ta.check();
        assert(callback_called == true);
    }

    // Test 7: reset() sets previous to current millis
    {
        call_count = 0;
        _mock_millis_counter = 0;
        TimedAction ta(1000, increment);
        _mock_millis_counter = 500;
        ta.reset();
        _mock_millis_counter = 1400;  // 900ms since reset, < 1000
        ta.check();
        assert(call_count == 0);
        _mock_millis_counter = 1600;  // 1100ms since reset, >= 1000
        ta.check();
        assert(call_count == 1);
    }

    // Test 8: setInterval() changes the interval
    {
        call_count = 0;
        _mock_millis_counter = 0;
        TimedAction ta(1000, increment);
        _mock_millis_counter = 1500;
        ta.check();
        assert(call_count == 1);
        ta.setInterval(2000);
        _mock_millis_counter = 3000;  // 1500ms since last check, < 2000
        ta.check();
        assert(call_count == 1);
        _mock_millis_counter = 4000;  // 2500ms since last check, >= 2000
        ta.check();
        assert(call_count == 2);
    }

    return 0;
}
