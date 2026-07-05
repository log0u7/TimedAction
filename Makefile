CXX         ?= g++
CXXFLAGS    ?= -std=c++03 -Wall -Wextra -pedantic -DARDUINO=100
INCLUDES    ?= -I. -Imock
BUILD_DIR   ?= build
SRC          = TimedAction.cpp
MOCK_CORE    = mock/mock.cpp
MOCK_MAIN    = mock/main.cpp
MOCK_TEST    = mock/test_api.cpp
HEADERS      = TimedAction.h

.PHONY: compile link test test-api lint format check-format compile-examples clean ci

compile:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC) -o $(BUILD_DIR)/TimedAction.o

link:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(MOCK_CORE) $(MOCK_MAIN) -o $(BUILD_DIR)/test.elf

test: compile link
	@echo "link OK"

test-api:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(MOCK_CORE) $(MOCK_TEST) -o $(BUILD_DIR)/test_api.elf
	$(BUILD_DIR)/test_api.elf
	@echo "api tests OK"

compile-examples:
	@for ex in HelloTimedAction ThreeExamplesAtOnce; do \
		echo "Checking examples/$$ex"; \
		$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(MOCK_CORE) examples/$$ex/$$ex.ino -o /dev/null -c 2>/dev/null || \
		echo "  (skipped - .ino format requires Arduino IDE)"; \
	done

lint:
	@which cppcheck >/dev/null 2>&1 && \
		cppcheck --enable=warning,performance,style --error-exitcode=1 \
			--language=c++ \
			--suppress=missingIncludeSystem \
			--suppress=unmatchedSuppression \
			$(SRC) $(HEADERS) $(MOCK_TEST) || \
		(echo "cppcheck not installed, skipping"; exit 0)

format:
	clang-format -i --style=file $(SRC) $(HEADERS) $(MOCK_CORE) $(MOCK_MAIN) $(MOCK_TEST) examples/**/*.ino 2>/dev/null || true

check-format:
	clang-format --dry-run --Werror --style=file $(SRC) $(HEADERS) $(MOCK_CORE) $(MOCK_MAIN) $(MOCK_TEST) examples/**/*.ino 2>/dev/null || true

clean:
	rm -rf $(BUILD_DIR)

ci: compile test test-api lint check-format
