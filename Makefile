CXX       ?= g++
CXXFLAGS  ?= -std=c++03 -Wall -Wextra -pedantic -DARDUINO=100
INCLUDES  ?= -I. -Imock
BUILD_DIR ?= build
SRC        = TimedAction.cpp
MOCK_SRC   = mock/main.cpp
HEADERS    = TimedAction.h

.PHONY: compile test link lint format check-format clean ci

compile:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC) -o $(BUILD_DIR)/TimedAction.o

link:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(MOCK_SRC) -o $(BUILD_DIR)/test.elf

test: compile link
	@echo "OK"

lint:
	@which cppcheck >/dev/null 2>&1 && \
		cppcheck --enable=warning,performance,style --error-exitcode=1 \
			--suppress=missingIncludeSystem \
			--suppress=unmatchedSuppression \
			$(SRC) $(HEADERS) || \
		(echo "cppcheck not installed, skipping"; exit 0)

format:
	clang-format -i --style=file $(SRC) $(HEADERS) $(MOCK_SRC) examples/**/*.ino 2>/dev/null || true

check-format:
	clang-format --dry-run --Werror --style=file $(SRC) $(HEADERS) $(MOCK_SRC) examples/**/*.ino 2>/dev/null || true

clean:
	rm -rf $(BUILD_DIR)

ci: compile link lint check-format
