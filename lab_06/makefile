CC := gcc

# Флаги компиляции
CFLAGS := -std=c99 -Wall -Wpedantic -Wextra -Werror

# Папки
SRCDIR := src/
INCDIR := inc/
OUTDIR := out/

# Цель сборки
TARGET := app.exe

SRCS := $(wildcard $(SRCDIR)*.c)
OBJS := $(SRCS:$(SRCDIR)%.c=$(OUTDIR)%.o)
DEPS := $(SRCS:$(SRCDIR)%.c=$(OUTDIR)%.d)

.PHONY : debug
debug : $(TARGET)
debug : CFLAGS += -g3

.PHONY : release
release : $(TARGET)
release : CFLAGS += -DNDEBUG -O2

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OUTDIR)%.o : $(SRCDIR)%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -MD -o $@ -c $<

-include $(DEPS)

$(OUTDIR) :
	mkdir $@

.PHONY : clean
clean :
	@rm -f $(TARGET) $(OUTDIR)*
