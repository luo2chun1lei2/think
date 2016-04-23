.PHONY:all clean

SUBS = src

all:
	@for dir in $(SUBS); do \
	if test -d $$dir; then \
		make -C $$dir || exit 1; \
	fi; done

clean:
	@for dir in $(SUBS); do \
	if test -d $$dir; then \
		make -C $$dir clean; \
	fi; done

run:
	@for dir in $(SUBS); do \
	if test -d $$dir; then \
		make -C $$dir run; \
	fi; done