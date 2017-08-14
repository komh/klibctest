.SUFFIXES : .c .o .obj .exe .dll .def

SHELL := /bin/sh

CC       := gcc
CXX      := g++
LD       := g++
CFLAGS   := -Wall
CXXFLAGS := -Wall
LDFLAGS  :=
LDLIBS   :=

TEST_DIRS    := io process misc startup str network
TEST_SRCS    := $(foreach dir,$(TEST_DIRS),$(wildcard $(dir)/*.c))
TEST_DEPS    := $(TEST_SRCS:.c=.d)
TEST_OBJS    := $(TEST_SRCS:.c=.o)
TEST_EXES-no := %-dll.c
TEST_EXES    := $(patsubst %.c,%.exe,$(filter-out $(TEST_EXES-no),$(TEST_SRCS)))
TEST-no      := %-sh.exe
TESTS        := $(addsuffix .test,$(filter-out $(TEST-no),$(TEST_EXES)))

define test_template
$(1) : $(1:.test=)
	@echo Testing $$<
	@d=$$(dir $$<); \
	n=$$(notdir $$<); \
	cd $$$$d; \
	if ./$$$$n > $$$$n.log 2>&1; then \
	  echo "PASSED"; \
	  rm -f $$$$n.log; \
	else \
	  echo "FAILED: see the $$$$d$$$$n.log"; \
	fi
endef

%.d : %.c
	$(CC) $(CFLAGS) -MM -MP -MT "$(@:.d=.o) $@" -MF $@ $<

%.d : %.cpp
	$(CXX) $(CXXFLAGS) -MM -MP -MT "$(@:.d=.o) $@" -MF $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.exe : %.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY : all $(TESTS) clean

all : $(TEST_EXES) $(TESTS)
	@echo -----; \
	failed_log=; \
	passed=0; \
	failed=0; \
	for l in $(TESTS:.test=.log); do \
	  if test -f $$l; then \
	    failed_log="$$failed_log $$l"; \
	    failed=$$(($$failed + 1)); \
	  else \
	    passed=$$(($$passed + 1)); \
	  fi; \
	done; \
	echo "PASSED: $$passed"; \
	echo "FAILED: $$failed"; \
	test $$failed = 0 || echo "FAILED test log: $$failed_log"

$(foreach t, $(TESTS), $(eval $(call test_template, $(t))))

startup/cwdefault-1.exe : startup/cwdefault-1.def
startup/cwdefault-1.exe : LDFLAGS += -Zomf

startup/heapvote.dll : LDFLAGS =
startup/heapvote.dll : startup/heapvote-1-dll.o
	$(LD) -Zomf -Zdll $(LDFLAGS) -o $@ $^ $(LDLIBS)

startup/heapvote-1.exe : startup/heapvote.dll
startup/heapvote-1.exe : LDFLAGS += -Zhigh-mem

clean :
	rm -f $(TEST_SRCS:.c=.bak)
	rm -f $(TEST_DEPS)
	rm -f $(TEST_OBJS)
	rm -f $(TEST_EXES)
	rm -f startup/heapvote.dll

ifeq ($(filter %clean, $(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

